#ifndef ROWWIDGET_H
#define ROWWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class RowWidget : public QWidget {
Q_OBJECT
public:
    explicit RowWidget(const int index, const QVector<int> &columnWidths, const int rowHeight, QVBoxLayout* verticalLayout, QWidget *parent = nullptr);

private:
    int m_index = 0;
    QVector<QLineEdit*> inputs;
};
#endif // ROWWIDGET_H
