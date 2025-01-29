#include "rowWidget.h"

RowWidget::RowWidget(const int index, const QVector<int> &columnWidths, const int rowHeight, QVBoxLayout* verticalLayout, QWidget *parent) : QWidget(parent) {
    m_index = index;
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
        edit->setMinimumWidth(columnWidths[i]);
        inputs.push_back(edit);
        layout->addWidget(edit);
    }

    QPushButton *button1 = new QPushButton("", this);
    button1->setMinimumWidth(columnWidths[columnWidths.size() - 2]);
    button1->setFixedHeight(rowHeight+1);
    layout->addWidget(button1);

    QPushButton *button2 = new QPushButton("", this);
    button2->setMinimumWidth(columnWidths[columnWidths.size() - 1]);
    button2->setFixedHeight(rowHeight+1);
    layout->addWidget(button2);

    setLayout(layout);

    verticalLayout->addWidget(this);
}

