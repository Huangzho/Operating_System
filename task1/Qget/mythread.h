#ifndef MYTHREAD_H
#define MYTHREAD_H
#include<QThread>
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

class mythread : public QThread
{
public:
    mythread(int a,int b,int c,int d,char *e,long &x,bool& y);
    int N,size,shmid,semid;
    char *file;
    long &n;
    bool &is_over;
protected:
    void run();


};

#endif // MYTHREAD_H
