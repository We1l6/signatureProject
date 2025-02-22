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
    rowsData = dbManager.fetchRowsBySheetID(m_sheetID);

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
    connect(toolBar, &ToolBarManager::createCurrentListActionRequested, this, &MainWindow::createCurrentListActionRequested);
    connect(toolBar, &ToolBarManager::createAlltListsActionRequested, this, &MainWindow::createAlltListsActionRequested);
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

void MainWindow::createCurrentListActionRequested() {
    QString folderPath = QFileDialog::getExistingDirectory(
        nullptr,
        "Select a folder",
        QDir::homePath()
        );

    if (folderPath.isEmpty()) {
        qWarning() << "Folder not selected.";
        return;
    }

    DatabaseManager& dbManager = DatabaseManager::instance();
    rowsData = dbManager.fetchRowsBySheetID(m_sheetID);

    if (rowsData.empty()) {
        qWarning() << "No data found for sheet ID:" << m_sheetID;
        return;
    }

    QDir().mkpath("temp");  // Убедимся, что папка temp существует

    QString htmlPath = "temp/output.html";
    TemplateRenderer templateRenderer;
    templateRenderer.fillHTMLfile("list.html", htmlPath, rowsData);

    QString pdfTempPath = "temp/output.pdf";
    PrintManager printManager;
    printManager.convertHtmlToPdf(htmlPath, pdfTempPath);

    if (!QFile::exists(pdfTempPath)) {
        qWarning() << "Error: PDF file was not created!";
        return;
    }

    QString finalPdfPath = folderPath + "/output.pdf";
    if (QFile::exists(finalPdfPath)) {
        QFile::remove(finalPdfPath);
    }

    if (QFile::rename(pdfTempPath, finalPdfPath)) {
        qDebug() << "PDF successfully moved to:" << finalPdfPath;
    } else {
        qWarning() << "Failed to move PDF. Trying to copy.";
        if (QFile::copy(pdfTempPath, finalPdfPath)) {
            QFile::remove(pdfTempPath);
            qDebug() << "PDF successfully copied to:" << finalPdfPath;
        } else {
            qWarning() << "Error copying PDF to:" << finalPdfPath;
        }
    }
}


void MainWindow::createAlltListsActionRequested() {
    QString folderPath = QFileDialog::getExistingDirectory(
        nullptr,
        "Select a folder",
        QDir::homePath()
        );

    if (folderPath.isEmpty()) {
        qWarning() << "Folder not selected.";
        return;
    }

    DatabaseManager& dbManager = DatabaseManager::instance();
    TemplateRenderer templateRenderer;
    QStringList htmlFiles;
    std::vector<std::vector<Structures::RowData>> allRows = dbManager.fetchAllRowsGroupedBySheet();

    QDir().mkpath("temp");

    for (int i = 0; i < allRows.size(); ++i) {
        QString outputHtmlPath = "temp/alloutput" + QString::number(i) + ".html";
        templateRenderer.fillHTMLfile("list.html", outputHtmlPath, allRows[i]);
        htmlFiles.push_back(outputHtmlPath);
    }

    PrintManager printManager;
    QString tempPdfPath = "temp/alloutput.pdf";
    printManager.convertMultipleHtmlToPdf(htmlFiles, tempPdfPath);

    QString finalPdfPath = folderPath + "/alloutput.pdf";
    if (QFile::exists(finalPdfPath)) {
        QFile::remove(finalPdfPath);
    }

    if (QFile::rename(tempPdfPath, finalPdfPath)) {
        qDebug() << "PDF successfully moved to:" << finalPdfPath;
    } else {
        qWarning() << "Failed to move PDF. Let's try copying.";
        if (QFile::copy(tempPdfPath, finalPdfPath)) {
            QFile::remove(tempPdfPath);
            qDebug() << "PDF successfully copied to:" << finalPdfPath;
        } else {
            qWarning() << "Error copying PDF to:" << finalPdfPath;
        }
    }
}
