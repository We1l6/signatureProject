#ifndef PRINTMANAGER_H
#define PRINTMANAGER_H

#include <QString>
#include <QApplication>
#include <QTextDocument>
#include <QPrinter>

class PrintManager
{
public:
    PrintManager();
    void convertHtmlToPdf(const QString &htmlContent, const QString &outputFilePath);
};

#endif // PRINTMANAGER_H
