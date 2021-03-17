#include "mythread.h"
void P(int semid,unsigned short index)//PV操作
{
    struct sembuf sem;
    sem.sem_num=index;
    sem.sem_op=-1;
    sem.sem_flg=0;
    semop(semid,&sem,1);
}
void V(int semid,unsigned short index)
{
    struct sembuf sem;
    sem.sem_num=index;
    sem.sem_op=1;
    sem.sem_flg=0;
    semop(semid,&sem,1);
}
mythread::mythread(int a,int b,int c,int d,char *e,long &x,bool& y):n(x),is_over(y)
{
    N=a;
    size=b;
    shmid=c;
    semid=d;
    file=e;
}
void mythread::run()
{
        int i;
        char *virtaddr;
        int count;


        virtaddr=(char*)shmat(shmid,NULL,0);//缓冲区引入
        char **al=new char*[N];
        for(i=0;i<N;i++) al[i]=virtaddr+i*size;//环形缓冲区构建
        int fp=open(file,O_RDONLY);//打开要复制文件

        i=0;
        while(1){
            P(semid,0);
            count=read(fp,al[i]+4,size-4);//写入缓冲区
            *(int*)al[i]=count;//前四个字节为读取大小
            n++;
            V(semid,1);

            if(count<size-4) break;//写入缓冲区未写满
            i++;
            if(i==N) i=0;
        }
        delete []al;
        close(fp);//关闭文件
        shmdt(virtaddr);//断开缓冲区链接
        is_over=true;
        exit(0);
}
