#ifndef __RSS_H__
#define __RSS_H__

#include "tinyxml2.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using std::cout;
using std::endl;
using std::ofstream;
using std::string;
using std::vector;
using namespace tinyxml2;

struct RssItem
{
    string title;
    string link;
    string description;
    string content;
};

class RssReader
{
public:
    RssReader();
    void parseRss();//解析
    void dump(const string & filename);//输出
private:
    vector<RssItem> _rss;
};

#endif
