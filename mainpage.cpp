#include "mainpage.h"
#include "ui_mainpage.h"
#include <QCheckBox>
#include<QLineEdit>
#include<adddialog.h>

MainPage::MainPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
    //设置表格
    Tablemodel = new QStandardItemModel();
    //设置列号
    Tablemodel->setColumnCount(11);
    Tablemodel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8( "序号"));
    Tablemodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("事件ID"));
    Tablemodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("日志名称"));
    Tablemodel->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("发生时间"));
    Tablemodel->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("任务类别"));
    Tablemodel->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("级别"));
    Tablemodel->setHeaderData(6,Qt::Horizontal,QString::fromUtf8("日志来源"));
    Tablemodel->setHeaderData(7,Qt::Horizontal,QString::fromUtf8("事件用户"));
    Tablemodel->setHeaderData(8,Qt::Horizontal,QString::fromUtf8("进程ID"));
    Tablemodel->setHeaderData(9,Qt::Horizontal,QString::fromUtf8("关键字"));
    Tablemodel->setHeaderData(10,Qt::Horizontal,QString::fromUtf8("描述"));
    ui->tableView->setModel(Tablemodel);

    //加载manage文件
    this->ManageLog = new manageLog();



    //设置绘图工具
    GraphScene = new QGraphicsScene();
    ui->graphicsView->setScene(GraphScene);
    GraphScene->addText("你好！");



}

MainPage::~MainPage()
{
    delete Tablemodel;
    delete GraphScene;
    delete this->ManageLog;
}


void MainPage::on_AddButton_clicked()
{
    AddDialog * adddialog;
    adddialog = new AddDialog(this,(manageLog *)(this->ManageLog));
    adddialog->exec();
}
