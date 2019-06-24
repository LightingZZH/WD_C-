#include "TcpConnection.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sstream>
#include <iostream>
using std::cout;
using std::endl;

TcpConnection::TcpConnection(int fd)
: _sock(fd)
, _socketIO(fd)
, _localAddr(getLocalAddr())
, _peerAddr(getPeerAddr())
, _isShutdownWrite(false)
{}

TcpConnection::~TcpConnection()
{
    if(!_isShutdownWrite){
        shutdown();
    }
    cout<<toString()<<endl;
    cout<<"connectiong close"<<endl;
}

string TcpConnection::receive()
{
    char buff[65536] = {0};
    _socketIO.readline(buff, sizeof(buff));
    return string(buff);
}

void TcpConnection::send(const string & msg)
{
    _socketIO.writen(msg.c_str(),msg.size());
}

void TcpConnection::shutdown()
{
    if(!_isShutdownWrite){
        _isShutdownWrite = true;
        _sock.shutdownWrite();
    }
}

string TcpConnection::toString() const
{
    std::ostringstream oss;
    oss<<_localAddr.getIp()<<":"<<_localAddr.getPort()<<"--->"
        <<_peerAddr.getIp()<<":"<<_peerAddr.getPort();
    return oss.str();
}

InetAddress TcpConnection::getLocalAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    if(getsockname(_sock.getFd(), (struct sockaddr*)&addr, &len) == -1){
        perror("getsockname");
    }
    return InetAddress(addr);
}

InetAddress TcpConnection::getPeerAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    if(getpeername(_sock.getFd(), (struct sockaddr*)&addr, &len) == -1){
        perror("getpeername");
    }
    return InetAddress(addr);
}

