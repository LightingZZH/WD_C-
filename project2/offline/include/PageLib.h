//网页库类
#ifndef __PAGELIB_H__
#define __PAGELIB_H__

#include <string>
#include <vector>
using std::vector;
using std::string;

class Configuration;
class DirScanner;

class PageLib
{
public:
    PageLib(Configuration & conf, DirScanner & dirScanner);

    void create();  //生成网页库
    void store();   //存储网页库
private:
    Configuration & _conf;
    DirScanner & _dirScanner;
    vector<string> _vecPages;    
};
#endif
