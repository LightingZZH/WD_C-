#include "../include/InetAddr.h"
#include <string.h>

InetAddr::InetAddr(unsigned short port)
{
    memset(&_addr, 0, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = INADDR_ANY;
}

InetAddr::InetAddr(const string &ip, unsigned short port)
{
    memset(&_addr, 0, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

InetAddr::InetAddr(const struct sockaddr_in & addr)
: _addr(addr)
{}

string InetAddr::getIp() const
{
    return string(inet_ntoa(_addr.sin_addr));
}

unsigned short InetAddr::getPort() const
{
    return ntohs(_addr.sin_port);
}
