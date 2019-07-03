#include "../include/WebPage.h"
#include <iostream>
#include <queue>
#include <algorithm>
using std::cout;
using std::endl;
using std::priority_queue;
using std::pair;
using std::make_pair;

struct wordCompare
{
    bool operator()(const pair<string, int> &lhs, const pair<string, int> &rhs)
    {
        if(lhs.second < rhs.second) return true;
        else if(lhs.second == rhs.second && lhs.first > rhs.first)
            return true;
        else return false;
    }
};


WebPage::WebPage(string & doc, Configuration & conf, SplitToolCppJieba & jieba)
: _doc(doc)
{
    processDoc(doc, conf, jieba);
}

void WebPage::processDoc(const string & doc, Configuration & conf, SplitToolCppJieba & jieba)
{
    string docIdHead = "<docid>";
    string docIdTail = "</docid>";
    string docUrlHead = "<link>";
    string docUrlTail = "</link>";
    string docTitleHead = "<title>";
    string docTitleTail = "</title>";
    string docContentHead = "<content>";
    string docContentTail = "</content>";

    int begPos = doc.find(docIdHead);
    int endPos = doc.find(docIdTail);
    string docId = doc.substr(begPos + docIdHead.size(), endPos - begPos - docIdHead.size());
    _docId = atoi(docId.c_str());

    begPos = doc.find(docUrlHead);
    endPos = doc.find(docUrlTail);
    _docUrl = doc.substr(begPos + docUrlHead.size(), endPos - begPos - docUrlHead.size());

    begPos = doc.find(docTitleHead);
    endPos = doc.find(docTitleTail);
    _docTitle = doc.substr(begPos + docTitleHead.size(), endPos - begPos - docTitleHead.size());
    
    begPos = doc.find(docContentHead);
    endPos = doc.find(docContentTail);
    _docContent = doc.substr(begPos + docContentHead.size(), endPos - begPos - docContentHead.size());

    vector<string> vecWords = jieba.cut(_docContent);
    set<string> & stopWordList = conf.getStopWordList();
    calTopWords(vecWords, TOPK_NUMBER, stopWordList);
}

void WebPage::calTopWords(vector<string> & vecWords, int topNum, set<string> & stopWordList)
{
    for(auto it = vecWords.begin(); it!=vecWords.end(); ++it){
        auto find_it = stopWordList.find(*it);
        if(find_it == stopWordList.end())
            ++_wordsMap[*it];
    }

    priority_queue<pair<string, int>, vector<pair<string, int>>, wordCompare>
        wordsQue(_wordsMap.begin(), _wordsMap.end());

    while(!wordsQue.empty()){
        string word = wordsQue.top().first;
        wordsQue.pop();
        if(word.size()==1 && (word[0]=='\n' || word[0]=='\r'))
            continue;
        _topWords.push_back(word);
        if(_topWords.size() == static_cast<size_t>(topNum)){
            break;
        }
    }
}

//判断两篇文章是否相等
bool operator==(const WebPage & lhs, const WebPage & rhs)
{
    int sameNum = 0;
    auto lIt = lhs._topWords.begin();
    for(; lIt!=lhs._topWords.end(); ++lIt){
        sameNum += std::count(rhs._topWords.begin(), rhs._topWords.end(), *lIt);
    }
    int lhsNum = lhs._topWords.size();
    int rhsNum = rhs._topWords.size();
    int totalNum = lhsNum < rhsNum ? lhsNum : rhsNum;

    if((1.0 * sameNum / totalNum) > 0.75) return true;
    else return false;
}

//对文章按docid进行排序
bool operator<(const WebPage & lhs, const WebPage & rhs)
{
    if(lhs._docId < rhs._docId) return true;
    else return false;
}
