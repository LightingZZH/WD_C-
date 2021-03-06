#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <stdio.h>
#include <errno.h>
#include <pthread.h>

namespace wd
{
class MutexLock
{
public:
    MutexLock()
    : _isLock(false)
    {
        if(pthread_mutex_init(&_mutex,NULL)){
            perror("pthread_mutex_init");
        }
    }

    MutexLock(const MutexLock &) = delete;
    MutexLock & operator=(const MutexLock &) = delete;

    ~MutexLock()
    {
        if(pthread_mutex_destroy(&_mutex)){
            perror("pthread_mutex_destroy");
        }
    }

    void lock()
    {
        if(pthread_mutex_lock(&_mutex)){
            perror("pthread_mutex_lock");
        }
        _isLock = true;
    }

    void unlock()
    {
        if(pthread_mutex_unlock(&_mutex)){
            perror("pthread_mutex_unlock");
        }
        _isLock=false;
    }

    bool isLock() const {return _isLock;}
    pthread_mutex_t * getMutexLockPtr() {return &_mutex;}

#if 0
private:    //禁止复制
    MutexLock(const MutexLock &);
    MutexLock & operator=(const MutexLock &);
#endif
private:
    pthread_mutex_t _mutex;
    bool _isLock;
};

class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock &mutex)
    : _mutex(mutex)
    {
        _mutex.lock();
    }

    ~MutexLockGuard()
    {
        _mutex.unlock();
    }
private:
    MutexLock & _mutex;
};
}
#endif
