#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__

#include "Noncopyable.h"
#include <pthread.h>
#include <stdio.h>
#include <errno.h>

class MutexLock
: Noncopyable
{
public:
    MutexLock()
    : _isLocking(false)
    {
        if(pthread_mutex_init(&_mutex, NULL)){
            perror("pthread_mutex_init");
        }
    }
    
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
            return ;
        }
        _isLocking = true;
    }
    
    void unlock()
    {
        if(pthread_mutex_unlock(&_mutex)){
            perror("pthread_mutex_unlock");
            return ;
        }
        _isLocking = false;
    }

    pthread_mutex_t * getMutexLockPtr() {   return &_mutex; }
private:
    bool _isLocking;
    pthread_mutex_t _mutex;
};

class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock & mutex)
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

#endif
