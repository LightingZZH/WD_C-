#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "TaskQueue.h"
#include "Thread.h"
#include <vector>
#include <memory>
#include <functional>
using std::vector;
using std::unique_ptr;

using Task = std::function<void(int)>;
class Threadpool
{
public:
    Threadpool(size_t, size_t);

    void start();
    void stop();

    void addTask(Task && task);
private:
    void threadFunc(int cnt);
    Task getTask();
private:
    size_t _threadNum;
    size_t _queSize;
    vector<unique_ptr<Thread>> _threads;
    TaskQueue _que;
    bool _isExit;
};
#endif
