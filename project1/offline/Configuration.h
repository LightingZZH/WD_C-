#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <iostream>
using std::string;
using std::istringstream;
using std::ifstream;
using std::map;
using std::cout;
using std::endl;

class Configuration
{
public:
    Configuration(const string & filepath)
    : _filepath(filepath)
    {}

    map<string, string> & getConfigMap()
    {
        ifstream ifs(_filepath);
        if(!ifs){
            cout<<">> open file error"<<endl;
        }else{
            string line;
            while(std::getline(ifs, line)){
                istringstream iss(line);
                string key, value;
                while(!iss.eof()){
                    iss >> key >> value;
                    _configMap.insert({key, value});
                }
            }
        }
        return _configMap;
    }

private:
    string _filepath;
    map<string, string> _configMap;
};

#endif
