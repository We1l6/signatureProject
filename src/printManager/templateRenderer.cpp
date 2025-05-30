#include "templateRenderer.h"

TemplateRenderer::TemplateRenderer() {}




void TemplateRenderer::fillHTMLfile(const QString templateFilePath, const QString outputFile, const std::vector<Structures::RowData> rowData){
    inja::Environment env;

    std::ifstream templateFile(templateFilePath.toStdString());
    if(!templateFile){
        qDebug()<<"Failed to open " << templateFilePath;
        //LOG_WARN("Failed to open " + templateFilePath);
        return;
    }

    std::string template_content((std::istreambuf_iterator<char>(templateFile)), std::istreambuf_iterator<char>());
    templateFile.close();

    inja::Template tmpl = env.parse(template_content);
    inja::json data;
    std::vector<inja::json> rows;

    for (int i = 0; i < 49; ++i) {
        rows.push_back(convertRowDataToJson(rowData[i]));
    }
    data["rows"] = rows;
    std::string rendered = env.render(tmpl, data);
    std::ofstream output_file(outputFile.toStdString());
    if (!output_file) {
        qDebug()<<"Failed to open " << outputFile;
        //LOG_WARN("Failed to open " + outputFile);
        return;
    }
    output_file << rendered;
    output_file.close();
}


inja::json TemplateRenderer::convertRowDataToJson(const Structures::RowData rowData) const {
    inja::json row_json;
    row_json["to_whom_issued"] = rowData.toWhomIssued.toStdString();
    row_json["unit"] = rowData.unit.toStdString();
    row_json["account_number"] = rowData.accountNumber.toStdString();
    row_json["number_of_sheets"] = rowData.numberOfSheets;
    row_json["date_of_receipt"] = rowData.dateOfReceipt.toStdString();
    row_json["receipt_signature"] = QString::fromUtf8(rowData.firstSign.toBase64()).toStdString();
    row_json["return_signature"] = QString::fromUtf8(rowData.secondSign.toBase64()).toStdString();;
    return row_json;
}
