//rss文件解析类
#ifndef __RSS_H__
#define __RSS_H__

#include "tinyxml2.h"
#include <string>
#include <vector>
#include <memory>
using std::string;
using std::vector;
using std::shared_ptr;
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
    RssReader(vector<string> & files);
    ~RssReader();

    void loadFiles();   //加载所有文件
    void loadFile(const string & filename); //加载并解析单个文件
    void makePages(vector<string> & pages); //生成网页库，存储在pages中

private:
    void parseRss(XMLDocument & doc);//解析
    //void dump(const string & filename);//输出
private:
    vector<shared_ptr<RssItem>> _items;
    vector<string> & _files;    //Rss文件的集合
};

#endif
