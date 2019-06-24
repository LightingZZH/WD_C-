#ifndef __INETADDR_H__
#define __INETADDR_H__

#include <arpa/inet.h>
#include <string>
using std::string;

class InetAddr
{
public:
    explicit
    InetAddr(unsigned short port);
    InetAddr(const string & ip, unsigned short port);
    InetAddr(const struct sockaddr_in & addr);

    string getIp() const;
    unsigned short getPort() const;
    struct sockaddr_in * getInetAddrPtr() {return &_addr;}
    ~InetAddr() {}

private:
    struct sockaddr_in _addr;
};

#endif
