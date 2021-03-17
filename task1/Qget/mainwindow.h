#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <sys/types.h>
#include <unistd.h>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    long n;
    bool is_over;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void Update();
    void end();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H