#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    int N=10,size=2050;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.move(200,200);
    int shmid,semid;
        pid_t p1,p2;

        char str_N[20],str_size[20],str_shmid[20],str_semid[20];
        shmid=shmget(IPC_PRIVATE,N*size,IPC_CREAT|0666);//创建缓冲区
        semid=semget(IPC_PRIVATE,2,0666);//创建信号灯

        sprintf(str_N,"%d",N);//向get与put传递信息
        sprintf(str_size,"%d",size);
        sprintf(str_shmid,"%d",shmid);
        sprintf(str_semid,"%d",semid);

        semctl(semid,0,SETVAL,N);//写信号灯赋值
        semctl(semid,1,SETVAL,0);//读
        p1=fork();
        if(!p1){//子进程1，get写缓冲区
            execl("./Qget",str_N,str_size,str_shmid,str_semid,argv[1],NULL);
        }
        else{
            p2=fork();
            if(!p2){//子进程2，put读缓冲区
                execl("./Qput",str_N,str_size,str_shmid,str_semid,argv[2],NULL);
            }
            else{
                a.exec();
                wait(NULL);//等待子进程结束
                wait(NULL);
                semctl(semid,0,IPC_RMID);//关闭信号灯
                shmctl(shmid,IPC_RMID,0);//关闭缓冲区
                return 0;
            }
        }
}
