#ifndef TEMPLATERENDERER_H
#define TEMPLATERENDERER_H

#include "inja.hpp"
#include <fstream>
#include <QString>
#include <QDebug>
#include "../logger/logger.h"
#include "../structures/rowData.h"

class TemplateRenderer
{
public:
    TemplateRenderer();

    void fillHTMLfile(const QString templateFilePath, const QString outputFile, const std::vector<Structures::RowData> rowData);
    inja::json convertRowDataToJson(const Structures::RowData rowData) const;
};

#endif // TEMPLATERENDERER_H
