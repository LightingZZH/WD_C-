#include "../include/Thread.h"
#include <stdio.h>
#include <errno.h>
#include <iostream>
using std::cout;
using std::endl;

__thread int threadCnt;

using ThreadCallback = std::function<void(int)>;

struct ThreadData
{
    int _cnt;
    ThreadCallback _cb;

    ThreadData(int cnt, ThreadCallback cb)
    : _cnt(cnt)
    , _cb(cb)
    {}

    void runInThread()
    {
        threadCnt = _cnt;
         if(_cb)
            _cb(threadCnt);
    }
};

Thread::Thread(ThreadCallback && cb, int cnt)
: _pthid(0)
, _cb(move(cb))
, _isRunning(false)
, _cnt(cnt)
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
    ThreadData * data = new ThreadData(_cnt, _cb);
    if(pthread_create(&_pthid, nullptr, threadFunc, data)){
        perror("pthread_create");
        return;
    }
    _isRunning = true;
}

void Thread::join()
{
    if(_isRunning){
        pthread_join(_pthid, NULL);
        _isRunning = false;
    }
}

void* Thread::threadFunc(void* arg)
{
    ThreadData* pdata = static_cast<ThreadData*>(arg);
    if(pdata)
        pdata->runInThread();
    delete pdata;
    return nullptr;
}
