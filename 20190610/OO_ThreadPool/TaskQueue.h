#pragma once
#include "MutexLock.h"
#include "Condition.h"
#include <queue>
using namespace std;

class Task;
using ElemType = Task*;
class TaskQueue
{
public:
    TaskQueue(size_t queSize = 10) 
    : _queSize(queSize)
    , _mutex()
    , _notFull(_mutex)
    , _notEmpty(_mutex)
    {}

    bool full() const;
    bool empty() const;
    void push(const ElemType &);
    ElemType pop();

private:
    size_t _queSize;
    queue<ElemType> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
};

