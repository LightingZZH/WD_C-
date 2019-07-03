#ifndef __WORDQUERYSEVER_H__
#define __WORDQUERYSEVER_H__

#include "TcpServer.h"
#include "WordQuery.h"
#include "Threadpool.h"
#include <string>
#include <functional>
using namespace std;
using placeholders::_1;

class WordQuerySever
{
public:
    WordQuerySever(Configuration & conf, const string & ip, unsigned short & port, SplitToolCppJieba & jieba);

    void start();

private:
    void onConnection(const TcpConnectionPtr & conn);
    void onMessage(const TcpConnectionPtr & conn);
    void onClose(const TcpConnectionPtr & conn);

    void doTask(const TcpConnectionPtr & conn, const string & msg);

private:
    Configuration & _conf;
    WordQuery _wordQuery;
    TcpServer _tcpSever;
    Threadpool _threadpool;
};

WordQuerySever::WordQuerySever(Configuration & conf, const string & ip, unsigned short & port, SplitToolCppJieba & jieba)
: _conf(conf)
, _wordQuery(_conf, jieba)
, _tcpSever(ip, port)
, _threadpool(4, 10)
{
    _tcpSever.setConnectionCallback(
            std::bind(&WordQuerySever::onConnection, this, _1));
    _tcpSever.setMessageCallback(
            std::bind(&WordQuerySever::onMessage, this, _1));
    _tcpSever.setCloseCallback(
            std::bind(&WordQuerySever::onClose, this, _1));
}

void WordQuerySever::start()
{
    _threadpool.start();
    _tcpSever.start();
}

void WordQuerySever::onConnection(const TcpConnectionPtr & conn)
{
    cout<<conn->toString()<<" has connected!"<<endl;
}

void WordQuerySever::onMessage(const TcpConnectionPtr & conn)
{
    string msg(conn->receive());
    cout<<"client: "<<msg<<", size: "<<msg.size()<<endl;
    _threadpool.addTask(std::bind(&WordQuerySever::doTask, this, conn, msg));
}

void WordQuerySever::onClose(const TcpConnectionPtr & conn)
{
    cout<<conn->toString()<<" has closed!"<<endl;
}

void WordQuerySever::doTask(const TcpConnectionPtr & conn, const string & msg)
{
    string ret = _wordQuery.doQuery(msg);
    int sz = ret.size();
    string message(to_string(sz));
    message.append("\n").append(ret);
    conn->sendInLoop(message);
}
#endif
