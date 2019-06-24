#ifndef __SOCKET_H__
#define __SOCKET_H__

class Socket
{
public:
    Socket();
    explicit Socket(int fd);

    int getFd();
    
    void shutdownWrite();

    ~Socket();

private:
    int _fd;
};

#endif
