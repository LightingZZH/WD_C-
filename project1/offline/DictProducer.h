#ifndef __DICTPRODUCER_H__
#define __DICTPRODUCER_H__

#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <map>
#include <iostream>
using namespace std;

class SplitTool;
class DictProducer
{
public:
    DictProducer(const string & dir)
    : _dir(dir)
    {   get_files();    }

    DictProducer(const string & dir, SplitTool * splitTool)
    : _dir(dir)
    , _splitTool(splitTool)
    {   get_files();    }

    void build_dict();
    void build_cn_dict();
    void store_dict(const char * filepath);
    void store_index(const char * filepath);
    void show_files() const;
    void show_dict() const;

private:
    void get_files();
    void push_dict(const string & word);
    size_t nBytesCode(const char ch);

private:
    string _dir;
    vector<string> _enfiles;
    vector<string> _cnfiles;
    map<string, int> _dict;
    unordered_map<string, set<int>> _index;
    
    SplitTool * _splitTool;
};
#endif
