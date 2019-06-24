#include "Threadpool.h"
#include "WorkerThread.h"
#include <unistd.h>
#include <iostream>

void Threadpool::start()
{
    for(size_t idx=0; idx!=_threadNum; ++idx){
        unique_ptr<Thread> up(new WorkerThread(*this));
        _threads.push_back(move(up));
    }
    for(auto & thread : _threads){
        thread->start();
    }
}

void Threadpool::addTask(Task *task)
{
    _taskque.push(task);
}

Task* Threadpool::getTask()
{
    return _taskque.pop();
}

void Threadpool::stop()
{
    if(!_isExit){
//        while(!_taskque.empty()){
//            usleep(1000);
//        }
        while(!_taskque.empty()) {}
        _isExit = true;
        for(auto & thread : _threads){
            thread->join();
        }
    }
}

void Threadpool::threadFunc()
{
    while(!_isExit && !_taskque.empty()){
        Task * task = getTask();
        if(task) task->process();
    }
}
