#ifndef QUERIES_H
#define QUERIES_H

#include <QString>

namespace Queries {
    const QString gridTable = ("CREATE TABLE IF NOT EXISTS gridTable ("
                               "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                               "sheet_id INTEGER NOT NULL, "
                               "row_number INTEGER NOT NULL,"
                               "to_whom_issued VARCHAR(32), "
                               "unit VARCHAR(32), "
                               "account_number VARCHAR(32), "
                               "number_of_sheets INTEGER, "
                               "date_of_receipt VARCHAR(16), "
                               "receipt_signature BLOB, "
                               "return_signature BLOB"
                               ");");
}

#endif // QUERIES_H
