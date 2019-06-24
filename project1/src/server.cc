#include "../offline/Configuration.h"
#include "../include/Threadpool.h"
#include "SpellcorrectServer.h"
#include "Mydict.h"
#include "CacheManager.h"
#include "TimerThread.h"
#include <unistd.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
using namespace std;
using std::placeholders::_1;

class TimerTask
{
public:
    TimerTask(CacheManager & cacheManager)
    : _cacheManager(cacheManager)
    {}

    void process(int cnt)
    {
        _cacheManager.updateCaches();
    }

private:
    CacheManager & _cacheManager;
};

int main()
{
    Configuration conf("../conf/my.conf");
    map<string, string> myconf = conf.getConfigMap();
    string ip = myconf["ip"];
    string s_port = myconf["port"];
    string dictpath = myconf["dict"];
    string indexpath = myconf["index"];
    string cachepath = myconf["cache"];
    unsigned short port;
    stringstream ss;
    ss << s_port;
    ss >> port;

    Mydict::getInstance()->initDict(dictpath.c_str());
    Mydict::getInstance()->initIndex(indexpath.c_str());
    
    CacheManager cacheManager(cachepath.c_str());

    TimerThread timer(60, 60, std::bind(&TimerTask::process, TimerTask(cacheManager), _1));
    timer.start();

    SpellcorrectServer server(4, 10, ip, port, cacheManager);
    server.start();

    cout<<"---------started-----------"<<endl;

    return 0;
}
