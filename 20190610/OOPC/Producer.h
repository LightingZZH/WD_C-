#pragma once
#include "Thread.h"

class TaskQueue;    //前向声明
class Producer
: public Thread
{
public:
    Producer(TaskQueue & taskque)
    : _taskque(taskque)
    {}

private:
    void run();
private:
    TaskQueue & _taskque;
};

