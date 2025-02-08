#include "signatureSaver.h"

SignatureSaver::SignatureSaver() {}

QByteArray SignatureSaver::saveImage(QImage &image, const QString &filePath) {
    QColor whiteColor(255, 255, 255);

    if (image.format() != QImage::Format_ARGB32 && image.format() != QImage::Format_RGBA8888) {
        image = image.convertToFormat(QImage::Format_ARGB32);
    }

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            if (image.pixelColor(x, y) == whiteColor) {
                image.setPixelColor(x, y, QColor(255, 255, 255, 0));
            }
        }
    }
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    if (!buffer.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open buffer for writing!";
        return QByteArray();
    }
    if (!image.save(&buffer, "PNG")) {
        qDebug() << "Failed to save image to buffer!";
        return QByteArray();
    }
    image.save(filePath);
    return byteArray;
}
