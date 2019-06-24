#pragma once
#include "Thread.h"

class TaskQueue;
class Consumer
: public Thread
{
public:
    Consumer(TaskQueue & taskque) 
    : _taskque(taskque)
    {}

private:
    void run();

private:
    TaskQueue & _taskque;
};

