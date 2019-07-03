//网页类
#ifndef __WEBPAGE_H__
#define __WEBPAGE_H__

#include "Configuration.h"
#include "SplitToolCppJieba.h"
#include <string>
#include <map>
#include <set>
#include <vector>
using std::string;
using std::map;
using std::vector;
using std::set;

class WebPage
{
    friend bool operator==(const WebPage & lhs, const WebPage & rhs);
    friend bool operator<(const WebPage & lhs, const WebPage & rhs);

public:
    const static int TOPK_NUMBER = 20;

    WebPage(string & doc, Configuration & conf, SplitToolCppJieba & jieba);

    int getDocId()
    {   return _docId;  }

    map<string, int> & getWordsMap()
    {   return _wordsMap;   }

    string getDoc()
    {   return _doc;    }

private:
    void processDoc(const string & doc, Configuration & conf, SplitToolCppJieba & jieba);

    void calTopWords(vector<string> & vecWords, int topNum, set<string> & stopWordList);
private:
    string _doc;
    int _docId;
    string _docTitle;
    string _docUrl;
    string _docContent;
    string _docSummary;     //摘要，自动生成的

    vector<string> _topWords;
    map<string, int> _wordsMap; //去停用词之后的单词和词频
};

#endif
