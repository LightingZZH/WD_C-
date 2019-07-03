#include "../include/Configuration.h"
#include <iostream>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;

Configuration::Configuration(const string & filepath)
: _filepath(filepath)
{
    readConf();
}

void Configuration::readConf()
{
    ifstream ifs(_filepath.c_str());
    if(!ifs){
        cout<<"open file "<<_filepath<<" error!"<<endl;
        return ;
    }
    string line;
    while(std::getline(ifs, line)){
        istringstream iss(line);
        string key, value;
        iss >> key >> value;
        _configMap[key] = value;
    }
    cout<<"read configuration is over"<<endl;
}

map<string, string> & Configuration::getConfigMap()
{
    return _configMap;
}

set<string> & Configuration::getStopWordList()
{
    string stopWordPath = _configMap["stopWord"];
    ifstream ifs(stopWordPath.c_str());
    if(!ifs){
        cout<<"open file "<<stopWordPath<<" error!"<<endl;
    }else{
        string word;
        while(std::getline(ifs, word))
            _stopWordList.insert(word);
#if 0
        for(auto & c : _stopWordList)
            cout<<c<<endl;
#endif
    }
    return _stopWordList;
}

void Configuration::print()
{
    for(auto & c : _configMap)
        cout<<c.first<<"\t"<<c.second<<endl;
}
