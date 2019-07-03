//目录扫描类，主要用来获取rss文件的绝对路径
#ifndef __DIRSCANNER_H__
#define __DIRSCANNER_H__

#include <string>
#include <vector>
using std::string;
using std::vector;

class Configuration;    //前向声明，头文件加在.cc里
class DirScanner
{
public:
    DirScanner(Configuration & conf);

    void operator()();
    vector<string> & files();
    void print();

private:
    void traverse(const string & dirName);

private:
    Configuration & _conf;    
    vector<string> _vecFiles;
};

#endif
