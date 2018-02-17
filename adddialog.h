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
    LOG::manageLog * ManageLog;
     AddDialog(LOG::manageLog * Manage_Log);
    ~AddDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
