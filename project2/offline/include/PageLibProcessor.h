#ifndef __PAGELIBPROCESSOR_H__
#define __PAGELIBPROCESSOR_H__

#include "WebPage.h"
#include "SplitToolCppJieba.h"
#include <string>
#include <vector>
#include <map>
using std::string;
using std::vector;
using std::pair;
using std::unordered_map;

class PageLibProcessor
{
public:
    PageLibProcessor(Configuration & conf, SplitToolCppJieba & jieba);

    void doProcess();

private:
    void readInfoFromFile();
    void cutRedundantPages();
    void buildInvertIndex();
    void store();

private:
    Configuration & _conf;
    SplitToolCppJieba & _jieba;
    vector<WebPage> _pageLib;
    unordered_map<int, pair<int, int>> _offsetLib;
    unordered_map<string, vector<pair<int, double>>> _invertIndex;
};
#endif
