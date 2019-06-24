#ifndef __MYDICT_H__
#define __MYDICT_H__
#include <pthread.h>
#include <vector>
#include <set>
#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

class Mydict
{
public:
    static Mydict * getInstance();
    static void init();
    static void destroy();

    void initDict(const char * dictpath);
    void initIndex(const char * indexpath);
    vector<pair<string, int>> & getDict();
    unordered_map<string, set<int>> & getIndex();
private:
    Mydict() {}
    ~Mydict() {}
private:
    static Mydict * _pInstance;
    static pthread_once_t _once;
    vector<pair<string, int>> _dict;
    unordered_map<string, set<int>> _index;
};

#endif
