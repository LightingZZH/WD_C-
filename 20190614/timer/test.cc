#include "TimerThread.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <functional>
using namespace std;

class Mytask
{
public:
    void process()
    {
        srand(time(NULL));
        int num = rand()%100;
        cout<<"thread "<<pthread_self()
            <<": get a number = "<<num<<endl;
        //sleep(1);
    }
};

int main()
{
    TimerThread timer(3, 6, bind(&Mytask::process, Mytask()));

    timer.start();
    sleep(20);
    cout<<"main thread timer stop..."<<endl;
    timer.stop();

    return 0;
}
