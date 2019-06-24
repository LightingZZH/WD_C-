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
void TaskQueue::push(const ElemType & elem)
{
    {
        MutexLockGuard autolock(_mutex);
        while(full()){
            _notFull.wait();    //while防止异常唤醒
        }
        _que.push(elem);
    }//使用语句块减小加锁范围
    _notEmpty.notify();
}
//pop在消费者
ElemType TaskQueue::pop()
{
        MutexLockGuard autolock(_mutex);
        while(_flag && empty()){
            _notEmpty.wait();
        }
        if(_flag){
            ElemType ret = _que.front();
            _que.pop();
            _notFull.notify();
            return ret;
        }else{      //避免退出时阻塞
            return ElemType();
        }
}

void TaskQueue::wakeup()
{
    if(_flag)
        _flag = false;
    _notEmpty.notifyAll();
}
