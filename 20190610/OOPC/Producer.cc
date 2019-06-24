#include "Producer.h"
#include "TaskQueue.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

void Producer::run()
{
    srand(clock());
    int cnt = 10;
    while(cnt--){
        int num = rand()%100;
        _taskque.push(num);
        cout<<"producer thread "<<pthread_self()
            <<" create a number = "<<num<<endl;
        sleep(1);
    }
}
