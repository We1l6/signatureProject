#include "databaseManager.h"

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager() {}

DatabaseManager::~DatabaseManager() {
    disconnect();
}

bool DatabaseManager::connect(const QString& dbPath) {
    if (db.isOpen()) {
        qDebug() << "Database already connected.";
        LOG_INFO("Database already connected.");
        return true;
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Database connection failed: " << db.lastError().text();
        LOG_WARN("Database connection failed: " + db.lastError().text().toStdString());
        return false;
    }

    qDebug() << "Database connected successfully!";
    LOG_INFO("Database connected successfully!");

    createTables();
    return true;
}

void DatabaseManager::disconnect() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "Database connection closed.";
        LOG_INFO("Database connection closed.");
    }
}

bool DatabaseManager::executeQuery(const QString& queryStr) {
    QSqlQuery query;
    if (!query.exec(queryStr)) {
        qDebug() << "Query execution failed: " << query.lastError().text();
        LOG_WARN("Query execution failed: " + query.lastError().text().toStdString());
        return false;
    }
    return true;
}

QSqlDatabase& DatabaseManager::getDatabase() {
    return db;
}

void DatabaseManager::createTables() {
    if (!executeQuery(Queries::gridTable)) {
        qDebug() << "Failed to create table gridTable";
        LOG_WARN("Failed to create table gridTable");
    } else {
        qDebug() << "Table gridTable is ready";
        LOG_INFO("Table gridTable is ready");
    }
}


bool DatabaseManager::insertRow(int sheetID, int rowNumber) {
    QSqlQuery query;
    query.prepare(Queries::insertIntoGridTable);
    query.bindValue(":sheetID", sheetID);
    query.bindValue(":rowNumber", rowNumber);

    if (!query.exec()) {
        qDebug() << "Error inserting into database:" << query.lastError().text();
        LOG_WARN("Error inserting into database:" + query.lastError().text().toStdString());
        return false;
    }
    return true;
}


bool DatabaseManager::updateRowData(const Structures::RowData& rowData) {
    QSqlQuery query;
    query.prepare(Queries::updategridTable);

    query.bindValue(":toWhomIssued", rowData.toWhomIssued);
    query.bindValue(":unit", rowData.unit);
    query.bindValue(":accountNumber", rowData.accountNumber);
    query.bindValue(":numberOfSheets", rowData.numberOfSheets);
    query.bindValue(":dateOfReceipt", rowData.dateOfReceipt);
    query.bindValue(":firstSign", rowData.firstSign);
    query.bindValue(":secondSign", rowData.secondSign);
    query.bindValue(":sheetID", rowData.sheetID);
    query.bindValue(":rowNumber", rowData.rowNumber);

    if (!query.exec()) {
        qDebug() << "Error updating line:" << query.lastError().text();
        LOG_WARN("Error updating line:" + query.lastError().text().toStdString());
        return false;
    }
    return true;
}

std::vector<Structures::RowData> DatabaseManager::fetchRowsBySheetID(int sheetID) {
    std::vector<Structures::RowData> rows;
    QSqlQuery query;

    query.prepare(Queries::selectFromGridTable);
    query.bindValue(":sheetID", sheetID);

    if (!query.exec()) {
        qDebug() << "Error fetching rows:" << query.lastError().text();
        LOG_WARN("Error fetching rows: " + query.lastError().text().toStdString());
        return rows;
    }

    while (query.next()) {
        Structures::RowData rowData;
        rowData.sheetID = query.value("sheet_id").toInt();
        rowData.rowNumber = query.value("row_number").toInt();
        rowData.toWhomIssued = query.value("to_whom_issued").toString();
        rowData.unit = query.value("unit").toString();
        rowData.accountNumber = query.value("account_number").toString();
        rowData.numberOfSheets = query.value("number_of_sheets").toInt();
        rowData.dateOfReceipt = query.value("date_of_receipt").toString();
        rowData.firstSign = query.value("receipt_signature").toByteArray();
        rowData.secondSign = query.value("return_signature").toByteArray();

        rows.push_back(rowData);
    }

    return rows;
}

int DatabaseManager::getMaxSheetID(){
    QSqlQuery query;
    if (query.exec("SELECT MAX(sheet_id) FROM gridTable")) {
        if (query.next()) {
            return query.value(0).toInt();
        }
    }

    return -1;
}

std::vector<std::vector<Structures::RowData>> DatabaseManager::fetchAllRowsGroupedBySheet() {
    std::vector<std::vector<Structures::RowData>> groupedRows;
    std::map<int, std::vector<Structures::RowData>> sheetMap;
    QSqlQuery query;

    query.prepare(Queries::selectAllFromGridTable);
    if (!query.exec()) {
        qDebug() << "Error fetching rows:" << query.lastError().text();
        LOG_WARN("Error fetching rows: " + query.lastError().text().toStdString());
        return groupedRows;
    }

    while (query.next()) {
        Structures::RowData rowData;
        rowData.sheetID = query.value("sheet_id").toInt();
        rowData.rowNumber = query.value("row_number").toInt();
        rowData.toWhomIssued = query.value("to_whom_issued").toString();
        rowData.unit = query.value("unit").toString();
        rowData.accountNumber = query.value("account_number").toString();
        rowData.numberOfSheets = query.value("number_of_sheets").toInt();
        rowData.dateOfReceipt = query.value("date_of_receipt").toString();
        rowData.firstSign = query.value("receipt_signature").toByteArray();
        rowData.secondSign = query.value("return_signature").toByteArray();

        sheetMap[rowData.sheetID].push_back(rowData);
    }

    for (auto& [sheetID, rows] : sheetMap) {
        groupedRows.push_back(std::move(rows));
    }

    return groupedRows;
}


