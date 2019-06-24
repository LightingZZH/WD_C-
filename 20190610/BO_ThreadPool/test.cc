#include "Thread.h"
#include "TaskQueue.h"
#include "Threadpool.h"
#include <unistd.h>
#include <time.h>
#include <memory>
#include <iostream>
using namespace std;

class MyTask
{
public:
    void process()
    {
        srand(time(NULL));
        int num = rand()%100;
        cout<<"sub thread "<<pthread_self()
            <<" create a number = "<<num<<endl;
        sleep(1);
    }
};

int main()
{
    unique_ptr<Threadpool> threadpool(new Threadpool(4,10));
    threadpool->start();
    int cnt = 20;
    while(cnt--){
        threadpool->addTask(bind(&MyTask::process,MyTask()));
    }
    threadpool->stop();
    return 0;
}

