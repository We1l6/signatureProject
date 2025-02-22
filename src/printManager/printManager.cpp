#include "printManager.h"


PrintManager::PrintManager() {}

void PrintManager::convertHtmlToPdf(const QString &htmlFilePath, const QString &outputFilePath) {
    QFile file(htmlFilePath);
    if (!file.exists()) {
        qWarning() << "HTML file not found:" << htmlFilePath;
        return;
    }

    QString wkhtmltopdfPath = "wkhtmltopdf/bin/wkhtmltopdf.exe";

    QProcess checkProcess;
    checkProcess.start(wkhtmltopdfPath, QStringList() << "--version");
    checkProcess.waitForFinished();
    if (checkProcess.exitCode() != 0) {
        qWarning() << "Wkhtmltopdf could not be found. Make sure it is installed and available.";
        return;
    }

    QProcess process;
    QStringList arguments;

    arguments << htmlFilePath << outputFilePath;

    process.start(wkhtmltopdfPath, arguments);
    if (!process.waitForStarted()) {
        qWarning() << "Wkhtmltopdf failed to start.";
        return;
    }

    process.waitForFinished();

    if (process.exitCode() == 0) {
        qDebug() << "PDF created successfully: " << outputFilePath;
    } else {
        qWarning() << "Error converting HTML to PDF.";
        qWarning() << process.readAllStandardError();
    }
}

void PrintManager::convertMultipleHtmlToPdf(const QStringList &htmlFilePaths, const QString &outputFilePath) {
    if (htmlFilePaths.isEmpty()) {
        qWarning() << "No HTML files provided.";
        return;
    }

    QString wkhtmltopdfPath = "wkhtmltopdf/bin/wkhtmltopdf.exe";

    QProcess checkProcess;
    checkProcess.start(wkhtmltopdfPath, QStringList() << "--version");
    checkProcess.waitForFinished();
    if (checkProcess.exitCode() != 0) {
        qWarning() << "Wkhtmltopdf could not be found. Make sure it is installed and available.";
        return;
    }

    QProcess process;
    QStringList arguments;


    arguments << htmlFilePaths;

    arguments << outputFilePath;

    process.start(wkhtmltopdfPath, arguments);
    if (!process.waitForStarted()) {
        qWarning() << "Wkhtmltopdf failed to start.";
        return;
    }

    process.waitForFinished();

    if (process.exitCode() == 0) {
        qDebug() << "PDF created successfully: " << outputFilePath;
    } else {
        qWarning() << "Error converting multiple HTML files to PDF.";
        qWarning() << process.readAllStandardError();
    }
}

