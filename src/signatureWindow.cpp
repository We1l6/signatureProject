#include "signatureWindow.h"
#include "ui_signatureWindow.h"

SignatureWindow::SignatureWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignatureWindow)
{
    ui->setupUi(this);
}

SignatureWindow::~SignatureWindow()
{
    delete ui;
}
