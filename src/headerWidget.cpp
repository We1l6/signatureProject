#include "headerWidget.h"

HeaderWidget::HeaderWidget(const QStringList &headers,const QVector<int> &columnWidths, int rowHeight, QVBoxLayout* verticalLayout, QWidget *parent) : QWidget(parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    QString styles = ("QLabel { "
                      "border: 1px solid black;"
                      "font-size: 16px;"
                      "font-weight: bold;"
                      "}");

    QLabel *label = createFixedWidthLabel(headers[0], columnWidths[0], rowHeight, styles);
    m_labels.push_back(label);
    layout->addWidget(label);

    for (int i = 1; i < headers.size() - NUMBER_OF_SIGNATURES; ++i) {
        QLabel *label = createMinimumWidthLabel(headers[i], columnWidths[i], rowHeight, styles);
        m_labels.push_back(label);
        layout->addWidget(label);
    }

    for(size_t i = 0; i < NUMBER_OF_SIGNATURES; ++i) {
        QLabel *label = createFixedWidthLabel(headers[headers.size()- NUMBER_OF_SIGNATURES + i], columnWidths[headers.size()- NUMBER_OF_SIGNATURES + i], rowHeight, styles);
        m_labels.push_back(label);
        layout->addWidget(label);
    }

    verticalLayout->addWidget(this);
}

QLabel* HeaderWidget::createMinimumWidthLabel(const QString &text, int width, int height, const QString &styles)
{
    QLabel *label = new QLabel(text, this);
    label->setAlignment(Qt::AlignCenter);
    label->setMinimumWidth(width);
    label->setStyleSheet(styles);
    label->setFixedHeight(height);
    return label;
}


QLabel* HeaderWidget::createFixedWidthLabel(const QString &text, int width, int height, const QString &styles)
{
    QLabel *label = new QLabel(text, this);
    label->setAlignment(Qt::AlignCenter);
    label->setFixedWidth(width);
    label->setStyleSheet(styles);
    label->setFixedHeight(height);
    return label;
}
