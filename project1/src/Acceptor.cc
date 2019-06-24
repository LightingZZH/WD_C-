#include "../include/Acceptor.h"
#include <sys/types.h>
#include <sys/socket.h>

Acceptor::Acceptor(unsigned short port)
: _addr(port)
, _listenSock()
{}

Acceptor::Acceptor(const string & ip, unsigned short port)
: _addr(ip, port)
, _listenSock()
{}

Acceptor::Acceptor(const struct sockaddr_in & addr)
: _addr(addr)
, _listenSock()
{}

void Acceptor::setReuseAddr(bool on)
{
    int one = on;
    if(setsockopt(_listenSock.getFd(),
                  SOL_SOCKET,
                  SO_REUSEADDR,
                  &one,
                  sizeof(one)) < 0){
        perror("setsockopt");
    }
}

void Acceptor::setReusePort(bool on)
{
    int one = on;
    if(setsockopt(_listenSock.getFd(),
                  SOL_SOCKET,
                  SO_REUSEPORT,
                  &one,
                  sizeof(one)) < 0){
        perror("setsockopt");
    }
}

void Acceptor::bind()
{
    int ret = ::bind(_listenSock.getFd(),
                     (struct sockaddr *)_addr.getInetAddrPtr(),
                     sizeof(struct sockaddr));
    if(-1 == ret) perror("bind");
}

void Acceptor::listen()
{
    int ret = ::listen(_listenSock.getFd(), 10);
    if(-1 == ret) perror("listen");
}

int Acceptor::accept()
{
    int peerfd = ::accept(_listenSock.getFd(), NULL, NULL);
    if(-1 == peerfd) perror("accept");
    return peerfd;
}

void Acceptor::ready()
{
    setReuseAddr(true);
    setReusePort(true);
    bind();
    listen();
}
