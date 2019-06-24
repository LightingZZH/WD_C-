#ifndef __TCPCONNETION_H__
#define __TCPCONNETION_H__

#include "Socket.h"
#include "InetAddr.h"
#include "SocketIO.h"
#include "Noncopyable.h"

#include <string>
#include <memory>
#include <functional>
using std::string;
using std::function;

class EventLoop;
class TcpConnection
: Noncopyable
, public std::enable_shared_from_this<TcpConnection>
{
    using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
    using TcpConnectionCallback = function<void(const TcpConnectionPtr &)>;
public:
    TcpConnection(int fd, EventLoop*);
    ~TcpConnection();

    string receive();
    void send(const string & msg);
    void sendInLoop(const string & msg);

    string toString() const;
    void shutdown();

    void setConnectionCallback(const TcpConnectionCallback & cb);
    void setMessageCallback(const TcpConnectionCallback & cb);
    void setCloseCallback(const TcpConnectionCallback & cb);

    void handleConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();

private:
    InetAddr getLocalAddr();
    InetAddr getPeerAddr();
private:
    Socket _sock;
    SocketIO _socketIO;
    InetAddr _localAddr;
    InetAddr _peerAddr;
    bool _isShutdownWrite;

    EventLoop * _loop;

    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
};

#endif
