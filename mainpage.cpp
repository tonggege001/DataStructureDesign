
       #include "mainpage.h"
#include "ui_mainpage.h"
#include <QCheckBox>
#include<QLineEdit>
#include<adddialog.h>
#include<vector>
#include<set>
#include<map>
#include<QDateTime>
#include<QMessageBox>
#include<QInputDialog>
#include"src/managegraph.h"
#include"tools/gnode.h"
#include"tools/tool.h"

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
    this->ManageGraph = new manageGraph(this->ManageLog);


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
    delete this->ManageGraph;
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
        Tablemodel->setItem(j,2,new QStandardItem(d.toString("yyyy/M/d H:mm:ss")));
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
        QDateTime time = QDateTime::fromString(Tablemodel->item(i,2)->data(0).toString(), "yyyy/M/d H:mm:ss");
        time.setTimeSpec(Qt::LocalTime);
        ManageLog->modifyLog(id,Tablemodel->item(i,1)->data(0).toString().toStdString(),Tablemodel->item(i,5)->data(0).toInt(),
                             (int)(time.toSecsSinceEpoch()),Tablemodel->item(i,3)->data(0).toInt(),Tablemodel->item(i,4)->data(0).toInt(),
                             Tablemodel->item(i,6)->data(0).toString().toStdString(),
                             Tablemodel->item(i,7)->data(0).toInt(),Tablemodel->item(i,8)->data(0).toInt(),
                             Tablemodel->item(i,9)->data(0).toString().toStdString());

    }
    QMessageBox::about(this, "修改成功", "修改成功，请注意及时存盘哦！");
}

