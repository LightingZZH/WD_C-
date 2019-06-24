#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"
#include "unistd.h"
#include <assert.h>
#include <sys/eventfd.h>
#include <iostream>
using namespace std;

EventLoop::EventLoop(Acceptor & acceptor)
: _efd(createEpollFd())
, _eventfd(createEventFd())
, _acceptor(acceptor)
, _eventList(1024)
, _isLooping(false)
{
    addEpollFdRead(_acceptor.getFd());
    addEpollFdRead(_eventfd);
}

int EventLoop::createEpollFd()
{
    int ret = epoll_create1(0);
    if(ret == -1){
        perror("epoll_create1");
    }
    return ret;
}

int EventLoop::createEventFd()
{
    int ret = eventfd(0, 0);
    if(ret == -1){
        perror("eventfd");
    }
    return ret;
}

bool EventLoop::isConnectionClosed(int fd)
{
    int ret;
    do{
        char buff[1024];
        ret = recv(fd, buff, sizeof(buff), MSG_PEEK);
    }while(ret == -1 && errno == EINTR);
    return (ret == 0);
}

void EventLoop::loop()
{
    _isLooping = true;
    while(_isLooping){
        waitEpollFd();
    }
}

void EventLoop::unloop()
{
    if(_isLooping)
        _isLooping = false;
}

void EventLoop::runInLoop(Functor && cb)
{
    {
        MutexLockGuard autoLock(_mutex);
        _PendingFunctors.push_back(move(cb));
    }
    wakeup();
}

void EventLoop::waitEpollFd()
{
    int nready;
    do{
        nready = epoll_wait(_efd, &(*_eventList.begin()), _eventList.size(), 5000);
    }while(nready == -1 && errno == EINTR);

    if(nready == -1){
        perror("epoll_wait");
        return ;
    }else if(nready == 0){
        cout<<">> epoll_wait timeout!"<<endl;
    }else{
        if(nready == _eventList.size()){
            _eventList.resize(2 * nready);
        }
        for(int idx = 0; idx != nready; ++idx){
            int fd = _eventList[idx].data.fd;
            if(fd == _acceptor.getFd()){
                if(_eventList[idx].events & EPOLLIN){
                    handleNewConnection();
                }
            }else if(fd == _eventfd){
                if(_eventList[idx].events & EPOLLIN){
                    handleRead();
                    cout<<">> before doPendingFunctors()"<<endl;
                    doPendingFunctors();    //在这里发送数据
                    cout<<">> after doPendingFunctors()"<<endl;
                }
            }else{
                if(_eventList[idx].events & EPOLLIN){
                    handleMessag(fd);
                }
            }
        }
    }
}

void EventLoop::handleNewConnection()
{
    int peerfd = _acceptor.accept();
    addEpollFdRead(peerfd);
    TcpConnectionPtr conn(new TcpConnection(peerfd, this));
    conn->setConnectionCallback(_onConnection);
    conn->setMessageCallback(_onMessage);
    conn->setCloseCallback(_onClose);

    _conns.insert(std::make_pair(peerfd, conn));

    conn->handleConnectionCallback();
}

void EventLoop::handleMessag(int fd)
{
    bool isClosed = isConnectionClosed(fd);
    auto iter = _conns.find(fd);
    assert(iter != _conns.end());

    if(!isClosed){
        iter->second->handleMessageCallback();
    }else{
        delEpollFdRead(fd);
        iter->second->handleCloseCallback();
        _conns.erase(iter);
    }
}

void EventLoop::handleRead()
{
    uint64_t howmany;
    int ret = read(_eventfd, &howmany, sizeof(howmany));
    if(ret != sizeof(howmany)){
        perror("read");
    }
}

void EventLoop::wakeup()
{
    uint64_t one = 1;
    int ret = write(_eventfd, &one, sizeof(one));
    if(ret != sizeof(one)){
        perror("write");
    }
}

void EventLoop::doPendingFunctors()
{
    vector<Functor> tmp;
    {
        MutexLockGuard autoLock(_mutex);
        tmp.swap(_PendingFunctors);
    }
    for(auto & functor : tmp)
    {
        functor();
    }
}


void EventLoop::addEpollFdRead(int fd)
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    int ret = epoll_ctl(_efd, EPOLL_CTL_ADD, fd, &event);
    if(-1 == ret) perror("epoll_ctl");
}

void EventLoop::delEpollFdRead(int fd)
{
    struct epoll_event event;
    event.data.fd = fd;
    int ret = epoll_ctl(_efd, EPOLL_CTL_DEL, fd, &event);
    if(-1 == ret) perror("epoll_ctl");
}
