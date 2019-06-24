#include "TaskQueue.h"
#include <iostream>
using std::cout;
using std::endl;

TaskQueue::TaskQueue(size_t sz)
: _sz(sz)
, _mutex()
, _notEmpty(_mutex)
, _notFull(_mutex)
, _flag(true)
{}

bool TaskQueue::empty() const
{
    return _que.empty();
}

bool TaskQueue::full() const
{
    return _que.size() == _sz;
}

void TaskQueue::push(ElemType elem)
{
    {   //使用语句块减小锁的范围
        MutexLockGuard autoLock(_mutex);
        while(full()){
            _notFull.wait();    //有可能异常唤醒，因此用while循环
        }
        _que.push(elem);
    }
    _notEmpty.notify();
}

ElemType TaskQueue::pop()
{
    ElemType ret;
    {
        MutexLockGuard autoLock(_mutex);
        while(_flag && empty()){
            _notEmpty.wait();
        }
        if(_flag){
            ret = _que.front();
            _que.pop();
            _notFull.notify();
        }else{
            return nullptr;
        }
    }
    return ret;
}

void TaskQueue::wakeup()    //唤醒所有线程
{
    _flag = false;
    _notEmpty.notifyAll();
}
