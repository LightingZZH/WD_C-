#include "../offline/Configuration.h"
#include "../include/Threadpool.h"
#include "../include/SpellcorrectServer.h"
#include "../include/Mydict.h"
#include <unistd.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
using namespace std;
using std::placeholders::_1;

int main()
{
    Configuration conf("../conf/my.conf");
    map<string, string> myconf = conf.getConfigMap();
    string ip = myconf["ip"];
    string s_port = myconf["port"];
    string dictpath = myconf["dict"];
    string indexpath = myconf["index"];
    unsigned short port;
    stringstream ss;
    ss << s_port;
    ss >> port;

    Mydict::getInstance()->initDict(dictpath.c_str());
    Mydict::getInstance()->initIndex(indexpath.c_str());
    

    cout<<"---------SpellcorrectServer started-----------"<<endl;
    SpellcorrectServer server(4, 10, ip, port);
    server.start();


    return 0;
}
