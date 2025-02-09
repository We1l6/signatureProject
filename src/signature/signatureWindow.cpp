#include "SignatureWindow.h"
#include "src/ui_signatureWindow.h"

SignatureWindow::SignatureWindow(int signatureButtonID, QWidget *parent)
    : QDialog(parent), ui(new Ui::SignatureWindow), cursorTimer(new QTimer(this)) {
    ui->setupUi(this);
    canvas = new SignatureCanvas(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(canvas);
    setLayout(layout);
    m_signatureButtonID = signatureButtonID,
    showFullScreen();
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

SignatureWindow::~SignatureWindow() {
    delete cursorTimer;
    delete ui;
}

void SignatureWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        close();
    } else if (event->key() == Qt::Key_Space) {
        canvas->clear();
    } else {
        QWidget::keyPressEvent(event);
    }
}

void SignatureWindow::closeEvent(QCloseEvent *event) {
    QImage img = canvas->getImage();

    SignatureSaver saver;
    QByteArray imgBit = saver.saveImage(img, QCoreApplication::applicationDirPath() + "/signs/drawing.png");
    if (!imgBit.isEmpty()) {
        qDebug() << "Image saved successfully!";
        LOG_INFO("Image saved successfully!");
        m_byteArray = imgBit;
        emit signatureSaved(m_signatureButtonID, imgBit);
    } else {
        qDebug() << "Failed to save image!";
        LOG_INFO("Failed to save image!");
    }
    cursorTimer->stop();
    event->accept();
}

void SignatureWindow::setPicture(QByteArray byteArray) {
    if (byteArray.isEmpty()) {
        qDebug() << "Error: received an empty QByteArray!";
    } else {
        qDebug() << "Received a non-empty QByteArray!";
    }
    canvas->setImageFromByteArray(byteArray);
}
