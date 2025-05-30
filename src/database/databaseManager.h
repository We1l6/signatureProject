#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QDebug>
#include <QtSql>

#include "../structures/rowData.h"
#include "../logger/logger.h"
#include "Queries.h"

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    bool connect(const QString& dbPath);
    void disconnect();
    bool executeQuery(const QString& queryStr);
    QSqlDatabase& getDatabase();
    bool insertRow(int sheetID, int rowNumber);
    bool updateRowData(const Structures::RowData& rowData);
    std::vector<Structures::RowData> fetchRowsBySheetID(int sheetID);
    std::vector<std::vector<Structures::RowData>> fetchAllRowsGroupedBySheet();
    int getMaxSheetID();

private:
    QSqlDatabase db;

    DatabaseManager();
    ~DatabaseManager();

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    void createTables();
};

#endif // DATABASEMANAGER_H
