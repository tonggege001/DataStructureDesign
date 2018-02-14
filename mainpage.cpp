#include "mainpage.h"
#include "ui_mainpage.h"
#include"QVBoxLayout"
#include"QHBoxLayout"
#include <QCheckBox>
#include<QLineEdit>

using namespace LOG;


MainPage::MainPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
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
}

MainPage::~MainPage()
{

}

