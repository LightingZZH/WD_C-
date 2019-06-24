#ifndef __THREAD_H__
#define __THREAD_H__

#include "Noncopyable.h"
#include <pthread.h>
#include <functional>

extern __thread int threadCnt;

class Thread
: Noncopyable
{
public:
    using ThreadCallback = std::function<void(int)>;
    Thread(ThreadCallback && cb, int cnt = -1);
    ~Thread();

    void start();
    void join();
private:
    static void* threadFunc(void*);
private:
    pthread_t _pthid;
    ThreadCallback _cb;
    bool _isRunning;
    int _cnt;
};

#endif
