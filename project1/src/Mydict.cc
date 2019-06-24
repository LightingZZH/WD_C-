#include "Mydict.h"
#include <fstream>
#include <sstream>

Mydict * Mydict::_pInstance = nullptr;
pthread_once_t Mydict::_once = PTHREAD_ONCE_INIT;

Mydict * Mydict::getInstance()
{
    pthread_once(&_once, init);
    return _pInstance;
}

void Mydict::init()
{
    _pInstance = new Mydict();
    ::atexit(destroy);
}

void Mydict::destroy()
{
    if(_pInstance)
        delete _pInstance;
}

void Mydict::initDict(const char * dictpath)
{
    ifstream ifs(dictpath);
    if(!ifs){
        cout<<"open file "<<dictpath<<" error!"<<endl;
        return ;
    }
    string line;
    while(std::getline(ifs, line)){
        istringstream iss(line);
        string word;
        int cnt;
        iss >> word;
        iss >> cnt;
        _dict.push_back(make_pair(word, cnt));
    }
}

void Mydict::initIndex(const char * indexpath)
{
    ifstream ifs(indexpath);
    if(!ifs){
        cout<<"open file "<<indexpath<<" error!"<<endl;
        return ;
    }
    string line;
    while(std::getline(ifs, line)){
        istringstream iss(line);
        string query;
        int idx;
        iss >> query;
        while(iss >> idx){
            _index[query].insert(idx);
        }
    }
}

vector<pair<string, int>> & Mydict::getDict()
{
    return _dict;
}

unordered_map<string, set<int>> & Mydict::getIndex()
{
    return _index;
}
