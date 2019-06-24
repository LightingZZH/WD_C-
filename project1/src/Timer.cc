#include "Timer.h"
#include <unistd.h>
#include <poll.h>
#include <sys/timerfd.h>
#include <iostream>
using namespace std;

void Timer::start()
{
    _isStarted = true;
    setTimer(_initTime, _intervalTime);

    struct pollfd pfd;
    pfd.fd = _fd;
    pfd.events = POLLIN;

    while(_isStarted){
        int nready = ::poll(&pfd, 1, -1);
        if(nready == -1 && errno == EINTR)
            continue;
        else if(nready == -1){
            perror("poll");
            return ;
        }else if(nready == 0){
            cout<<"poll timeout"<<endl;
        }else{
            if(pfd.revents & POLLIN){
                handleRead();
                if(_cb)
                    _cb(1);
            }
        }
    }
}

void Timer::stop()
{
    if(_isStarted){
        setTimer(0, 0);
        _isStarted = false;
    }
}

int Timer::createTimerfd()
{
    int fd = ::timerfd_create(CLOCK_REALTIME, 0);
    if(fd == -1){
        perror("timerfd_create");
    }
    return fd;
}

void Timer::setTimer(int initTime, int intervalTime)
{
    struct itimerspec value;
    value.it_value.tv_sec = initTime;
    value.it_value.tv_nsec = 0;
    value.it_interval.tv_sec = intervalTime;
    value.it_interval.tv_nsec = 0;

    int ret = ::timerfd_settime(_fd, 0, &value, nullptr);
    if(ret == -1){
        perror("timerfd_settime");
    }
}

void Timer::handleRead()
{
    uint64_t howmany;
    int ret = ::read(_fd, &howmany, sizeof(howmany));
    if(ret != sizeof(howmany)){
        perror("read");
    }
}
