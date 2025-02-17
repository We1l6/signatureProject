#include "printManager.h"

PrintManager::PrintManager() {}

void PrintManager::convertHtmlToPdf(const QString &htmlFilePath, const QString &outputFilePath) {
    QFile file(htmlFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open HTML file:" << htmlFilePath;
        return;
    }

    QTextStream in(&file);
    QString htmlContent = in.readAll();
    file.close();

    htmlContent.prepend("<style>body, html { margin: 24px; padding: 0; margin-left: 40px;}</style>");

    QTextDocument document;
    document.setHtml(htmlContent);
    document.setDocumentMargin(0);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(outputFilePath);
    printer.setFullPage(true);
    printer.setPageMargins(QMarginsF(60, 24, 24, 24));
    printer.setPageSize(QPageSize(QPageSize::A4));

    document.setPageSize(printer.pageRect(QPrinter::Point).size());

    document.print(&printer);
}
