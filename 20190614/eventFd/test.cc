#include "EventfdThread.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <functional>
using namespace std;

struct Mytask
{
    void process()
    {
        srand(time(NULL));
        int num = rand()%100;
        cout<<"thread "<<pthread_self()
            <<": get a number = "<<num<<endl;
    }
};

int main()
{
    EventfdThread evethread(bind(&Mytask::process, Mytask()));

    evethread.start();
    int cnt = 20;
    while(cnt--){
        cout<<"cnt == "<<cnt<<endl
            <<"main thread notify sub thread to do something..."<<endl;
        evethread.wakeup();
        sleep(1);
    }
    cout<<"main thread eventfd stop..."<<endl;
    evethread.stop();

    return 0;
}
