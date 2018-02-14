#include "mainpage.h"
#include <QApplication>
#include<QFile>
#include <QTextCodec>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss("style.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();



    MainPage w;
    w.show();

    return a.exec();
}
