#ifndef MAINPAGE_H
#define MAINPAGE_H
#include <QMainWindow>
#include"src/managelog.h"
#include"QStandardItemModel"
#include<QPushButton>
#include<QGraphicsScene>

namespace Ui {
class MainPage;
}

class MainPage : public QMainWindow
{
    Q_OBJECT

public:
    manageLog * ManageLog;
    QStandardItemModel * Tablemodel;//日志操作的Model
    QGraphicsScene * GraphScene;
    explicit MainPage(QWidget *parent = 0);
    ~MainPage();

private slots:

    void on_AddButton_clicked();

private:
    Ui::MainPage *ui;
};

#endif // MAINPAGE_H
