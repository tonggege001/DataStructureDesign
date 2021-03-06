#ifndef MAINPAGE_H
#define MAINPAGE_H
#include <QMainWindow>
#include"src/managelog.h"
#include"src/managegraph.h"
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
    manageLog * ManageLog;//管理LOG
    manageGraph * ManageGraph;//管理图
    QStandardItemModel * Tablemodel;//日志操作的Model
    QGraphicsScene * GraphScene;//作图类
    explicit MainPage(QWidget *parent = 0);
    ~MainPage();

private slots:

    void on_AddButton_clicked();

    void on_QueryButton_clicked();

    void on_SaveButton_clicked();

    void on_pushButton_clicked();

    void on_action_Delete_ID_triggered();

    void on_action_Dleete_RecordID_triggered();

    void on_action_delete_Source_triggered();

    void on_GraphQuery_clicked();

    void on_GraphUpdate_clicked();

    void on_GraphClear_clicked();

    void on_Analysis_clicked();

    void on_clear_Button_clicked();

    void on_Save_Button_clicked();

private:
    Ui::MainPage *ui;
};

#endif // MAINPAGE_H
