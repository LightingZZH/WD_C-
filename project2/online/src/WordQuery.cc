#include "../include/WordQuery.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <sstream>
#include <algorithm>

#include <json/json.h>

using std::cout;
using std::endl;
using std::ifstream;
using std::stringstream;

struct SimilarityCompare
{
    SimilarityCompare(vector<double> & base)
    : _base(base)
    {}

    bool operator()(const pair<int, vector<double>> & lhs,
                    const pair<int, vector<double>> & rhs)
    {
        double lhsCrossProduct = 0;
        double rhsCrossProduct = 0;
        double lhsVectorLength = 0;
        double rhsVectorLength = 0;

        for(size_t idx = 0; idx!=_base.size(); ++idx){
            lhsCrossProduct += (lhs.second)[idx] * _base[idx];
            rhsCrossProduct += (rhs.second)[idx] * _base[idx];
            lhsVectorLength += pow((lhs.second)[idx], 2);
            rhsVectorLength += pow((rhs.second)[idx], 2);
        }

        if(lhsCrossProduct / sqrt(lhsVectorLength) < rhsCrossProduct / sqrt(rhsVectorLength))
            return false;
        else return true;
    }

    vector<double> _base;
};

WordQuery::WordQuery(Configuration & conf, SplitToolCppJieba & jieba)
: _conf(conf)
, _jieba(jieba)
{
    loadLib();
}

void WordQuery::loadLib()
{
    ifstream ifsPage(_conf.getConfigMap()["newripepage"].c_str());
    ifstream ifsOffset(_conf.getConfigMap()["newoffset"].c_str());
    if(!ifsPage && !ifsOffset){
        cout<<"new page or offset lib ifstream open error!"<<endl;
        return ;
    }

    int docid, offset, len;
    string line;
    while(getline(ifsOffset, line)){
        stringstream ss(line);
        ss >> docid >> offset >> len;

        string doc;
        doc.resize(len, ' ');
        ifsPage.seekg(offset, ifsPage.beg);
        ifsPage.read(&*doc.begin(), len);

        WebPage webPage(doc, _conf, _jieba);
        _pageLib.insert(make_pair(docid, webPage));
        _offsetLib.insert(make_pair(docid, make_pair(offset, len)));
    }
    ifsPage.close();
    ifsPage.close();


    ifstream ifsInvertIndex(_conf.getConfigMap()["invertIndex"].c_str());
    if(!ifsInvertIndex){
        cout<<"invertIndex ifstream open error!"<<endl;
        return ;
    }
    string word;
    double weight;
    while(getline(ifsInvertIndex, line)){
        stringstream ss(line);
        ss >> word;
        set<pair<int, double>> setID;
        while(ss >> docid >> weight){
            setID.insert(make_pair(docid, weight));
        }
        _invertIndex.insert(make_pair(word, setID));
    }
    ifsInvertIndex.close();
    
    cout<<"loadLib() over"<<endl;
}

string WordQuery::doQuery(const string & query)
{
    vector<string> queryWords;
    if(query.size() > 0)
        queryWords = _jieba.cut(query);

    for(auto & c : queryWords){     //只有满足所有查询词的文章才符合条件
        auto it = _invertIndex.find(c);
        if(it == _invertIndex.end()){
            cout<<"can not found "<<c<<endl;
            return returnNoAnswer();
        }
    }

    vector<double> vecWeight = getQueryWordsWeight(queryWords);
    SimilarityCompare similarityCmp(vecWeight);

    vector<pair<int, vector<double>>> vecResult;
    if(executeQuery(queryWords, vecResult)){
        stable_sort(vecResult.begin(), vecResult.end(), similarityCmp);
        vector<int> vecDocId;

        for(auto & c : vecResult){
            vecDocId.push_back(c.first);
        }
        return createJson(vecDocId, queryWords);
    }else return returnNoAnswer();
}

string WordQuery::returnNoAnswer()
{
    Json::Value root;
    Json::Value arr;
    Json::Value elem;

    elem["title"] = "404, not found";
    elem["summary"] = "亲, I cann't find what you want. What a pity!";
    elem["url"] = "";
    arr.append(elem);
    root["files"] = arr;
    Json::StyledWriter writer;
    return writer.write(root);
}

vector<double> WordQuery::getQueryWordsWeight(vector<string> & queryWords)
{
    map<string, int> wordsMap;
    for(auto & c : queryWords){
        ++wordsMap[c];
    }

    vector<double> weightList;
    double weightSum = 0;
    int totalPageNum = _offsetLib.size();

    for(auto & c : queryWords){
        int df = _invertIndex[c].size();
        double idf = log(1.0*totalPageNum/df);
        int tf = wordsMap[c];
        double weight = idf * tf;
        weightSum += pow(weight, 2);
        weightList.push_back(weight);
    }
    //归一化
    for(auto & c : weightList){
        c /= sqrt(weightSum);
    }

    return weightList;
}

bool WordQuery::executeQuery(const vector<string> & queryWords,
                vector<pair<int, vector<double>>> & vecResult)
{
    cout<<"executeQuery()"<<endl;
    if(queryWords.size() == 0){
        cout<<"empty string not find"<<endl;
        return false;
    }

    typedef set<pair<int, double>>::iterator setIter;
    vector<pair<setIter, int>> vecIter; //保存需要求取交集的迭代器
    vector<int> setSize;
    for(auto & c : queryWords){
        int sz = _invertIndex[c].size();
        if(!sz) return false;

        vecIter.push_back(make_pair(_invertIndex[c].begin(), 0));
        setSize.push_back(sz);
    }

    bool isExiting = false;
    while(!isExiting){
        size_t idx = 0;
        for(; idx!=vecIter.size()-1; ++idx){
            if(vecIter[idx].first->first != vecIter[idx+1].first->first)
                break;
        }
    
        if(idx == vecIter.size()-1){
            vector<double> vecWeight;
            int docid = vecIter[0].first->first;
            for(idx = 0; idx!=vecIter.size(); ++idx){
                vecWeight.push_back(vecIter[idx].first->second);
                ++(vecIter[idx].first);
                ++(vecIter[idx].second);
                if(vecIter[idx].second >= setSize[idx]){
                    isExiting = true;
                }
            }
            vecResult.push_back(make_pair(docid, vecWeight));
        }else{
            int minDocId = 0x7fffffff;
            int iterIdx;    //保存minDocId的迭代器位置
            for(idx = 0; idx!=vecIter.size(); ++idx){
                if(vecIter[idx].first->first < minDocId){
                    minDocId = vecIter[idx].first->first;
                    iterIdx = idx;
                }
            }
            ++(vecIter[iterIdx].first);
            ++(vecIter[iterIdx].second);
            if(vecIter[iterIdx].second >= setSize[iterIdx]){
                isExiting = true;
            }
        }
    }
    return true;
}

string WordQuery::createJson(vector<int> & vecDocId, const vector<string> & queryWords)
{
    Json::Value root;
    Json::Value arr;

    int cnt = 0;
    for(auto & id : vecDocId){
        string summary = _pageLib[id].summary(queryWords);
        string title = _pageLib[id].getTitle();
        string url = _pageLib[id].getUrl();

        Json::Value elem;
        elem["title"] = title;
        elem["summary"] = summary;
        elem["url"] = url;
        arr.append(elem);
        if(++cnt == 10) break;
    }

    root["files"] = arr;
    Json::StyledWriter writer;
    return writer.write(root);
}
