#include "headerWidget.h"

HeaderWidget::HeaderWidget(const QStringList &headers,const QVector<int> &columnWidths, int rowHeight, QVBoxLayout* verticalLayout, QWidget *parent) : QWidget(parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    for (int i = 0; i < headers.size(); ++i) {
        QLabel *label = new QLabel(headers[i], this);
        label->setAlignment(Qt::AlignCenter);
        label->setMinimumWidth(columnWidths[i]);
        label->setStyleSheet("QLabel { "
                             "border: 1px solid black;"
                             "font-size: 16px;"
                             "font-weight: bold;"
                             "}");
        label->setFixedHeight(rowHeight);
        m_labels.push_back(label);
        layout->addWidget(label);
    }

    setLayout(layout);

    verticalLayout->addWidget(this);
}
