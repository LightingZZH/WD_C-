#ifndef __MYTASK_H__
#define __MYTASK_H__
#include "../include/TcpConnection.h"
#include "CacheManager.h"
#include <queue>
using std::priority_queue;

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;


struct MyResult{
    string _word;
    int _frequence;
    int _distance;

    MyResult(string word, int frequence, int Distance)
    : _word(word)
    , _frequence(frequence)
    , _distance(Distance)
    {}
};

struct MyCompare{
    bool operator()(const MyResult & lhs, const MyResult & rhs) const
    {
        if(lhs._frequence > rhs._frequence) return true;
        else if(lhs._frequence == rhs._frequence){
            if(lhs._distance > rhs._distance) return true;
            else if(lhs._distance == rhs._distance){
                if(lhs._word > rhs._word) return true;
                return false;
            }
            return false;
        }
        return false;
    }
};

class MyTask
{
public:
    MyTask(const string & msg, const TcpConnectionPtr & conn, CacheManager & cacheManager)
    : _msg(msg)
    , _conn(conn)
    , _cacheManager(cacheManager)
    {}

    size_t nBytesCode(const char ch);
    size_t length(const string & str, vector<string> & v);
    size_t minDistance(string & word1, string & word2);

    void process(int);
private:
    string _msg;
    TcpConnectionPtr _conn;
    CacheManager & _cacheManager;
    priority_queue<MyResult, vector<MyResult>, MyCompare> _resultQue;    
};

#endif
