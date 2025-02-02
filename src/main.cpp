#include "mainWindow.h"
#include <QApplication>
#include "database/databaseManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    DatabaseManager::instance().connect("database.db");
<<<<<<< HEAD
=======
    DatabaseManager::instance().disconnect();
>>>>>>> 4051ed4ad24336f7ab2eff9e1af3d22d0868d872
    w.show();
    return a.exec();
    DatabaseManager::instance().disconnect();
}
