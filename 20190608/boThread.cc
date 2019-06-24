#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <functional>
#include <memory>
#include <iostream>
using namespace std;

class Noncopyable
{
public:
    Noncopyable() {}
    ~Noncopyable() {}
    Noncopyable(const Noncopyable &) = delete;
    Noncopyable operator=(const Noncopyable &) = delete;
};

class Thread
: Noncopyable
{
public:
    using ThreadCallback = function<void()>; //回调函数 函数对象？
    
    Thread(ThreadCallback && cb)
    : _pthid(0)
    , _isRunning(false)
    , _cb(move(cb))
    {}

    ~Thread()
    {
        if(_isRunning){
            pthread_detach(_pthid);
            _isRunning = false;
        }
        cout<<"~Thread()"<<endl;
    }

    void start()
    {
        if(pthread_create(&_pthid, nullptr, threadFunc, this)){
            perror("pthread_create");
            return ;
        }
        _isRunning = true;
    }

    void join()
    {
        if(_isRunning){
            pthread_join(_pthid, nullptr);
            _isRunning = false;
        }
    }

private:
    static void* threadFunc(void*);
private:
    pthread_t _pthid;
    bool _isRunning;
    ThreadCallback _cb;
};

void* Thread::threadFunc(void* arg)
{
    Thread* pthread = static_cast<Thread*>(arg);
    if(pthread){
        pthread->_cb();
    }
    return nullptr;
}

class MyTask
{
public:
    ~MyTask() {cout<<"~MyTask()"<<endl;}

    void process()
    {
        srand(clock());
        int cnt = 10;
        while(cnt--){
            int num = rand()%100;
            cout<<"sub thread "<<pthread_self()
                <<": get a number = "<<num<<endl;
            sleep(1);
        }
        
    }
};

int main()
{
    cout<<"main thread "<<pthread_self()<<endl;
    MyTask task;
    //&task传的是对象指针，也可以传对象，但是值传递
    unique_ptr<Thread> mythread(new Thread(bind(&MyTask::process, &task)));
    mythread->start();
    mythread->join();
    return 0;
}

