//配置文件类
#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <string>
#include <map>
#include <set>
using std::string;
using std::map;
using std::set;

class Configuration
{
public:
    Configuration(const string & filepath);

    map<string, string> & getConfigMap();
    set<string> & getStopWordList();
    void print();

private:
    void readConf();

private:
    string _filepath;
    map<string, string> _configMap;
    set<string> _stopWordList;
};

#endif
