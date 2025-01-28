#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVector>
#include <QVBoxLayout>

class HeaderWidget : public QWidget
{
Q_OBJECT
public:
    explicit HeaderWidget(const QStringList &headers,const QVector<int> &columnWidths, int rowHeight, QVBoxLayout* verticalLayout, QWidget *parent = nullptr);

private:
    QVector<QLabel*> m_labels;
    QPushButton *m_actionButton = nullptr;
};

#endif // HEADERWIDGET_H
