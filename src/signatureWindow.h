#ifndef SIGNATUREWINDOW_H
#define SIGNATUREWINDOW_H

#include <QDialog>
#include <QTimer>
#include <QKeyEvent>
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
    QImage image;
    QPoint lastPoint;
    bool drawing;
    QTimer *cursorTimer = nullptr;
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // SIGNATUREWINDOW_H
