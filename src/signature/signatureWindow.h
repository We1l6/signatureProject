#ifndef SIGNATUREWINDOW_H
#define SIGNATUREWINDOW_H

#include <QDialog>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QBuffer>
#include <QVBoxLayout>

#include "signatureCanvas.h"
#include "signatureSaver.h"
#include "../logger/logger.h"

namespace Ui {
class SignatureWindow;
}

class SignatureWindow : public QDialog {
    Q_OBJECT

public:
    explicit SignatureWindow(int signatureButtonID, QWidget *parent = nullptr);
    ~SignatureWindow();
    void setPicture(QByteArray byteArray);
signals:
    void signatureSaved(int signatureID, QByteArray imgBit);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
private:
    QByteArray m_byteArray = 0;
    int m_signatureButtonID;
    Ui::SignatureWindow *ui;
    SignatureCanvas *canvas;
    QTimer *cursorTimer;
};

#endif // SIGNATUREWINDOW_H
