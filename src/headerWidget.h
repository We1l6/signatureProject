#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVector>
#include <QVBoxLayout>

#define NUMBER_OF_SIGNATURES 2

class HeaderWidget : public QWidget
{
Q_OBJECT
public:
    explicit HeaderWidget(const QStringList &headers, const QVector<int> &columnWidths,const int rowHeight, QVBoxLayout* verticalLayout, QWidget *parent = nullptr);

private:
    QVector<QLabel*> m_labels;
    QPushButton *m_actionButton = nullptr;
    QLabel* createMinimumWidthLabel(const QString &text, int width, int height, const QString &styles);
    QLabel* createFixedWidthLabel(const QString &text, int width, int height, const QString &styles);
};

#endif // HEADERWIDGET_H
