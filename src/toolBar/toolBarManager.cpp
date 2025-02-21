#include "toolBarManager.h"

ToolBarManager::ToolBarManager(QWidget *parent) : QToolBar(parent) {
    setObjectName("toolbar");

    QAction *leftArrow = new QAction(QIcon("img/left.png"), tr("ліворуч"), this);
    leftArrow->setShortcut(QKeySequence::Open);
    connect(leftArrow, &QAction::triggered, this, &ToolBarManager::leftArrowActionTriggered);

    QAction *rightArrow = new QAction(QIcon("img/right.png"), tr("праворуч"), this);
    rightArrow->setShortcut(QKeySequence::Open);
    connect(rightArrow, &QAction::triggered, this, &ToolBarManager::rightArrowActionTriggered);

    QAction *newList = new QAction(QIcon(""), tr("Новий лист"), this);
    newList->setShortcut(QKeySequence::Open);
    connect(newList, &QAction::triggered, this, &ToolBarManager::newListActionTriggered);


    QAction *createCurrentList = new QAction(QIcon(""), tr("Надрукувати поточний лист"), this);
    newList->setShortcut(QKeySequence::Open);
    connect(createCurrentList, &QAction::triggered, this, &ToolBarManager::createCurrentListActionTriggered);

    QAction *createAlltLists = new QAction(QIcon(""), tr("Надрукувати усі листи"), this);
    newList->setShortcut(QKeySequence::Open);
    connect(createAlltLists, &QAction::triggered, this, &ToolBarManager::createAlltListsActionTriggered);

    addAction(leftArrow);
    addAction(rightArrow);
    addAction(newList);
    addAction(createCurrentList);
    addAction(createAlltLists);
}

void ToolBarManager::leftArrowActionTriggered()
{
    emit leftArrowActionRequested();
}

void ToolBarManager::rightArrowActionTriggered()
{
    emit rightArrowActionRequested();
}

void ToolBarManager::newListActionTriggered()
{
    emit newListActionRequested();
}

void ToolBarManager::createCurrentListActionTriggered()
{
    emit createCurrentListActionRequested();
}

void ToolBarManager::createAlltListsActionTriggered(){
    emit createAlltListsActionRequested();
}
