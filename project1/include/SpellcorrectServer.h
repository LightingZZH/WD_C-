#ifndef __SPELLCORRECTSERVER_H__
#define __SPELLCORRECTSERVER_H__

#include "TcpConnection.h"
#include "Threadpool.h"
#include "TcpServer.h"
#include "MyTask.h"
#include <iostream>
using namespace std;
using std::placeholders::_1;

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;

class SpellcorrectServer
{
public:
    SpellcorrectServer(size_t threadNum, size_t queSize, const string & ip, unsigned short port)
    : _threadpool(threadNum, queSize)
    , _server(ip, port)
    {}

    void onConnection(const TcpConnectionPtr & conn)
    {
        cout<<conn->toString()<<" has connected!"<<endl;
        conn->send("welcome to server.");
    }

    void onMessage(const TcpConnectionPtr & conn)
    {
        cout<<"onMessage..."<<endl;
        string msg = conn->receive();
        cout<<">> receive msg from client: "<<msg<<endl;
        MyTask task(msg, conn);
        _threadpool.addTask(std::bind(&MyTask::process,task));
    }

    void onClose(const TcpConnectionPtr & conn)
    {
        cout<<"onClose..."<<endl;
        cout<<conn->toString()<<" has closed!"<<endl;
    }

    void start()
    {
        _threadpool.start();

        _server.setConnectionCallback(std::bind(&SpellcorrectServer::onConnection, this, _1));
        _server.setMessageCallback(std::bind(&SpellcorrectServer::onMessage, this, _1));
        _server.setCloseCallback(std::bind(&SpellcorrectServer::onClose, this, _1));

        _server.start();
    }

private:
    Threadpool _threadpool;
    TcpServer _server;
};

#endif
