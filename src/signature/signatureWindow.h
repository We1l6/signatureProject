#ifndef SIGNATUREWINDOW_H
#define SIGNATUREWINDOW_H

#include <QDialog>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QBuffer>
#include "signatureCanvas.h"
#include "signatureSaver.h"
#include <QVBoxLayout>

namespace Ui {
class SignatureWindow;
}

class SignatureWindow : public QDialog {
    Q_OBJECT

public:
    explicit SignatureWindow(QWidget *parent = nullptr);
    ~SignatureWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::SignatureWindow *ui;
    SignatureCanvas *canvas;
    QTimer *cursorTimer;
};

#endif // SIGNATUREWINDOW_H
