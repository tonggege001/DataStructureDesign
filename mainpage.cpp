#include "mainpage.h"
#include "ui_mainpage.h"
#include <QCheckBox>
#include<QLineEdit>
#include<adddialog.h>
#include<vector>
#include<set>
#include<QDateTime>
#include<QMessageBox>
#include<QInputDialog>

MainPage::MainPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
    //设置表格





    Tablemodel = new QStandardItemModel();
    //设置列号
    Tablemodel->setColumnCount(10);
    Tablemodel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("事件ID"));
    Tablemodel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("日志名称"));
    Tablemodel->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("发生时间"));
    Tablemodel->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("任务类别"));
    Tablemodel->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("级别"));
    Tablemodel->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("日志来源"));
    Tablemodel->setHeaderData(6,Qt::Horizontal,QString::fromUtf8("事件用户"));
    Tablemodel->setHeaderData(7,Qt::Horizontal,QString::fromUtf8("进程ID"));
    Tablemodel->setHeaderData(8,Qt::Horizontal,QString::fromUtf8("关键字"));
    Tablemodel->setHeaderData(9,Qt::Horizontal,QString::fromUtf8("描述"));
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

void MainPage::on_QueryButton_clicked()
{
    Tablemodel->removeRows(0,Tablemodel->rowCount());
    vector<int> *SR[5] = {NULL,NULL,NULL,NULL,NULL};
    if(ui->EventIDCheck->isChecked()) SR[0] = ManageLog->searchByID(ui->EventIDEdit->text().toInt());
    if(ui->EventRecordIDCheck->isChecked()) SR[1] = ManageLog->searchByRecordID(ui->EventREdit->text().toInt());
    if(ui->EventTaskCheck->isChecked()) SR[2] = ManageLog->searchByTaskType(ui->EventTaskEdit->text().toInt());
    if(ui->EventUserCheck->isChecked()) SR[3] = ManageLog->searchByUser(ui->EventUserEdit->text().toStdString());
    if(ui->TimeCheck->isChecked()) SR[4] = ManageLog->searchByTime(ui->TimeEditLow->dateTime().toSecsSinceEpoch(),
                                                        ui->TimeEditHigh->dateTime().toSecsSinceEpoch());
    std::set <int>SS;
    for(int i = 0;i<5;i++){
        if(SR[i]==NULL) continue;
        for(int e:*SR[i]){
            SS.insert(e);
        }
        delete SR[i];
    }
    int j = 0;
    for(int e:SS){
        Tablemodel->setItem(j,0,new QStandardItem(QString::number(ManageLog->logs[e]->getID())));
        Tablemodel->setItem(j,1,new QStandardItem(QString::fromStdString(ManageLog->logs[e]->getLogName())));
        QDateTime d;d = QDateTime::fromSecsSinceEpoch(ManageLog->logs[e]->getTime());
        d.setTimeSpec(Qt::LocalTime);
        Tablemodel->setItem(j,2,new QStandardItem(d.toString("yyyy/M/d H:mm")));
        Tablemodel->setItem(j,3,new QStandardItem(QString::number(ManageLog->logs[e]->getTaskType())));
        Tablemodel->setItem(j,4,new QStandardItem(QString::number(ManageLog->logs[e]->getClassType())));
        Tablemodel->setItem(j,5,new QStandardItem(QString::number(ManageLog->logs[e]->getSourceID())));
        Tablemodel->setItem(j,6,new QStandardItem(QString::fromStdString(ManageLog->logs[e]->getUser())));
        Tablemodel->setItem(j,7,new QStandardItem(QString::number(ManageLog->logs[e]->getEventRecordID())));
        Tablemodel->setItem(j,8,new QStandardItem(QString::number(ManageLog->logs[e]->getKeyWord())));
        Tablemodel->setItem(j,9,new QStandardItem(QString::fromStdString(ManageLog->logs[e]->getDescription())));
        j++;
    }
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->resizeColumnsToContents();
}

void MainPage::on_SaveButton_clicked()
{
    if(ManageLog->SaveData()){
        QMessageBox::about(this, "存盘成功", "恭喜，存盘成功！");
    }
    else{
        QMessageBox::about(this, "存盘失败", "错误，存盘失败！");
    }
}



void MainPage::on_pushButton_clicked()
{
    for(int i = 0;i<Tablemodel->rowCount();i++){
        QStandardItem *	item = Tablemodel->item(i,0);
        int id = item->data(0).toInt();
        QDateTime time = QDateTime::fromString(Tablemodel->item(i,2)->data(0).toString(), "yyyy/M/d H:mm");
        ManageLog->modifyLog(id,Tablemodel->item(i,1)->data(0).toString().toStdString(),
                             (int)(time.toSecsSinceEpoch()),Tablemodel->item(i,3)->data(0).toInt(),Tablemodel->item(i,4)->data(0).toInt(),
                             Tablemodel->item(i,5)->data(0).toInt(),Tablemodel->item(i,6)->data(0).toString().toStdString(),
                             Tablemodel->item(i,7)->data(0).toInt(),Tablemodel->item(i,8)->data(0).toInt(),
                             Tablemodel->item(i,9)->data(0).toString().toStdString());

    }
    QMessageBox::about(this, "修改成功", "修改成功，请注意及时存盘哦！");
}

void MainPage::on_action_Delete_ID_triggered()
{
    bool isOK;
    QString text = QInputDialog::getText(this, "输入待删除的ID","请输入待删除的日志ID：",QLineEdit::Normal,"",&isOK);
    if(isOK) {
        if(this->ManageLog->DeleteLog(text.toInt())){
            QMessageBox::about(this, "删除成功！", "删除成功！");
        }
        else{
            QMessageBox::about(this, "删除失败", "删除失败！");
        }
    }
}

void MainPage::on_action_Dleete_RecordID_triggered()
{
    bool isOK;
    QString text = QInputDialog::getText(this, "输入待日志的进程ID","请输入日志的进程ID：",QLineEdit::Normal,"",&isOK);
    if(isOK) {
        if(this->ManageLog->DeleteLogbyRecordID(text.toInt())){
            QMessageBox::about(this, "删除成功！", "删除成功！");
        }
        else{
            QMessageBox::about(this, "删除失败", "删除失败！");
        }
    }
}

void MainPage::on_action_delete_Source_triggered()
{
    bool isOK;
    QString text = QInputDialog::getText(this, "输入待删除的日志源ID","请输入待删除的日志源ID：",QLineEdit::Normal,"",&isOK);
    if(isOK) {
        if(this->ManageLog->DeleteLogbySourceID(text.toInt())){
            QMessageBox::about(this, "删除成功！", "删除成功！");
        }
        else{
            QMessageBox::about(this, "删除失败", "删除失败！");
        }
    }
}
