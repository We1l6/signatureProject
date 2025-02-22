#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "headerWidget.h"
#include "rowWidget.h"
#include "database/databaseManager.h"
#include "config/configManager.h"
#include "toolBar/toolBarManager.h"
#include <fstream>
#include "printManager/printManager.h"
#include "printManager/templateRenderer.h"
#include <QFileDialog>

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
    void createCurrentListActionRequested();
    void createAlltListsActionRequested();

    Ui::MainWindow *ui;
    std::vector<RowWidget*> rows;
    int m_sheetID = 1;
    int m_maxSheetID = 1;
    ToolBarManager* toolBar = nullptr;
    std::vector<Structures::RowData> rowsData;
};
#endif // MAINWINDOW_H
