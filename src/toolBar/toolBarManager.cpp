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


    addAction(leftArrow);
    addAction(rightArrow);
    addAction(newList);
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

