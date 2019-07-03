#ifndef __REDIS_H__
#define __REDIS_H__

#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <hiredis/hiredis.h>
using namespace std;

class Redis
{
public:
    Redis() {}
    ~Redis()
    {
        this->_connect = NULL;
        this->_reply = NULL;
    }

    bool connect(string host, int port)
    {
        this->_connect = redisConnect(host.c_str(), port);
        if(this->_connect != NULL && this->_connect->err){
            printf("connect error: %s\n", this->_connect->errstr);
            return 0;
        }
        return 1;
    }

    string get(string key)
    {
        this->_reply = (redisReply*)redisCommand(this->_connect, "GET %s", key.c_str());
        if(_reply->type == REDIS_REPLY_NIL)
            return string();
        string str = this->_reply->str;
        freeReplyObject(this->_reply);
        return str;
    }

    void set(string key, string value)
    {
        redisCommand(this->_connect, "SET %s %s", key.c_str(), value.c_str());
    }

private:
    redisContext * _connect;
    redisReply * _reply;
};
#endif
