#include "configManager.h"

ConfigManager::ConfigManager(const QString& filePath) : configFilePath(filePath) {}

bool ConfigManager::loadConfig()
{
    if (!QFile::exists(configFilePath))
    {
        qDebug() << "Config file not found: " << configFilePath.toStdString();
        return false;
    }

    try
    {
        configData = YAML::LoadFile(configFilePath.toStdString());
        return true;
    }
    catch (const YAML::Exception& e)
    {
        qDebug() << "Error loading config: " << e.what();
        return false;
    }
}

bool ConfigManager::saveConfig() const
{
    try
    {
        QFile file(configFilePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "Cannot open config file for writing: " << configFilePath.toStdString();
            return false;
        }

        QTextStream out(&file);
        out << QString::fromStdString(YAML::Dump(configData));
        file.close();
        return true;
    }
    catch (const std::exception& e)
    {
        qDebug() << "Error saving config: " << e.what();
        return false;
    }
}

QString ConfigManager::getQStringValue(const QString& key, const QString& defaultValue) const
{
    if (configData[key.toStdString()]) {
        return QString::fromStdString(configData[key.toStdString()].as<std::string>());
    }
    return defaultValue;
}


void ConfigManager::setQStringValue(const QString& key, const QString& value)
{
    configData[key.toStdString()] = value.toStdString();
}

