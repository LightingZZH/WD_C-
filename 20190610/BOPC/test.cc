#include "TaskQueue.h"
#include "Producer.h"
#include "Consumer.h"
#include "Thread.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <memory>
#include <iostream>
using namespace std;


int main()
{
    cout<<"main thread "<<pthread_self()<<endl;

    TaskQueue taskque;
    unique_ptr<Thread> producer(
        new Thread(std::bind(&Producer::create, Producer(), ref(taskque))));
    unique_ptr<Thread> consumer(
        new Thread(std::bind(&Consumer::get, Consumer(), ref(taskque))));

    producer->start();
    consumer->start();

    producer->join();
    consumer->join();

    return 0;
}

