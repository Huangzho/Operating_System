#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),n(0),is_over(false),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("pid="+QString::number(getpid(),10));
    ui->label_2->setText("processing(KB):");
    ui->over->setText("running");


    QTimer*timer = new QTimer(this);//flash in a period time

    connect(timer,SIGNAL(timeout()),this,SLOT(Update()));
    timer->start(1000);
}
void MainWindow::Update(void)
{

    if(is_over) ui->over->setText("finished");
    ui->label_3->setText(QString::number(n,10));
}

MainWindow::~MainWindow()
{
    delete ui;
}
