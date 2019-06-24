#include "Threadpool.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

class MyTask
: public Task
{
public:
private:
    void process()
    {
        srand(time(NULL));
        int num = rand()%100;
        cout<<">> sub thread "<<pthread_self()
            <<" create a number = "<<num<<endl;
        sleep(1);
    }
};

int main()
{
    Threadpool threadpool(4,10);
    threadpool.start();

    unique_ptr<Task> task(new MyTask());
    int cnt = 10;
    while(cnt--){
        threadpool.addTask(task.get());
        cout<<">> cnt = "<<cnt<<endl;
    }

    threadpool.stop();

    return 0;
}

