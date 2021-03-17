#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),n(0),is_over(false),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("pid="+QString::number(getpid(),10));
    ui->label_2->setText("processing(KB):");
    ui->label_4->setText("running");

    QTimer*timer = new QTimer(this);//flash in a period time
    timer->start(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(Update()));



}
void MainWindow::Update()
{
    if(is_over) ui->label_4->setText("finished");
    ui->label_3->setText(QString::number(n,10));
}
void MainWindow::end()
{
    ui->label_3->setText("END");
}

MainWindow::~MainWindow()
{
    delete ui;
}
