#include <iostream>
#include <list>
#include <unordered_map>
using std::endl;
using std::cout;
using std::unordered_map;
using std::list;

struct CacheNode{
    int key;
    int value;
    CacheNode(int k, int v)
    : key(k)
    , value(v)
    {}
};

class LRUCache
{
public:
    LRUCache(int capacity)
    : _capacity(capacity)
    {}

    int get(int key)
    {
        auto ret = _umap.find(key);
        if(ret == _umap.end()) return -1;
        else{
            _list.splice(_list.end(),_list,ret->second);
            return ret->second->key;
        }
    }

    void put(int key, int value)
    {
        auto ret = _umap.find(key);
        if(ret != _umap.end()){
            _list.erase(ret->second);
        }
        _list.push_back(CacheNode(key,value));
        _umap[key] = --_list.end();
        if(_list.size() > _capacity){
            int k = _list.begin()->key;
            _list.pop_front();
            _umap.erase(k);
        }
    }

private:
    unsigned long _capacity;
    list<CacheNode> _list;
    unordered_map<int, list<CacheNode>::iterator> _umap;
};

int main()
{
    LRUCache cache(2);
    cache.put(1,1);
    cache.put(2,2);
    cout<<"cache.get(1) = "<<cache.get(1)<<endl;
    cache.put(3,3);
    cout<<"cache.get(2) = "<<cache.get(2)<<endl;
    cache.put(4,4);
    cout<<"cache.get(1) = "<<cache.get(1)<<endl;
    cout<<"cache.get(3) = "<<cache.get(3)<<endl;
    cout<<"cache.get(4) = "<<cache.get(4)<<endl;

    return 0;
}

