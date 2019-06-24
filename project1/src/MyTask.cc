#include "MyTask.h"
#include "Mydict.h"

size_t MyTask::nBytesCode(const char ch)
{
    if(ch & (1<<7)){
        size_t nBytes = 1;
        for(int idx = 0; idx!=6; ++idx){
            if(ch & (1<<(6-idx))){
                ++nBytes;
            }
            else break;
        }
        return nBytes;
    }
    return 1;
}

size_t MyTask::length(const string & str, vector<string> & v)
{
    size_t len = 0;
    for(size_t idx = 0; idx != str.size(); ++idx){
        size_t nBytes = nBytesCode(str[idx]);
        string c = str.substr(idx, nBytes);
        v.push_back(c);
        idx += (nBytes - 1);
        ++len;
    }
    return len;
}

size_t MyTask::minDistance(string & word1, string & word2)
{
    vector<string> v1;
    vector<string> v2;
    const size_t size1 = length(word1, v1);
    const size_t size2 = length(word2, v2);
    if(size1 == 0) return size2;
    if(size2 == 0) return size1;

    vector<vector<size_t>> ed(size1+1, vector<size_t>(size2+1, 0));

    for(size_t i=0; i<=size1; ++i){
        ed[i][0] = i;
    }
    for(size_t i=0; i<=size2; ++i){
        ed[0][i] = i;
    }
    
    for(size_t i=1; i<=size1; ++i){
        for(size_t j=1; j<=size2; ++j){
            if(v1[i-1] == v2[j-1])
                ed[i][j] = ed[i-1][j-1];
            else
                ed[i][j] = min(min(ed[i][j-1]+1, ed[i-1][j]+1), ed[i-1][j-1]+1);
        }
    }
    return ed[size1][size2];
}

void MyTask::process(int cnt)
{
    Cache cache = _cacheManager.getCache(cnt);
    string ret = cache.getResult(_msg);
    if(!ret.size()){
        vector<pair<string, int>> dict = Mydict::getInstance()->getDict();
        unordered_map<string, set<int>> index = Mydict::getInstance()->getIndex();
        for(size_t idx = 0; idx!=_msg.size(); ++idx){
            size_t nBytes = nBytesCode(_msg[idx]);
            string s = _msg.substr(idx, nBytes);
            for(auto & idx : index[s]){
               string word = dict[idx].first;
               int frequence = dict[idx].second;
               int Distance = minDistance(_msg, word);
               _resultQue.push(MyResult(word, frequence, Distance));
            }
        }
        int cnt = 0;
        while(!_resultQue.empty() && cnt < 3){
            ret = ret + _resultQue.top()._word + " ";
            ++cnt;
        }
        cache.addElement(_msg, ret);
    }
    _conn->sendInLoop(ret);
}
