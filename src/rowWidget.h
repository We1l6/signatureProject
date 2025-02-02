#ifndef ROWWIDGET_H
#define ROWWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>

#include "structures/rowData.h"
#include "database/databaseManager.h"

class RowWidget : public QWidget {
Q_OBJECT
public:
    explicit RowWidget(const int index, const int sheetID, const QVector<int> &columnWidths, const int rowHeight, QVBoxLayout* verticalLayout, QWidget *parent = nullptr);

private:
    int m_index = 0;
    QVector<QLineEdit*> m_inputs;
    QPushButton *m_button1 = nullptr;
    QPushButton *m_button2 = nullptr;
    int m_sheetID = 0;
    void resetRowColor();
    void highlightRow();
    void editedRow();

    void button1Pressed();
    void button2Pressed();
};
#endif // ROWWIDGET_H
