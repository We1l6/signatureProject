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
