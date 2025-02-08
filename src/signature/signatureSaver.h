#ifndef SIGNATURESAVER_H
#define SIGNATURESAVER_H

#include <QImage>
#include <QString>
#include <QDebug>
#include <QBuffer>

class SignatureSaver
{
public:
    SignatureSaver();
    static QByteArray saveImage(QImage &image, const QString &filePath);
};

#endif // SIGNATURESAVER_H
