#include "signatureSaver.h"

SignatureSaver::SignatureSaver() {}

bool SignatureSaver::saveImage(const QImage &image, const QString &filePath) {
    QImage img = image;
    if (img.format() != QImage::Format_ARGB32) {
        img = img.convertToFormat(QImage::Format_ARGB32);
    }

    for (int y = 0; y < img.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(img.scanLine(y));
        for (int x = 0; x < img.width(); ++x) {
            if (line[x] == qRgb(255, 255, 255)) {
                line[x] = qRgba(255, 255, 255, 0);
            }
        }
    }

    return img.save(filePath);
}
