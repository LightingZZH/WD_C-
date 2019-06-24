#include "Acceptor.h"
#include "TcpConnection.h"
#include "EventLoop.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

using TcpConnectionPtr = shared_ptr<TcpConnection>;

void onConnection(const TcpConnectionPtr & conn)
{
    cout<<conn->toString()<<" has connected!"<<endl;
    conn->send("welcome to server");
}

void onMessage(const TcpConnectionPtr & conn)
{
    string msg = conn->receive();
    cout<<">> receive msg from client: "<<msg<<endl;
    //decode
    //compute
    //encode
    conn->send(msg);    //回显
}

void onClose(const TcpConnectionPtr & conn)
{
    cout<<conn->toString()<<" has closed!"<<endl;
}

int main()
{
    Acceptor acceptor("192.168.3.155", 2000);
    acceptor.ready();

    EventLoop loop(acceptor);
    loop.setConnectionCallback(onConnection);
    loop.setMessageCallback(onMessage);
    loop.setCloseCallback(onClose);

    loop.loop();

    return 0;
}

