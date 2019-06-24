#ifndef __TIMER_H__
#define __TIMER_H__

#include <functional>
using namespace std;

class Timer
{
using TimerCallback = function<void()>;
public:
    Timer(int initTime, int intervalTime, TimerCallback && cb)
    : _fd(createTimerfd())
    , _initTime(initTime)
    , _intervalTime(intervalTime)
    , _cb(move(cb))
    , _isStarted(false)
    {}

    void start();
    void stop();
    void setTimer(int initTime, int intervalTime);

private:
    int createTimerfd();
    void handleRead();

private:
    int _fd;
    int _initTime;
    int _intervalTime;
    TimerCallback _cb;
    bool _isStarted;
};
#endif
