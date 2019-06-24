#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "InetAddress.h"
#include "Socket.h"
class Acceptor
{
public:
    Acceptor(unsigned short port);
    Acceptor(const string & ip, unsigned short port);
    Acceptor(const struct sockaddr_in & addr);

    void ready();
    int accept();

private:
    void setResueAddr(bool on);
    void setResuePort(bool on);

    void bind();
    void listen();
private:
    InetAddress _addr;
    Socket _listenSocket;
};

#endif
