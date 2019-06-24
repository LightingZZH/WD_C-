#include "TcpServer.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

void onConnection(const TcpConnectionPtr & conn)
{
    cout<<conn->toString()<<" has conencted!"<<endl;
    conn->send("welcome to server.");
}

void onMessage(const TcpConnectionPtr & conn)
{
    //cout<<"onMessage..."<<endl;
    string msg = conn->receive();
    cout<<">> receive msg from client: "<<msg<<endl;
    conn->send(msg);
}

void onClose(const TcpConnectionPtr & conn)
{
    cout<<"onClose..."<<endl;
    cout<<conn->toString()<<" has closed!"<<endl;
}

int main()
{
    TcpServer server("192.168.3.155",2000);
    server.setConnectionCallback(onConnection);
    server.setMessageCallback(onMessage);
    server.setCloseCallback(onClose);

    server.start();
    return 0;
}

