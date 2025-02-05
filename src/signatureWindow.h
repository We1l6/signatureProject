#ifndef SIGNATUREWINDOW_H
#define SIGNATUREWINDOW_H

#include <QDialog>

namespace Ui {
class SignatureWindow;
}

class SignatureWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SignatureWindow(QWidget *parent = nullptr);
    ~SignatureWindow();

private:
    Ui::SignatureWindow *ui;
};

#endif // SIGNATUREWINDOW_H
