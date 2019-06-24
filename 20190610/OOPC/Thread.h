#pragma once
#include "Noncopyable.h"
#include <pthread.h>

class Thread
: Noncopyable
{
public:
    Thread() 
    : _pthid(0)
    , _isRunning(false)
    {}

    virtual ~Thread();
    void start();
    void join();

private:
    virtual void run() = 0;
    static void * threadFunc(void*);

private:
    pthread_t _pthid;
    bool _isRunning;
};

