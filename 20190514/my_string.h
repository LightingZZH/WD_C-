#ifndef __MY_STRING_H__
#define __MY_STRING_H__
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class String
{
public:
    String();
    String(const char *pstr);
    String(const String & rhs);
    String & operator=(const String & rhs);
    ~String();

    void print();
private:
    char * _pstr;
};

#endif
