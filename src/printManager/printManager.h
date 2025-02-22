#ifndef PRINTMANAGER_H
#define PRINTMANAGER_H

#include <QString>
#include <QApplication>
#include <QTextDocument>
#include <QPrinter>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QDebug>

class PrintManager
{
public:
    PrintManager();
    void convertHtmlToPdf(const QString &htmlFilePath, const QString &outputFilePath);
    void convertMultipleHtmlToPdf(const QStringList &htmlFilePaths, const QString &outputFilePath);
};

#endif // PRINTMANAGER_H
