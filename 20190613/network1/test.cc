#include "Acceptor.h"
#include "TcpConnection.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

int main()
{
    Acceptor acceptor("192.168.3.155",2000);
    acceptor.ready();

    TcpConnection conn(acceptor.accept());
    cout<<conn.toString()<<" has connected!"<<endl;

    conn.send("welcome to server.");
    printf(">> pls client data: \n");
    cout<<conn.receive()<<endl;

    return 0;
}

