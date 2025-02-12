#ifndef TOOLBARMANAGER_H
#define TOOLBARMANAGER_H
#include<QToolBar>

class ToolBarManager : public QToolBar
{
    Q_OBJECT
public:
    explicit ToolBarManager(QWidget *parent = nullptr);

signals:
    void leftArrowActionRequested();
    void rightArrowActionRequested();

private slots:
    void leftArrowActionTriggered();
    void rightArrowActionTriggered();
};

#endif // TOOLBARMANAGER_H
