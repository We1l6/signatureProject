#include "mainWindow.h"
#include "src/ui_mainWindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVector<int> columnWidths = {50, 55, 55, 55, 55, 55, 120, 120};
    LOG_INFO("sdfsdfsdfsdfsdfs");
    QStringList header1 = {"№ з/п", "Кому видано", "Підрозділ", "Обліковий\nномер", "Кількість\nаркушів",
                           "Дата\nотримання", "Підпис про\nотримання", "Підпис про\nзворотний\nприйом, дата"};

    QStringList header2 = {"1", "2", "3", "4", "5", "6", "7", "8"};

    HeaderWidget *header1Widget = new HeaderWidget(header1, columnWidths, 70, ui->verticalLayout, this);
    HeaderWidget *header2Widget = new HeaderWidget(header2, columnWidths, 20, ui->verticalLayout, this);


    for (int i = 0; i < 49; ++i) {
        RowWidget *row = new RowWidget(i + 1, columnWidths, 20, ui->verticalLayout, this);
        rows.push_back(row);
    }

    QSpacerItem* spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->verticalLayout->addItem(spacer);
}

MainWindow::~MainWindow()
{
    delete ui;
}
