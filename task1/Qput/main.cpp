#include "mainwindow.h"
#include<mythread.h>
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("put");
    w.show();
    w.move(800,200);
    mythread P(atoi(argv[0]),atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),argv[4],w.n,w.is_over);
    P.start();


    return a.exec();

}


