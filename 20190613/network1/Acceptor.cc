#include "Acceptor.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

Acceptor::Acceptor(unsigned short port)
: _addr(port)
, _listenSocket()
{}

Acceptor::Acceptor(const string & ip, unsigned short port)
: _addr(ip, port)
, _listenSocket()
{}

Acceptor::Acceptor(const struct sockaddr_in & addr)
: _addr(addr)
, _listenSocket()
{}

void Acceptor::setResueAddr(bool on)
{
    int one = on;
    if(setsockopt(_listenSocket.getFd(),
                  SOL_SOCKET,
                  SO_REUSEADDR,
                  &one,
                  sizeof(one)) < 0){
        perror("setsocket");
    }
}

void Acceptor::setResuePort(bool on)
{
    int one = on;
    if(setsockopt(_listenSocket.getFd(),
                  SOL_SOCKET,
                  SO_REUSEPORT,
                  &one,
                  sizeof(one)) < 0){
        perror("setsocket");
    }
}

void Acceptor::bind()
{
    int ret = ::bind(_listenSocket.getFd(),
                   (struct sockaddr *)_addr.getInetAddressPtr(),
                   sizeof(struct sockaddr));
    if(-1 == ret) perror("bind");
}

void Acceptor::listen()
{
    int ret = ::listen(_listenSocket.getFd(),10);//10表示处理客户端的半连接的个数
    if(-1 == ret){
        perror("listen");
    }
}

int Acceptor::accept()
{
    int peerfd = ::accept(_listenSocket.getFd(), NULL, NULL);
    if(peerfd == -1) perror("accept");
    return peerfd;
}

void Acceptor::ready()
{
    setResueAddr(true);
    setResuePort(true);
    bind();
    listen();
}
