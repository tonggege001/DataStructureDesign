#include "adddialog.h"
#include "ui_adddialog.h"


AddDialog::AddDialog(manageLog * Manage_Log) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    this->ManageLog = Manage_Log;
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_buttonBox_accepted()
{

}

void AddDialog::on_buttonBox_rejected()
{

}
