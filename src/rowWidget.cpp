#include "rowWidget.h"

RowWidget::RowWidget(const int index, const int sheetID, const QVector<int> &columnWidths, const int rowHeight, QVBoxLayout* verticalLayout, QWidget *parent) : QWidget(parent) {
    m_index = index;
    m_sheetID = sheetID;
    QString styles = ("QLabel { "
                      "border: 1px solid black;"
                      "font-size: 12px;"
                      "}");

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    QLabel *label = new QLabel(QString::number(index), this);
    label->setMinimumWidth(columnWidths[0]);
    label->setStyleSheet(styles);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    for (int i = 1; i < columnWidths.size() - 2; ++i) {
        QLineEdit *edit = new QLineEdit(this);
        connect(edit, &QLineEdit::textEdited, this, &RowWidget::highlightRow);
        connect(edit, &QLineEdit::editingFinished, this, &RowWidget::resetRowColor);
        connect(edit, &QLineEdit::editingFinished, this, &RowWidget::editedRow);
        edit->setMinimumWidth(columnWidths[i]);
        m_inputs.push_back(edit);
        layout->addWidget(edit);
    }

    m_button1 = new QPushButton("", this);
    connect(m_button1, &QPushButton::clicked, this, &RowWidget::button1Pressed);
    m_button1->setMinimumWidth(columnWidths[columnWidths.size() - 2]);
    m_button1->setFixedHeight(rowHeight+1);
    layout->addWidget(m_button1);

    m_button2 = new QPushButton("", this);
    connect(m_button2, &QPushButton::clicked, this, &RowWidget::button2Pressed);
    m_button2->setMinimumWidth(columnWidths[columnWidths.size() - 1]);
    m_button2->setFixedHeight(rowHeight+1);
    layout->addWidget(m_button2);

    setLayout(layout);

    verticalLayout->addWidget(this);
}

void RowWidget::resetRowColor()
{
    for (int column = 0; column < m_inputs.size(); ++column) {
        m_inputs[column]->setStyleSheet("QLineEdit { background-color: white;}");
    }
}

void RowWidget::highlightRow()
{
    for (int column = 0; column < m_inputs.size(); ++column) {
        m_inputs[column]->setStyleSheet("QLineEdit { background-color: yellow;}");
    }
}

void RowWidget::button1Pressed(){

}

void RowWidget::button2Pressed(){

}

void RowWidget::editedRow(){
    DatabaseManager& dbManager = DatabaseManager::instance();
    Structures::RowData row;

    row.toWhomIssued = m_inputs[0]->text();
    row.unit = m_inputs[1]->text();
    row.accountNumber = m_inputs[2]->text();
    row.numberOfSheets = m_inputs[3]->text().toInt();
    row.dateOfReceipt = m_inputs[4]->text();

    row.sheetID = m_sheetID;
    row.rowNumber = m_index;

    dbManager.updateRowData(row);
}

void RowWidget::setRowData(Structures::RowData rowData){
    m_inputs[0]->setText(rowData.toWhomIssued);
    m_inputs[1]->setText(rowData.unit);
    m_inputs[2]->setText(rowData.accountNumber);
    m_inputs[3]->setText(QString::number(rowData.numberOfSheets));
    m_inputs[4]->setText(rowData.dateOfReceipt);
}
