#include "TcpConnection.h"

#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sstream>
#include <iostream>
using namespace std;

TcpConnection::TcpConnection(int fd)
: _sock(fd)
, _socketIO(fd)
, _localAddr(getLocalAddr())
, _peerAddr(getPeerAddr())
, _isShutdownWrite(false)
{}

void TcpConnection::shutdown()
{
    if(!_isShutdownWrite){
        _isShutdownWrite = true;
        _sock.shutdownWrite();
    }
}

TcpConnection::~TcpConnection()
{
    if(!_isShutdownWrite){
        shutdown();
    }
    cout<<"~TcpConnection()"<<endl;
}

string TcpConnection::receive()
{
    char buff[65536] = {0};
    _socketIO.readline(buff, sizeof(buff));
    return string(buff);
}

void TcpConnection::send(const string & msg)
{
    _socketIO.writen(msg.c_str(), msg.size());
}

InetAddr TcpConnection::getLocalAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    if(getsockname(_sock.getFd(), (struct sockaddr*)&addr, &len) == -1){
        perror("getsockname");
    }
    return InetAddr(addr);
}

InetAddr TcpConnection::getPeerAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    if(getpeername(_sock.getFd(), (struct sockaddr*)&addr, &len) == -1){
        perror("getpeername");
    }
    return InetAddr(addr);
}

string TcpConnection::toString() const
{
    std::ostringstream oss;
    oss<<_localAddr.getIp()<<":"<<_localAddr.getPort()<<"--->"
        <<_peerAddr.getIp()<<":"<<_peerAddr.getPort();
    return oss.str();
}

void TcpConnection::setConnectionCallback(const TcpConnectionCallback & cb)
{
    _onConnection = move(cb);
}

void TcpConnection::setMessageCallback(const TcpConnectionCallback & cb)
{
    _onMessage = move(cb);
}

void TcpConnection::setCloseCallback(const TcpConnectionCallback & cb)
{
    _onClose = move(cb);
}

void TcpConnection::handleConnectionCallback()
{
    if(_onConnection){
        _onConnection(shared_from_this());
    }
}

void TcpConnection::handleMessageCallback()
{
    if(_onMessage){
        _onMessage(shared_from_this());
    }
}

void TcpConnection::handleCloseCallback()
{
    if(_onClose){
        _onClose(shared_from_this());
    }
}
