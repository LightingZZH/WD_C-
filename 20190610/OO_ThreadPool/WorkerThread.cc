#include "WorkerThread.h"
#include "Threadpool.h"
#include <iostream>

void WorkerThread::run()
{
    _threadpool.threadFunc();
}

