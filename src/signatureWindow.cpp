#include "SignatureWindow.h"
#include "src/ui_signatureWindow.h"

SignatureWindow::SignatureWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignatureWindow)
    , drawing(false)
    , cursorTimer(new QTimer(this))
{
    ui->setupUi(this);
    image = QImage(size(), QImage::Format_ARGB32);
    image.fill(Qt::white);
    showFullScreen();
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

SignatureWindow::~SignatureWindow()
{
    delete cursorTimer;
    delete ui;
}

void SignatureWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        close();
    } else if(event->key() == Qt::Key_Space){
        clearImage();
    } else {
        QWidget::keyPressEvent(event);
    }
}

void SignatureWindow::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}


void SignatureWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawImage(0, 0, image);
}


void SignatureWindow::setImageFromByteArray(const QByteArray &byteArray) {
    if(!byteArray.isEmpty()){
        image.loadFromData(byteArray, "PNG");
        update();
    }
}


void SignatureWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawing = true;
    }
}


void SignatureWindow::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        QPainter painter(&image);
        painter.setRenderHint(QPainter::Antialiasing, true);
        QPen pen(Qt::black, 20, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
        update();
    }
}


void SignatureWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        QPainter painter(&image);
        painter.setRenderHint(QPainter::Antialiasing, true);
        QPen pen(Qt::black, 20, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        painter.drawLine(lastPoint, event->pos());
        drawing = false;
    }
}

QByteArray SignatureWindow::getImageAsByteArray() {
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    return byteArray;
}


void SignatureWindow::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(Qt::white);
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void SignatureWindow::closeEvent(QCloseEvent *event)
{
    saveImage(QCoreApplication::applicationDirPath()+"/signs/drawing.png");
    cursorTimer->stop();
    event->accept();
    byteArray = getImageAsByteArray();
    //emit requestChangeImage(byteArray);
}

void SignatureWindow::saveImage(const QString &filePath)
{
    QColor whiteColor(255, 255, 255);

    if (image.format() != QImage::Format_ARGB32 && image.format() != QImage::Format_RGBA8888) {
        image = image.convertToFormat(QImage::Format_ARGB32);
    }

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            if (image.pixelColor(x, y) == whiteColor) {
                image.setPixelColor(x, y, QColor(255, 255, 255, 0));
            }
        }
    }

    if (image.save(filePath)) {
        qDebug() << "Image saved successfully to:" << filePath;
    } else {
        qDebug() << "Failed to save the image to:" << filePath;
    }
}

void SignatureWindow::clearImage()
{
    image.fill(Qt::white);
    update();
}
