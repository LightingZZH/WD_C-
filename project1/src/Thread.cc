#include "../include/Thread.h"
#include "../include/redis.h"
#include <hiredis/hiredis.h>
#include <stdio.h>
#include <errno.h>
#include <iostream>
using std::cout;
using std::endl;

extern __thread Redis* redis;

using ThreadCallback = std::function<void()>;

Thread::Thread(ThreadCallback && cb, int cnt)
: _pthid(0)
, _cb(move(cb))
, _isRunning(false)
, _cnt(cnt)
{
    cout<<"Thread() "<<_cnt<<endl;
}

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
        pthread_join(_pthid, NULL);
        _isRunning = false;
    }
}

void* Thread::threadFunc(void* arg)
{
    Thread* pthread = static_cast<Thread*>(arg);
    threadCnt = pthread->_cnt;
    redis = new Redis();
    redis->connect("127.0.0.1", 6379);
    if(pthread)
        pthread->_cb();
    delete redis;
    return nullptr;
}
