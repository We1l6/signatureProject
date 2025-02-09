#include "signatureCanvas.h"

SignatureCanvas::SignatureCanvas(QWidget *parent)
    : QWidget(parent), drawing(false) {
    image = QImage(800, 600, QImage::Format_ARGB32);
    image.fill(Qt::white);
    setMinimumSize(800, 600);
}

void SignatureCanvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}

void SignatureCanvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawing = true;
    }
}

void SignatureCanvas::mouseMoveEvent(QMouseEvent *event) {
    if (drawing && (event->buttons() & Qt::LeftButton)) {
        QPainter painter(&image);
        painter.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
        update();
    }
}

void SignatureCanvas::resizeEvent(QResizeEvent *event) {
    QImage newImage(size(), QImage::Format_ARGB32);
    newImage.fill(Qt::white);

    QPainter painter(&newImage);
    painter.drawImage(0, 0, image);
    image = newImage;

    update();
}

void SignatureCanvas::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        drawing = false;
    }
}

void SignatureCanvas::clear() {
    image.fill(Qt::white);
    update();
}


void SignatureCanvas::setImageFromByteArray(const QByteArray &byteArray) {
    if (!byteArray.isEmpty()) {
        if (!image.loadFromData(byteArray, "PNG")) {
            qDebug() << "Error loading image from QByteArray!";
        }
        update();
    } else {
        qDebug() << "Received an empty QByteArray!";
    }
}

