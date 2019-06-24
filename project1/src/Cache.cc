#include "Cache.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Cache::Cache()
: _capacity(8)
{}

void Cache::addElement(const string & key, const string & value)
{
    auto it = _cacheMap.find(key);
    if(it == _cacheMap.end()){
        if(_cacheList.size() == _capacity){
            string oldkey = _cacheList.back().key;
            _cacheMap.erase(oldkey);
            _cacheList.pop_back();
        }
        _cacheList.push_front(CacheNode(key, value));
        _cacheMap.insert(make_pair(key, _cacheList.begin()));
    }
}

string Cache::getResult(const string & key)
{
    auto it = _cacheMap.find(key);
    if(it == _cacheMap.end())
        return string();
    else{
        string value = it->second->value;
        _cacheList.splice(_cacheList.begin(), _cacheList, it->second);
        _cacheMap[key] = _cacheList.begin();
        return value;
    }
}

void Cache::readFromFile(const string & filename)
{
    ifstream ifs(filename);
    if(!ifs){
        cout<<"open file "<<filename<<" error!"<<endl;
        return ;
    }
    string line;
    while(std::getline(ifs, line)){
        istringstream iss(line);
        string query, ret;
        iss >> query;
        while(iss >> ret){
            ret = ret + " ";
        }
        addElement(query, ret);
    }
}

void Cache::writeToFile(const string & filename)
{
    ofstream ofs(filename);
    if(!ofs){
        cout<<"open file "<<filename<<" error!"<<endl;
        return ;
    }
    for(auto & c : _cacheList){
        ofs << c.key <<" "<< c.value<<"\n";
    }
    ofs.close();
}

void Cache::update(const Cache & rhs)
{
    _cacheMap = rhs._cacheMap;
    _cacheList = rhs._cacheList;
}
