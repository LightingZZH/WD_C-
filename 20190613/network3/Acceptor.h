#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "InetAddr.h"
#include "Socket.h"

class Acceptor
{
public:
    Acceptor(unsigned short port);
    Acceptor(const string &ip, unsigned short port);
    Acceptor(const struct sockaddr_in & addr);

    void ready();
    int accept();
    int getFd() const {return _listenSock.getFd();}
private:
    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void bind();
    void listen();
private:
    InetAddr _addr;
    Socket _listenSock;
};

#endif
