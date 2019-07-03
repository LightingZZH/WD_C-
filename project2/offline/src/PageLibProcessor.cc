#include "../include/PageLibProcessor.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::stringstream;

PageLibProcessor::PageLibProcessor(Configuration & conf, SplitToolCppJieba & jieba)
: _conf(conf)
, _jieba(jieba)
{}

void PageLibProcessor::doProcess()
{
    readInfoFromFile();
    time_t t1 = time(NULL);
    cutRedundantPages();
    buildInvertIndex();
    time_t t2 = time(NULL);
    printf("preprocess time: %ld s\n", t2-t1);

    store();
    time_t t3 = time(NULL);
    printf("store time: %ld s\n", t3-t2);
}

void PageLibProcessor::readInfoFromFile()
{
    map<string, string> & confMap = _conf.getConfigMap();
    string pageLibPath = confMap["ripepage"];
    string offsetLibPath = confMap["offset"];

    ifstream pageIfs(pageLibPath.c_str());
    ifstream offsetIfs(offsetLibPath.c_str());
    if(!pageIfs && !offsetIfs){
        cout<<"ripepage or offset lib open error!"<<endl;
        return ;
    }

    string line;
    int docId, docOffset, docLen;
    while(getline(offsetIfs, line)){
        stringstream ss(line);
        ss >> docId >> docOffset >> docLen;

        string doc;
        doc.resize(docLen, ' ');
        pageIfs.seekg(docOffset, pageIfs.beg);
        pageIfs.read(&*doc.begin(), docLen);

        WebPage webPage(doc, _conf, _jieba);
        _pageLib.push_back(webPage);
        _offsetLib.insert(std::make_pair(docId, std::make_pair(docOffset, docLen)));
    }

#if 0
    for(auto & c : _offsetLib)
        cout<<c.first<<"\t"<<c.second.first<<"\t"<<c.second.second<<endl;
#endif
}

void PageLibProcessor::cutRedundantPages()
{
    for(size_t i = 0; i!=_pageLib.size()-1; ++i)
    {
        for(size_t j = i+1; j!= _pageLib.size(); ++j)
        {
            if(_pageLib[i] == _pageLib[j]){
                _pageLib[j] = _pageLib[_pageLib.size()-1];
                _pageLib.pop_back();
                --j;
            }
        }
    }
}

/*
tf: term frequency, 单词在该篇文章中出现的次数
df: document frequency, 表示一共有多少篇文章出现了该单词
idf: inverse document frequency, 逆文档频率
表示该词对该篇文章的一个重要性系数

idf = log(N/df)     //N表示文章总数
w = tf *idf

//进行归一化处理
w' = w / sqrt(w1^2 +w2^2 + ... + wn^2)

*/


void PageLibProcessor::buildInvertIndex()
{
    for(auto page : _pageLib){
        map<string, int> & wordsMap = page.getWordsMap();
        for(auto wordMap : wordsMap){
            _invertIndex[wordMap.first].push_back(std::make_pair(
                    page.getDocId(), wordMap.second));
        }
    }

    map<int, double> weightSum; //保存每一篇文档中所有词的权重平方和，int代表docid
    
    int totalPageNum = _pageLib.size();
    for(auto & c : _invertIndex){
        int df = c.second.size();
        double idf = log(1.0*totalPageNum/df);
        for(auto & item : c.second){
            double weight = item.second * idf;

            item.second = weight;
            weightSum[item.first] += pow(weight, 2);
        }
    }
    //归一化处理
    for(auto & c : _invertIndex){
        for(auto & item : c.second){
            item.second = item.second / sqrt(weightSum[item.first]);
        }
    }

#if 0
    for(auto & c : _invertIndex){
        cout<<c.first<<"\t";
        for(auto & item : c.second){
            cout<<item.first<<"\t"<<item.second<<"\t";
        }
        cout<<endl;
    }
#endif
}

void PageLibProcessor::store()
{
    sort(_pageLib.begin(), _pageLib.end()); //因为重载了WebPage类的 < 运算符
    
    ofstream ofsPageLib(_conf.getConfigMap()["newripepage"].c_str());
    ofstream ofsOffsetLib(_conf.getConfigMap()["newoffset"].c_str());
    if(!ofsPageLib && !ofsOffsetLib){
        cout<<"new page or offset lib ofstream open error!"<<endl;
        return ;
    }

    for(auto & page : _pageLib){
        int id = page.getDocId();
        int len = page.getDoc().size();
        ofstream::pos_type offset = ofsPageLib.tellp();

        ofsPageLib << page.getDoc();    //newripage
        ofsOffsetLib << id << '\t' << offset << '\t' << len << '\n';    //newoffset
    }
    ofsPageLib.close();
    ofsOffsetLib.close();

    ofstream ofsInvertIndex(_conf.getConfigMap()["invertIndex"].c_str());
    if(!ofsInvertIndex){
        cout<<"invertIndex ofstream open error!"<<endl;
        return ;
    }
    for(auto & c : _invertIndex){
        ofsInvertIndex << c.first << '\t';
        for(auto & item : c.second){
            ofsInvertIndex << item.first << '\t' << item.second << '\t';
        }
        ofsInvertIndex << '\n';
    }
    ofsInvertIndex.close();
}