void MainPage::on_action_Delete_ID_triggered()
{
    bool isOK;
    QString text = QInputDialog::getText(this, "输入待删除的ID","请输入待删除的日志ID：",QLineEdit::Normal,"",&isOK);
  //  QMessageBox::about(NULL,text,text);
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



void MainPage::on_GraphQuery_clicked()
{
    //初始时先把上一次的作图残留释放
    QGraphicsScene * scene = this->GraphScene;
    scene->clear();

    manageGraph * ManageGraph = this->ManageGraph;
    if(ManageGraph->GraphCount()==0){
        QMessageBox::about(this,"提示","数据中没有图文件，请点击右侧“更新”按钮！");
        return ;
    }
    //如果查询到
    int type;EventGraph * G;
    if(ui->SubRadio->isChecked()){
        G = ManageGraph->findGraph(ui->IndexEdit->text().toInt(),type = LOG::GraphType::Subject);
    }
    if(ui->ObjRadio->isChecked()){
        G = ManageGraph->findGraph(ui->IndexEdit->text().toInt(),type = LOG::GraphType::Object);
    }
    if(ui->AccomRadio->isChecked()){
        G = ManageGraph->findGraph(ui->IndexEdit->text().toInt(),type = LOG::GraphType::AccomEvent);

    }
    if(ui->CAERadio->isChecked()){
        G = ManageGraph->findGraph(ui->IndexEdit->text().toInt(),type = LOG::GraphType::CauseAndEffect);
    }
    if(!G){
        QMessageBox::about(this,"提示","图不存在！");
        return ;
    }
    if(type!=LOG::GraphType::CauseAndEffect) this->ManageGraph->DrawGraph(scene, G,type);
    else{
        this->ManageGraph->DrawGraphCE(scene,G,ui->IndexEdit->text().toInt());
    }

}

void MainPage::on_GraphUpdate_clicked()
{
    //首先删除所有的图
    ManageGraph->deleteAllGraph();
    //其次产生新的图

    for(int i = 0;i<ManageLog->size;i++){
        //该事件不存在，则进行下一个
        if(ManageLog->logs[i]==NULL) continue;
        //如果事件存在，且没有形成图，则产生一个这样的图；
        if(!ManageGraph->hasGraph(ManageLog->logs[i]->getID(),LOG::GraphType::Subject)){
            EventGraph * g = ManageGraph->generateGraph(ManageLog->logs[i]->getID(),LOG::GraphType::Subject);
            ManageGraph->addGraph(g);
        }
        if(!ManageGraph->hasGraph(ManageLog->logs[i]->getID(),LOG::GraphType::Object)){
            EventGraph * g = ManageGraph->generateGraph(ManageLog->logs[i]->getID(),LOG::GraphType::Object);
            ManageGraph->addGraph(g);
        }
        if(!ManageGraph->hasGraph(ManageLog->logs[i]->getID(),LOG::GraphType::AccomEvent)){
            EventGraph * g = ManageGraph->generateGraph(ManageLog->logs[i]->getID(),LOG::GraphType::AccomEvent);
            ManageGraph->addGraph(g);
        }
        if(!ManageGraph->hasGraph(ManageLog->logs[i]->getID(),LOG::GraphType::CauseAndEffect)){
            EventGraph * g = ManageGraph->generateGraph(ManageLog->logs[i]->getID(),LOG::GraphType::CauseAndEffect);
            ManageGraph->addGraph(g);
        }
    }
    this->ManageGraph->SaveGraph();
}

void MainPage::on_GraphClear_clicked()
{
    this->GraphScene->clear();
}

void MainPage::on_Analysis_clicked()
{
    if(!(ui->LogNameE->text()!=""&&ui->TaskTypeE->text()!=""&&ui->ClassTypeE->text()!=""&&
            ui->KeyWordE->text()!=""&&ui->SourceIDE->text()!=""&&ui->UserE->text()!=""&&
         ui->EventRecordE->text()!=""&&ui->DescriptionE->text()!="")){
        QMessageBox::about(this,"提示","信息不完整，请补充完整！");
        return;
    }
    EventLog * log = new EventLog(999);
    log->setLogName(ui->LogNameE->text().toStdString());
    log->setTaskType(ui->TaskTypeE->text().toInt());
    log->setClassType(ui->ClassTypeE->text().toInt());
    log->setKeyWord(ui->KeyWordE->text().toInt());
    log->setSourceID(ui->SourceIDE->text().toInt());
    log->setUser(ui->UserE->text().toStdString());
    log->setTime(ui->OccurTimeE->dateTime().toSecsSinceEpoch());
    log->setEventRecordID(ui->EventRecordE->text().toInt());
    log->setDescription(ui->DescriptionE->text().toStdString());

    QString s = ResultStr(this->ManageGraph,this->ManageLog,log);
    delete log;
    if(s==""){
        QMessageBox::about(this,"提示","没有相似的事件！");
        ui->ResuleLabel->setPlainText("分析失败，系统中没有相似的事件！");
    }
    else{
        ui->ResuleLabel->setPlainText(s);
    }
    return;
}

void MainPage::on_clear_Button_clicked()
{
    ui->LogNameE->setText("");
    ui->TaskTypeE->setText("");
    ui->ClassTypeE->setText("");
    ui->KeyWordE->setText("");
    ui->SourceIDE->setText("");
    ui->UserE->setText("");
    ui->EventRecordE->setText("");
    ui->DescriptionE->setText("");
}

void MainPage::on_Save_Button_clicked()
{
    if(!(ui->LogNameE->text()!=""&&ui->TaskTypeE->text()!=""&&ui->ClassTypeE->text()!=""&&
            ui->KeyWordE->text()!=""&&ui->SourceIDE->text()!=""&&ui->UserE->text()!=""&&
         ui->EventRecordE->text()!=""&&ui->DescriptionE->text()!="")){
        QMessageBox::about(this,"提示","信息不完整，请补充完整！");
        return;
    }
    QString str = QInputDialog::getText(this,"输入新日志的ID","请输入新日志的ID：");
    int ID = str.toInt();
    EventLog * log = new EventLog(ID);
    log->setLogName(ui->LogNameE->text().toStdString());
    log->setTaskType(ui->TaskTypeE->text().toInt());
    log->setClassType(ui->ClassTypeE->text().toInt());
    log->setKeyWord(ui->KeyWordE->text().toInt());
    log->setSourceID(ui->SourceIDE->text().toInt());
    log->setUser(ui->UserE->text().toStdString());
    log->setTime(ui->OccurTimeE->dateTime().toSecsSinceEpoch());
    log->setEventRecordID(ui->EventRecordE->text().toInt());
    log->setDescription(ui->DescriptionE->text().toStdString());
    this->ManageLog->AddLog(log);
    QMessageBox::about(this,"添加成功","添加成功，请及时存盘！");
}













