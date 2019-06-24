#ifndef __GAMETIME_H__
#define __GAMETIME_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

class GameTime
{
public:
    static GameTime * getInstance();
    static void init();
    static void destroy();

    size_t getTime() const;
    void showTime() const;
    void updateTime();
    void initTime();

private:
    static GameTime * _pInstance;
    static pthread_once_t _once;
    size_t _hour;
    size_t _min;
};
#endif
