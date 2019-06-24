#include "Consumer.h"
#include "TaskQueue.h"
#include <unistd.h>
#include <iostream>

void Consumer::run()
{
    int cnt = 10;
    while(cnt--){
        sleep(2);
        int num = _taskque.pop();
        cout<<"Consumer thread "<<pthread_self()
            <<" get a number = "<<num<<endl;
    }
}
