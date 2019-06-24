#include "Threadpool.h"
#include <unistd.h>
#include <iostream>

void Threadpool::start()
{
    for(size_t idx=0; idx!=_threadNum; ++idx){
        unique_ptr<Thread> up(new Thread(
            bind(&Threadpool::threadFunc, this)
        ));
        _threads.push_back(move(up));
    }
    for(auto & thread : _threads){
        thread->start();
    }
}

void Threadpool::addTask(Task && task)
{
    _taskque.push(std::move(task));
}

Task Threadpool::getTask()
{
    return _taskque.pop();
}

void Threadpool::stop()
{
    if(!_isExit){
        while(!_taskque.empty()){
            sleep(2);
        }
        
        _isExit = true;
        _taskque.wakeup();
        for(auto & thread : _threads){
            thread->join();
        }
    }
}

void Threadpool::threadFunc()
{
    while(!_isExit){
        Task task = getTask();  //task其实就是个函数对象
        if(task) task();
    }
}
