#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include<QString>
#include<QDebug>
#include <QtSql>
#include "Queries.h"

class DatabaseManager
{
public:
    static DatabaseManager& instance();

    bool connect(const QString& dbPath);
    void disconnect();
    bool executeQuery(const QString& queryStr);
    QSqlDatabase& getDatabase();

private:
    QSqlDatabase db;

    DatabaseManager();
    ~DatabaseManager();

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    void createTables();
};

#endif // DATABASEMANAGER_H
