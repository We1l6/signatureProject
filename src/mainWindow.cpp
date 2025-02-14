#include "mainWindow.h"
#include "src/ui_mainWindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    toolBar = new ToolBarManager(this);
    addToolBar(Qt::TopToolBarArea, toolBar);
    ConfigManager config("config.yaml");
    if (!config.loadConfig())
    {
        qWarning() << "Failed to load config!";
    }
    DatabaseManager::instance().connect("database.db");
    QVector<int> columnWidths = {50, 55, 55, 55, 55, 55, 120, 120};
    QStringList header1;

    header1.push_back(config.getQStringValue("firstColumn", ""));
    header1.push_back(config.getQStringValue("secondColumn", ""));
    header1.push_back(config.getQStringValue("thirdColumn", ""));
    header1.push_back(config.getQStringValue("fourthColumn", ""));
    header1.push_back(config.getQStringValue("fifthColumn", ""));
    header1.push_back(config.getQStringValue("sixthColumn", ""));
    header1.push_back(config.getQStringValue("seventhColumn", ""));
    header1.push_back(config.getQStringValue("eighthColumn", ""));

    QStringList header2 = {"1", "2", "3", "4", "5", "6", "7", "8"};

    HeaderWidget *header1Widget = new HeaderWidget(header1, columnWidths, 70, ui->verticalLayout, this);
    HeaderWidget *header2Widget = new HeaderWidget(header2, columnWidths, 20, ui->verticalLayout, this);
    DatabaseManager& dbManager = DatabaseManager::instance();
    m_sheetID = dbManager.getMaxSheetID();
    m_maxSheetID = m_sheetID;

    setWindowTitle(QString::number(m_sheetID));
    std::vector<Structures::RowData> rowsData = dbManager.fetchRowsBySheetID(m_sheetID);

    for (int i = 0; i < ROW_COUNT; ++i) {
        //dbManager.insertRow(m_sheetID, i);
        RowWidget *row = new RowWidget(i, m_sheetID, columnWidths, 20, ui->verticalLayout, this);
        row->setRowData(rowsData[i]);
        rows.push_back(row);
    }

    QSpacerItem* spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->verticalLayout->addItem(spacer);

    connect(toolBar, &ToolBarManager::leftArrowActionRequested, this, &MainWindow::leftArrowActionRequested);
    connect(toolBar, &ToolBarManager::rightArrowActionRequested, this, &MainWindow::rightArrowActionRequested);
    connect(toolBar, &ToolBarManager::newListActionRequested, this, &MainWindow::newListActionRequested);

}

MainWindow::~MainWindow()
{
    DatabaseManager::instance().disconnect();
    delete toolBar;
    delete ui;
}

void MainWindow::leftArrowActionRequested(){
    if(m_sheetID != 1){
        DatabaseManager& dbManager = DatabaseManager::instance();
        m_sheetID--;
        setWindowTitle(QString::number(m_sheetID));
        std::vector<Structures::RowData> rowsData = dbManager.fetchRowsBySheetID(m_sheetID);

        for (int i = 0; i < ROW_COUNT; ++i) {
            rows[i]->clearRow();
            rows[i]->setRowData(rowsData[i]);
        }
    }
}

void MainWindow::rightArrowActionRequested(){
    if(m_sheetID != m_maxSheetID){
        DatabaseManager& dbManager = DatabaseManager::instance();
        m_sheetID++;
        setWindowTitle(QString::number(m_sheetID));
        std::vector<Structures::RowData> rowsData = dbManager.fetchRowsBySheetID(m_sheetID);

        for (int i = 0; i < ROW_COUNT; ++i) {
            rows[i]->clearRow();
            rows[i]->setRowData(rowsData[i]);
        }
    }
}

void MainWindow::newListActionRequested(){
    DatabaseManager& dbManager = DatabaseManager::instance();
    m_sheetID++;
    setWindowTitle(QString::number(m_sheetID));
    m_maxSheetID = m_sheetID;
    for (int i = 0; i < ROW_COUNT; ++i) {
        dbManager.insertRow(m_sheetID, i);
        rows[i]->clearRow();
        rows[i]->setSheetID(m_sheetID);
    }
}

