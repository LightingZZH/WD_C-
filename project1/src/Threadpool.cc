#include "../include/Threadpool.h"
#include <unistd.h>
using std::placeholders::_1;

Threadpool::Threadpool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _que(_queSize)
, _isExit(false)
{
    _threads.reserve(_threadNum);
}

void Threadpool::start()
{
    for(size_t idx = 0; idx!=_threadNum; ++idx){
        unique_ptr<Thread> thread(new Thread(
            std::bind(&Threadpool::threadFunc, this, _1), idx
        ));
        _threads.push_back(move(thread));
    }

    for(auto & thread : _threads){
        thread->start();
    }
}

void Threadpool::stop()
{
    if(!_isExit){
        while(!_que.empty()){
            sleep(1);
        }
        _isExit = true;
        _que.wakeup();
        for(auto & thread : _threads){
            thread->join();
        }
    }
}

void Threadpool::addTask(Task && task)
{
    _que.push(move(task));
}

Task Threadpool::getTask()
{
    return _que.pop();
}

void Threadpool::threadFunc(int cnt)
{
    while(!_isExit){
        Task task = getTask();
        if(task){
            task(cnt);
        }
    }
}
