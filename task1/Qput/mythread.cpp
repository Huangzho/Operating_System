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



    virtaddr=(char*)shmat(shmid,NULL,0);
    char **al=new char*[N];
    for(i=0;i<N;i++) al[i]=virtaddr+i*size;//循环缓冲区构建
    int fp=open(file,O_WRONLY|O_CREAT|O_APPEND);//创建文件
    if(!fp) printf("can't open\n");

    i=0;
    while(1){
        P(semid,1);
        count=write(fp,al[i]+4,*(int*)(al[i]));
        n++;
        //printf("%ld\n",w.n);
        V(semid,0);

        if(count<size-4) break;
        i++;
        if(i==N) i=0;
    }
    delete [] al;
    close(fp);//关闭文件
    shmdt(virtaddr);//断开共享文件链接
    is_over=true;
    exit(0);
}
