#include "mainWindow.h"

#include <QApplication>
#include "spdlog/spdlog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);
    MainWindow w;
    w.show();
    return a.exec();
}
