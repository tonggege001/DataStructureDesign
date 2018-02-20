#include "adddialog.h"
#include "ui_adddialog.h"
#include <QMessageBox>
#include<src/eventlog.h>
#include<src/managelog.h>

AddDialog::AddDialog(QWidget *parent,manageLog *manage_log) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    this->ManageLog = manage_log;
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_buttonBox_accepted(){ 
    if(ui->EventIDEdit->text()==""){
        QMessageBox::about(this, "警告", "警告：请输入日志ID！");
    }
    else if(ui->LogNameEdit->text()==""){
        QMessageBox::about(this, "警告", "警告：请输入日志名称！");
    }
    else if(ui->ClassTypeEdit->text()==""){
        QMessageBox::about(this, "警告", "警告：请输入级别！");
    }
    else if(ui->DescriptionEdit->text()==""){
        QMessageBox::about(this, "警告", "警告：请输入日志描述！");
    }
    else if(ui->EventRecordEdit->text()==""){
        QMessageBox::about(this, "警告", "警告：请输入日志进程！");
    }
    else if(ui->KeyWordEdit->text()==""){
        QMessageBox::about(this, "警告", "警告：请输入关键字！");
    }
    else if(ui->SourceIDEdit->text()==""){
        QMessageBox::about(this, "警告", "警告：请输入日志来源！");
    }
    else if(ui->TaskTypeEdit->text()==""){
        QMessageBox::about(this, "警告", "警告：请输入日志类别！");
    }
    else if(ui->UserEdit->text()==""){
        QMessageBox::about(this, "警告", "警告：请输入调用者！");
    }
    else{
        EventLog * log = new EventLog(ui->LogNameEdit->text().toStdString(),ui->SourceIDEdit->text().toInt(), ui->OccurTimeEdit->dateTime().toSecsSinceEpoch(),
                                                     ui->EventIDEdit->text().toInt(),ui->TaskTypeEdit->text().toInt(),
                                                     ui->ClassTypeEdit->text().toInt(),ui->UserEdit->text().toStdString(),
                                                     ui->EventRecordEdit->text().toInt(),ui->KeyWordEdit->text().toInt(),
                                                     ui->DescriptionEdit->text().toStdString());
        if(this->ManageLog->AddLog(log)){
            QMessageBox::about(this, "添加成功", "恭喜！添加成功");
            ui->EventIDEdit->setText("");ui->LogNameEdit->setText("");ui->SourceIDEdit->setText("");
            ui->ClassTypeEdit->setText("");ui->TaskTypeEdit->setText("");ui->DescriptionEdit->setText("");
            ui->UserEdit->setText("");ui->EventRecordEdit->setText("");ui->KeyWordEdit->setText("");
        }
        else {
            QMessageBox::about(this, "错误", "该ID已有事件！");
        }
    }
    return this->show();
}

void AddDialog::on_buttonBox_rejected()
{
    this->destroy();
}
