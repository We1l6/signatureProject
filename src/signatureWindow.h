#ifndef SIGNATUREWINDOW_H
#define SIGNATUREWINDOW_H

#include <QDialog>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QBuffer>

namespace Ui {
class SignatureWindow;
}

class SignatureWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SignatureWindow(QWidget *parent = nullptr);
    ~SignatureWindow();
    void setImageFromByteArray(const QByteArray &byteArray);

    QByteArray getImageAsByteArray();
    QByteArray byteArray;

private:
    Ui::SignatureWindow *ui;
    QImage image;
    QPoint lastPoint;
    bool drawing;
    QTimer *cursorTimer = nullptr;
protected:
    void clearImage();
    void saveImage(const QString &filePath);
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void resizeImage(QImage *image, const QSize &newSize);
    void closeEvent(QCloseEvent *event) override;
    //void leaveEvent(QEvent *event) override;
    //void enterEvent(QEnterEvent *event) override;
    //void showEvent(QShowEvent *event) override;
};

#endif // SIGNATUREWINDOW_H
