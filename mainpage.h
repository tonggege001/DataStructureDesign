#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QMainWindow>
#include"QStandardItemModel"
#include "src/manage.h"
#include<QPushButton>

using namespace LOG;
namespace Ui {
class MainPage;
}

class MainPage : public QMainWindow
{
    Q_OBJECT

public:
    LOG::manage *Manage;
    QStandardItemModel * Tablemodel;
    explicit MainPage(QWidget *parent = 0);
    ~MainPage();

private slots:

private:
    Ui::MainPage *ui;
};

#endif // MAINPAGE_H
