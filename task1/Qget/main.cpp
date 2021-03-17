#include "mainwindow.h"
#include <QApplication>
#include <mythread.h>


int main(int argc, char *argv[])
{
    bool is_over=false;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.move(400,200);
    w.setWindowTitle("get");

    mythread P(atoi(argv[0]),atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),argv[4],w.n,w.is_over);//muti thread
    P.start();


    a.exec();

    return 0;

}
