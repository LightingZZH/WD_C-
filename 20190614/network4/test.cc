#include "Threadpool.h"
#include "TcpServer.h"
#include <unistd.h>
#include <stdio.h>
#include <iostream>
using namespace std;
using std::placeholders::_1;

class MyTask
{
public:
    MyTask(const string & msg, const TcpConnectionPtr & conn)
    : _msg(msg)
    , _conn(conn)
    {}

    //运行在线程池的某个子线程中
    void process()
    {
        string response = _msg;
        _conn->sendInLoop(response);
    }
private:
    string _msg;
    TcpConnectionPtr _conn;
};

class EchoServer
{
public:
    EchoServer(size_t threadNum, size_t queSize, const string & ip, unsigned short port)
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
        _threadpool.addTask(bind(&MyTask::process,task));
    }

    void onClose(const TcpConnectionPtr & conn)
    {
        cout<<"onClose..."<<endl;
        cout<<conn->toString()<<" has closed!"<<endl;
    }
    //void process(); //业务逻辑的处理，不知道干嘛的

    void start()
    {
        _threadpool.start();

        _server.setConnectionCallback(std::bind(&EchoServer::onConnection, this, _1));
        _server.setMessageCallback(std::bind(&EchoServer::onMessage, this, _1));
        _server.setCloseCallback(std::bind(&EchoServer::onClose, this, _1));

        _server.start();
    }

private:
    Threadpool _threadpool;
    TcpServer _server;
};

int main()
{
    EchoServer server(4, 10, "192.168.3.155", 2000);
    server.start();
    return 0;
}
