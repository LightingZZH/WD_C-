#pragma once
#include "Thread.h"
#include <iostream>
using namespace std;

class Threadpool;   //前向声明，防止头文件的循环引用
class WorkerThread
: public Thread
{
public:
    WorkerThread(Threadpool & threadpool) 
    : _threadpool(threadpool)
    {}

    ~WorkerThread() {cout<<"~WorkerThread()"<<endl;}

private:
    void run();

private:
    Threadpool & _threadpool;
};

