#include "SignatureWindow.h"
#include "src/ui_signatureWindow.h"

SignatureWindow::SignatureWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::SignatureWindow), cursorTimer(new QTimer(this)) {
    ui->setupUi(this);
    canvas = new SignatureCanvas(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(canvas);
    setLayout(layout);

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
    if (saver.saveImage(img, QCoreApplication::applicationDirPath() + "/signs/drawing.png")) {
        qDebug() << "Image saved successfully!";
    } else {
        qDebug() << "Failed to save image!";
    }

    cursorTimer->stop();
    event->accept();
}


