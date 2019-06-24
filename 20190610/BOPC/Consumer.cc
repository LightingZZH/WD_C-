#include "Consumer.h"
#include "TaskQueue.h"
#include <unistd.h>
#include <iostream>
using namespace std;

void Consumer::get(TaskQueue & taskque)
{
    int cnt = 10;
    while(cnt--){
        sleep(2);
        int num = taskque.pop();
        cout<<"consumer thread "<<pthread_self()
            <<" get a number = "<<num<<endl;
    }
}
