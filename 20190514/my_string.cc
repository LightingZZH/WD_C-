#include "my_string.h"

String::String()
: _pstr(nullptr)
{
    cout<<"String()"<<endl;
}

String::String(const char *pstr)
: _pstr(new char[strlen(pstr)+1]())
{
    strcpy(_pstr,pstr);
    cout<<"String(const char*)"<<endl;
}

String::String(const String & rhs)
: _pstr(new char[strlen(rhs._pstr)+1]())
{
    strcpy(_pstr,rhs._pstr);
    cout<<"String(const String & rhs)"<<endl;
}

String& String::operator=(const String & rhs)
{
    if(this != &rhs){
        delete [] _pstr;
        _pstr=new char[strlen(rhs._pstr)+1]();
        strcpy(_pstr,rhs._pstr);
    }
    cout<<"operator=(const String & )"<<endl;
    return *this;
}

String::~String()
{
    delete [] _pstr;
    cout<<"~String()"<<endl;
}

void String::print()
{
    if(_pstr){
        cout<<_pstr<<endl;
        printf("_pstr=%p\n",_pstr);
    }
}
