#include "mutex.h"
#include "cond.h"
#include <iostream>
using std::cout;
using std::endl;

int Ticket=100;
bool flag=true;
wd::MutexLock mutex;

class cond
{
public:
    cond() {}
    ~cond() {}

private:

};

wd::Condition condition(mutex);

void * threadFunc1(void *arg)
{
    int cnt=20;
    while(cnt--)
    {
        wd::MutexLockGuard autolock(mutex); //防止死锁
        if(false==flag) condition.wait();
        --Ticket;
        cout<<"thread "<<pthread_self()<<": "
            <<Ticket<<endl;
        if(flag) flag=false;
        condition.notify();
    }
    return NULL;
}

void * threadFunc2(void *arg)
{
    int cnt=20;
    while(cnt--)
    {
        wd::MutexLockGuard autolock(mutex);
        if(true==flag) condition.wait();
        --Ticket;
        cout<<"thread "<<pthread_self()<<": "
            <<Ticket<<endl;
        if(false==flag) flag=true;
        condition.notify();
    }
    return NULL;
}

int main()
{
    pthread_t pthId1,pthId2;
    pthread_create(&pthId1,NULL,threadFunc1,NULL);
    pthread_create(&pthId2,NULL,threadFunc2,NULL);

    pthread_join(pthId1,NULL);
    pthread_join(pthId2,NULL);

    /* wd::MutexLock mutex3; */
    /* mutex3=mutex; */
    return 0;
}

