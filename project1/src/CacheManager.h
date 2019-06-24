#ifndef __CACHEMANAGER_H__
#define __CACHEMANAGER_H__
#include "Cache.h"
#include <vector>
using std::vector;

class CacheManager
{
public:
    CacheManager(const string & filename)
    : _sz(4)
    , _filename(filename)
    {
        initCache();
    }

    void initCache()
    {
        for(size_t i=0; i!=_sz; ++i){
            _cacheList.push_back(Cache());
        }
        for(auto & c : _cacheList){
            c.readFromFile(_filename);
        }
    }

    Cache & getCache(size_t idx)
    {
        return _cacheList[idx];
    }

    void updateCaches()
    {
        for(size_t idx = 1; idx!=_sz; ++idx){
            size_t size = _cacheList[idx]._cacheList.size();
            if(size == 1){
                auto it =_cacheList[idx]._cacheList.begin();
                _cacheList[0].addElement(it->key, it->value);
            }
            if(size>=2){
                auto it = _cacheList[idx]._cacheList.begin();
                _cacheList[0].addElement(it->key, it->value);
                ++it;
                _cacheList[0].addElement(it->key, it->value);
            }
        }
        for(size_t idx = 1; idx!=_sz; ++idx){
            _cacheList[idx].update(_cacheList[0]);
        }
        _cacheList[0].writeToFile(_filename);
    }
private:
    size_t _sz;
    string _filename;
    vector<Cache> _cacheList;
};

#endif

