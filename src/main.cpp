#include "mainWindow.h"
#include <QApplication>
#include "database/databaseManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //DatabaseManager::instance().connect("database.db");
    //DatabaseManager::instance().disconnect();
    w.show();
    return a.exec();
}
