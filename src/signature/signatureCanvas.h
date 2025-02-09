#ifndef SIGNATURECANVAS_H
#define SIGNATURECANVAS_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>

class SignatureCanvas : public QWidget {
    Q_OBJECT

public:
    explicit SignatureCanvas(QWidget *parent = nullptr);
    void clear();
    QImage getImage() const { return image; }
    void setImageFromByteArray(const QByteArray &byteArray);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    QImage image;
    QPoint lastPoint;
    bool drawing;
};

#endif // SIGNATURECANVAS_H
