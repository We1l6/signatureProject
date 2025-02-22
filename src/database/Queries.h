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

    const QString updategridTable = ("UPDATE gridTable SET "
                            "to_whom_issued = :toWhomIssued, "
                            "unit = :unit, "
                            "account_number = :accountNumber, "
                            "number_of_sheets = :numberOfSheets, "
                            "date_of_receipt = :dateOfReceipt, "
                            "receipt_signature = :firstSign, "
                            "return_signature = :secondSign "
                            "WHERE sheet_id = :sheetID AND row_number = :rowNumber");

    const QString insertIntoGridTable = ("INSERT INTO gridTable (sheet_id, row_number) VALUES (:sheetID, :rowNumber)");

    const QString selectFromGridTable = ("SELECT sheet_id, row_number, to_whom_issued, unit, account_number, number_of_sheets, date_of_receipt, receipt_signature, return_signature "
                                         "FROM gridTable WHERE sheet_id = :sheetID");

    const QString selectAllFromGridTable = ("SELECT sheet_id, row_number, to_whom_issued, unit, account_number, number_of_sheets, date_of_receipt, receipt_signature, return_signature "
                                            "FROM gridTable");
}

#endif // QUERIES_H
