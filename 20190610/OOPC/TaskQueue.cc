#include "TaskQueue.h"
#include <iostream>
using namespace std;

bool TaskQueue::full() const
{
    return _que.size() == _queSize;
}

bool TaskQueue::empty() const
{
    return _que.empty();
}
//push在生产者
void TaskQueue::push(int number)
{
    {
        MutexLockGuard autolock(_mutex);
        while(full()){
            _notFull.wait();    //while防止异常唤醒
        }
        _que.push(number);
    }//使用语句块减小加锁范围
    _notEmpty.notify();
}
//pop在消费者
int TaskQueue::pop()
{
    int ret;
    {
        MutexLockGuard autolock(_mutex);
        while(empty()){
            _notEmpty.wait();
        }
        ret = _que.front();
        _que.pop();
    }
    _notFull.notify();
    return ret;
}

