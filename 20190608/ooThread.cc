#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <memory>
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
: public Noncopyable
{
public:
    Thread();
    virtual ~Thread();

    void start();
    void join();
private:
    virtual void run() = 0;
    static void* threadFunc(void*);
private:
    pthread_t _pthid;
    bool _isRunning;
};

Thread::Thread()
: _pthid(0)
, _isRunning(false)
{}

Thread::~Thread()
{
    if(_isRunning){
        pthread_detach(_pthid);
        _isRunning = false;
    }
    cout<<"~Thread()"<<endl;
}

void Thread::start()
{
    if(pthread_create(&_pthid, nullptr, threadFunc, this)){
        perror("pthread_create");
        return;
    }
    _isRunning = true;
}

void Thread::join()
{
    if(_isRunning){
        pthread_join(_pthid, nullptr);
        _isRunning = false;
    }
}

void* Thread::threadFunc(void *arg)
{
    Thread* pthread = static_cast<Thread*>(arg);
    if(pthread) pthread->run();
    return nullptr;
}

class Mythread
: public Thread
{
public:
    ~Mythread() {   cout<<"~Mythread()"<<endl;  }
private:
    void run() override
    {
        ::srand(::clock());
        int cnt = 10;
        while(cnt--){
            int num = ::rand()%100;
            cout<<"sub thread "<<pthread_self()
                <<": get a number = "<<num<<endl;
            sleep(1);
        }
    }
};

int main()
{
    cout<<"main thread "<<pthread_self()<<endl;
    unique_ptr<Thread> mythread(new Mythread());
    mythread->start();
    mythread->join();
    return 0;
}

