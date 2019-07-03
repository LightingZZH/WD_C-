#ifndef __WORDQUERY_H__
#define __WORDQUERY_H__

#include "WebPage.h"
#include "Configuration.h"
#include "SplitToolCppJieba.h"
#include <vector>
#include <map>
#include <set>
#include <string>
using std::vector;
using std::map;
using std::unordered_map;
using std::set;
using std::string;
using std::pair;
using std::make_pair;

class WordQuery
{
public:
    WordQuery(Configuration & conf, SplitToolCppJieba & jieba);

    string doQuery(const string & query);

private:
    void loadLib();
    vector<double> getQueryWordsWeight(vector<string> & queryWords);
    bool executeQuery(const vector<string> & queryWords, vector<pair<int, vector<double>>> & vecResult);
    string createJson(vector<int> & vecDocId, const vector<string> & queryWords);
    string returnNoAnswer();

private:
    Configuration & _conf;
    SplitToolCppJieba & _jieba;
    unordered_map<int, WebPage> _pageLib;
    unordered_map<int, pair<int, int>> _offsetLib;
    unordered_map<string, set<pair<int, double>>> _invertIndex;
};

#endif
