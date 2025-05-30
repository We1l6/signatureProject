#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <yaml-cpp/yaml.h>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class ConfigManager
{
public:
    explicit ConfigManager(const QString& filePath);

    bool loadConfig();
    bool saveConfig() const;

    QString getQStringValue(const QString& key, const QString& defaultValue) const;
    void setQStringValue(const QString& key, const QString& value);

private:
    QString configFilePath;
    YAML::Node configData;
};

#endif // CONFIGMANAGER_H
