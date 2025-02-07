#ifndef SIGNATURESAVER_H
#define SIGNATURESAVER_H

#include <QImage>
#include <QString>

class SignatureSaver
{
public:
    SignatureSaver();
    static bool saveImage(const QImage &image, const QString &filePath);
};

#endif // SIGNATURESAVER_H
