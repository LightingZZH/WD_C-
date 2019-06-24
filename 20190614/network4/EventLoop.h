#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__
#include "MutexLock.h"
#include <map>
#include <memory>
#include <vector>
#include <sys/epoll.h>
#include <functional>
using std::vector;
using std::map;
using std::shared_ptr;

class Acceptor;
class TcpConnection;
class EventLoop
{
    using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
    using TcpConnectionCallback = std::function<void(const TcpConnectionPtr&)>;
    using Functor = std::function<void()>;
public:
    EventLoop(Acceptor & acceptor);
    void loop();
    void unloop();
    void runInLoop(Functor && cb);

    void setConnectionCallback(TcpConnectionCallback && cb)
    {   _onConnection = move(cb);   }
    void setMessageCallback(TcpConnectionCallback && cb)
    {   _onMessage = move(cb);   }
    void setCloseCallback(TcpConnectionCallback && cb)
    {   _onClose = move(cb);   }

private:
    void waitEpollFd();
    
    void handleNewConnection();
    void handleMessag(int fd);
    void handleRead();
    void wakeup();

    int createEpollFd();
    int createEventFd();
    void doPendingFunctors();

    void addEpollFdRead(int fd);
    void delEpollFdRead(int fd);
    bool isConnectionClosed(int fd);
private:
    int _efd;
    int _eventfd;
    Acceptor & _acceptor;
    vector<struct epoll_event> _eventList;
    map<int, TcpConnectionPtr> _conns;
    bool _isLooping;

    MutexLock _mutex;
    vector<Functor> _PendingFunctors;

    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
};

#endif
