#ifndef __MYLOG_H__
#define __MYLOG_H__

#include <log4cpp/Category.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
using namespace log4cpp;

#define prefix(msg) string("[").append(__FILE__) \
        .append(":").append(__FUNCTION__) \
        .append(":").append(std::to_string(__LINE__)).append("] ") \
        .append(msg)

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

    template <typename... Args>
    void warn(Args... args)
    {   _myRecord.warn(args...);   }

    void error(const char *msg);

    template <typename... Args>
    void error(Args... args)
    {   _myRecord.error(args...);   }

    void debug(const char *msg);

    template <typename... Args>
    void debug(Args... args)
    {   _myRecord.debug(args...);   }

    void info(const char *msg);

    template <typename... Args>
    void info(Args... args)
    {   _myRecord.info(args...);   }

    static void destory()
    {
        if(_pMylog){
            delete _pMylog;
        }
    }

private:
    Category & _myRecord;

private:
    Mylog();
    ~Mylog();

    static Mylog * _pMylog; 
};

#define LogInfo(msg, ...) Mylog::getInstance()->info(prefix(msg).c_str(), ##__VA_ARGS__)
#define LogError(msg, ...) Mylog::getInstance()->error(prefix(msg).c_str(), ##__VA_ARGS__)
#define LogWarn(msg, ...) Mylog::getInstance()->warn(prefix(msg).c_str(), ##__VA_ARGS__)
#define LogDebug(msg, ...) Mylog::getInstance()->debug(prefix(msg).c_str(), ##__VA_ARGS__)


#endif
