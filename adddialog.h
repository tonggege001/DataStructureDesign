#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include<src/managelog.h>
namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    manageLog * ManageLog;//管理LOG类
     AddDialog(QWidget *parent,manageLog * manage_log);
    ~AddDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
