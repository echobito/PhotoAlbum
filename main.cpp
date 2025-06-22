#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFile qss(":/style/style.qss");
    if(qss.open(QFile::ReadOnly)){
        qDebug() << "Open qss success";
        QString Style = QLatin1String(qss.readAll());
        a.setStyleSheet(Style);
        qss.close();
    }else{
        qDebug() << "Open qss filed";
        return 0;
    }
    w.setWindowTitle("Album");
    w.showMaximized();
    return a.exec();
}
