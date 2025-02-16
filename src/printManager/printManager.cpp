#include "printManager.h"


PrintManager::PrintManager() {}

void PrintManager::convertHtmlToPdf(const QString &htmlContent, const QString &outputFilePath) {
    QTextDocument document;
    document.setHtml(htmlContent);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(outputFilePath);
    printer.setPageMargins(QMarginsF(10, 10, 10, 10));

    document.print(&printer);
}
