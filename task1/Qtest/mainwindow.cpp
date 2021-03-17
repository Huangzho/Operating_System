#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("pid="+QString::number(getpid(),10));
    ui->label_2->setText("running");
    QTimer* timer=new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(Update()));
    timer->start(1000);

}

void MainWindow::Update()
{

    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy_mm_dd hh:mm:ss dddd");
    ui->label_2->setText(str);

}

MainWindow::~MainWindow()
{
    delete ui;
}
