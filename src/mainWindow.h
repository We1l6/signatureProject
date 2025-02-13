#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "headerWidget.h"
#include "rowWidget.h"
#include "database/databaseManager.h"
#include "config/configManager.h"
#include "toolBar/toolBarManager.h"

#define ROW_COUNT 49

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    void rightArrowActionRequested();
    void leftArrowActionRequested();
    void newListActionRequested();

    Ui::MainWindow *ui;
    QVector<RowWidget*> rows;
    int m_sheetID = 1;
    ToolBarManager* toolBar = nullptr;
};
#endif // MAINWINDOW_H
