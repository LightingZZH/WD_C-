#include "InetAddress.h"
#include <string.h>

InetAddress::InetAddress(unsigned short port)
{
    memset(&_addr, 0, sizeof(struct sockaddr_in));
    _addr.sin_family = AF_INET; //表示网络层协议,ipv4
    _addr.sin_port = htons(port);   //主机字节序转网络字节序
    _addr.sin_addr.s_addr = INADDR_ANY; //inet_addr("0.0.0.0")表示本机地址
}

InetAddress::InetAddress(const string & ip, unsigned short port)
{
    memset(&_addr, 0, sizeof(struct sockaddr_in));
    _addr.sin_family = AF_INET; //表示网络层协议,ipv4
    _addr.sin_port = htons(port);   //主机字节序转网络字节序
    _addr.sin_addr.s_addr = inet_addr(ip.c_str()); //inet_addr("0.0.0.0")表示本机地址
}

InetAddress::InetAddress(const struct sockaddr_in & addr)
: _addr(addr)
{}

string InetAddress::getIp() const
{
    return string(inet_ntoa(_addr.sin_addr));   //网络字节序转点分十进制
}

unsigned short InetAddress::getPort() const
{
    return ntohs(_addr.sin_port);   //网络字节序转主机字节序
}
