#include "GameTime.h"

pthread_once_t GameTime::_once = PTHREAD_ONCE_INIT;
GameTime * GameTime::_pInstance = getInstance();

GameTime * GameTime::getInstance()
{
    pthread_once(&_once, init);
    return _pInstance;
}

void GameTime::init()
{
    _pInstance = new GameTime();
    ::atexit(destroy);
}

void GameTime::destroy()
{
    if(_pInstance)
        delete _pInstance;
}

size_t GameTime::getTime() const
{
    return _hour*60 + _min;
}


void GameTime::updateTime()
{
    _min += 10;
    if(_min == 60){
        ++_hour;
        _min -= 60;
    }
}

void GameTime::initTime()
{
    _min = 0;
    _hour = 0;
}

void GameTime::showTime() const
{
    printf("%03lu:%02lu ", _hour, _min);
}
