#include "TaskQueue.h"
#include "Consumer.h"
#include "Producer.h"
#include <iostream>
#include <memory>
using namespace std;

int main()
{
    TaskQueue que;
    unique_ptr<Thread> producer(new Producer(que));
    unique_ptr<Thread> consumer(new Consumer(que));
    
    producer->start();
    consumer->start();

    producer->join();
    consumer->join();

    return 0;
}

