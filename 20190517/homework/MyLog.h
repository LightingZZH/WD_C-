#ifndef __MYLOG_H__
#define __MYLOG_H__

#include <log4cpp/Category.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <iostream>
using std::cout;
using std::endl;
using namespace log4cpp;

class Mylog
{
public:
    static Mylog * getInstance()
    {
        if(_pMylog==nullptr){
            _pMylog=new Mylog();
        }
        return _pMylog;
    }

    void warn(const char *msg);
    void error(const char *msg);
    void debug(const char *msg);
    void info(const char *msg);

    static void destory()
    {
        if(_pMylog){
            delete _pMylog;
        }
    }

private:
    PatternLayout *_pL1;
    PatternLayout *_pL2;
    OstreamAppender *_OsApp;
    FileAppender *_fApp;
    Category & _myRecord;

private:
    Mylog();
    ~Mylog();

    static Mylog * _pMylog; 
};

#endif
