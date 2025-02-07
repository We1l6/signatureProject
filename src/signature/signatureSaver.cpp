#include "signatureSaver.h"

SignatureSaver::SignatureSaver() {}

bool SignatureSaver::saveImage(const QImage &image, const QString &filePath) {
    QImage img = image;

    QColor whiteColor(255, 255, 255);

    if (img.format() != QImage::Format_ARGB32 && img.format() != QImage::Format_RGBA8888) {
        img = img.convertToFormat(QImage::Format_ARGB32);
    }

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            if (img.pixelColor(x, y) == whiteColor) {
                img.setPixelColor(x, y, QColor(255, 255, 255, 0));
            }
        }
    }

    return img.save(filePath);
}
