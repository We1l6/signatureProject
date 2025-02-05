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

    } else {
        QWidget::keyPressEvent(event);
    }
}
