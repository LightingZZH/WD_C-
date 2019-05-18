#include <pthread.h>
#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;

class MutexLock
{
public:
    MutexLock()
    {
        pthread_mutex_init(&_mutex,NULL);
        cout<<"MutexLock()"<<endl;
    }
    void lock()
    {
        pthread_mutex_lock(&_mutex);
    }
    void unlock()
    {
        pthread_mutex_unlock(&_mutex);
    }
    pthread_mutex_t * getMutex()
    {
        return &_mutex;
    }
    ~MutexLock()
    {
        pthread_mutex_destroy(&_mutex);
        cout<<"~MutexLock()"<<endl;
    }
private:
    pthread_mutex_t _mutex;
};

class Condition
{
public:
    Condition()
    : _Mux()
    {
        pthread_cond_init(&_cond,NULL);
        cout<<"Condition()"<<endl;
    }
    MutexLock * getMux()
    {
        return &_Mux;
    }
    void wait()
    {
        pthread_cond_wait(&_cond,_Mux.getMutex());
    }
    void notify()
    {
        pthread_cond_signal(&_cond);
    }
    void notifyall()
    {
        pthread_cond_broadcast(&_cond);
    }
    ~Condition()
    {
        //_Mux.~MutexLock();
        pthread_cond_destroy(&_cond);
        cout<<"~Condition()"<<endl;
    }
private:
    pthread_cond_t _cond;
    MutexLock  _Mux;
};

void* threadFunc(void *p)
{
    Condition* pcd=(Condition*)p;
    pcd->getMux()->lock();
    pcd->wait();
    pcd->getMux()->unlock();
    cout<<"I am child,after wait"<<endl;
    pthread_exit(NULL);
}

int main()
{
    Condition cd;
    pthread_t pthId;
    pthread_create(&pthId,NULL,threadFunc,&cd);
    cout<<"main befor sleep"<<endl;
    sleep(1);
    cout<<"main after sleep"<<endl;
    cd.notify();
    cout<<"send signal ok"<<endl;
    pthread_join(pthId,NULL);
    cout<<"I am main thread"<<endl;
    return 0;
}

