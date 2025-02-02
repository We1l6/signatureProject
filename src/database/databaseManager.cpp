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
    query.prepare("INSERT INTO gridTable (sheet_id, row_number) VALUES (:sheetID, :rowNumber)");
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
    query.prepare("UPDATE gridTable SET "
                  "to_whom_issued = :toWhomIssued, "
                  "unit = :unit, "
                  "account_number = :accountNumber, "
                  "number_of_sheets = :numberOfSheets, "
                  "date_of_receipt = :dateOfReceipt "
                  "WHERE sheet_id = :sheetID AND row_number = :rowNumber");

    query.bindValue(":toWhomIssued", rowData.toWhomIssued);
    query.bindValue(":unit", rowData.unit);
    query.bindValue(":accountNumber", rowData.accountNumber);
    query.bindValue(":numberOfSheets", rowData.numberOfSheets);
    query.bindValue(":dateOfReceipt", rowData.dateOfReceipt);
    //query.bindValue(":receiptSignature", rowData.receiptSignature);
    //query.bindValue(":returnSignature", rowData.returnSignature);
    query.bindValue(":sheetID", rowData.sheetID);
    query.bindValue(":rowNumber", rowData.rowNumber);

    if (!query.exec()) {
        qDebug() << "Error updating line:" << query.lastError().text();
        LOG_WARN("Error updating line:" + query.lastError().text().toStdString());
        return false;
    }
    return true;
}

