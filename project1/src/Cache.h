#ifndef __CACHE_H__
#define __CACHE_H__
#include <string>
#include <list>
#include <unordered_map>
using std::string;
using std::list;
using std::unordered_map;

struct CacheNode
{
    string key;
    string value;
    CacheNode(string k, string v) : key(k), value(v) {}
};

class Cache
{
public:
    Cache();
    void addElement(const string & key, const string & value);
    void readFromFile(const string & filename);
    void writeToFile(const string & filename);
    void update(const Cache & rhs);

    string getResult(const string & key);

    list<CacheNode> _cacheList;
private:
    size_t _capacity;
    unordered_map<string, list<CacheNode>::iterator> _cacheMap;
};

#endif
