#include "mainWindow.h"
#include "src/ui_mainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVector<int> columnWidths = {55, 55, 55, 55, 55, 55, 55, 55};

    QStringList header1 = {"№ з/п", "Кому видано", "Підрозділ", "Обліковий\nномер", "Кількість\nаркушів",
                           "Дата\nотримання", "Підпис про\nотримання", "Підпис про\nзворотний\nприйом, дата"};

    QStringList header2 = {"1", "2", "3", "4", "5", "6", "7", "8"};

    HeaderWidget *header1Widget = new HeaderWidget(header1, columnWidths, 70, ui->verticalLayout, this);
    HeaderWidget *header2Widget = new HeaderWidget(header2, columnWidths, 20, ui->verticalLayout, this);

    QSpacerItem* spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->verticalLayout->addItem(spacer);
}

MainWindow::~MainWindow()
{
    delete ui;
}
