#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <QString>

namespace Structures {
    struct RowData {
        int sheetID;
        int rowNumber;
        QString toWhomIssued;
        QString unit;
        QString accountNumber;
        int numberOfSheets;
        QString dateOfReceipt;
    };
}

#endif // STRUCTURES_H
