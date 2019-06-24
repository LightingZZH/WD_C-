#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "Socket.h"
#include "InetAddress.h"
#include "SocketIO.h"
#include "Noncopyable.h"
#include <string>
using std::string;

class TcpConnection
: Noncopyable
{
public:
    TcpConnection(int fd);
    ~TcpConnection();

    string receive();
    void send(const string & msg);

    string toString() const;
    void shutdown();

private:
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();
private:
    Socket _sock;
    SocketIO _socketIO;
    InetAddress _localAddr;
    InetAddress _peerAddr;
    bool _isShutdownWrite;
};

#endif
