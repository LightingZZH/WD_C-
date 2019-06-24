#ifndef __THREAD_H__
#define __THREAD_H__
#include "Noncopyable.h"
#include <pthread.h>
#include <functional>

class Thread
: Noncopyable
{
    using ThreadCallback = std::function<void()>;
public:
    Thread(ThreadCallback && cb)
    : _pthid(0)
    , _isRunning(false)
    , _cb(move(cb))
    {}

    ~Thread();

    void start();
    void join();
private:
    static void* threadFunc(void*);
private:
    pthread_t _pthid;
    bool _isRunning;
    ThreadCallback _cb;
};

#endif
