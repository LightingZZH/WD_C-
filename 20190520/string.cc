#include <string.h>
#include <iostream>
#include <limits>
using std::cout;
using std::endl;

class String
{
public:
    String()
    : _pstr(new char[10]())
    {
        cout<<"String()"<<endl;
    }

    String(const char *pstr)
    : _pstr(new char[strlen(pstr)+1]())
    {
        strcpy(_pstr,pstr);
        cout<<"String(const char *)"<<endl;
    }

    String(const String & rhs)
    : _pstr(new char[strlen(rhs._pstr)+1]())
    {
        strcpy(_pstr,rhs._pstr);
        cout<<"String(const String &)"<<endl;
    }

    ~String()
    {
        if(_pstr) delete [] _pstr;
        cout<<"~String()"<<endl;
    }

    String & operator=(const String & rhs)
    {
        cout<<"String & operator=(const String &)"<<endl;
        if(this!=&rhs){ //避免自复制
            delete [] _pstr;
            _pstr=new char[strlen(rhs._pstr)+1]();
            strcpy(_pstr,rhs._pstr);
        }
        return *this;
    }

    String & operator=(const char *pstr)
    {
        cout<<"String & operator=(const char *)"<<endl;
        if(this->_pstr!=pstr){
            delete [] _pstr;
            _pstr=new char[strlen(pstr)+1]();
            strcpy(_pstr,pstr);
        }
        return *this;
    }

    String & operator+=(const String & rhs)
    {
        cout<<"String & operator+=(const String &)"<<endl;
        _pstr=(char*)realloc(_pstr,strlen(_pstr)+strlen(rhs._pstr)+1);
        strcat(_pstr,rhs._pstr);
        return *this;
    }

    String & operator+=(const char *pstr)
    {
        cout<<"String & operator+=(const char *)"<<endl;
        _pstr=(char*)realloc(_pstr,strlen(_pstr)+strlen(pstr)+1);
        strcat(_pstr,pstr);
        return *this;
    }

    char & operator[](std::size_t index)
    {
        if(index<strlen(_pstr)){
            return _pstr[index];
        }else{
            static char nullchar='\0';
            cout<<"下标越界!"<<endl;
            return nullchar;
        }
    }

    const char & operator[](std::size_t index) const
    {
        if(index<strlen(_pstr)){
            return _pstr[index];
        }else{
            static char nullchar='\0';
            cout<<"下标越界!"<<endl;
            return nullchar;
        }
    }

    std::size_t size() const {return strlen(_pstr);}

    const char* c_str() const {return (const char*)_pstr;}

    friend bool operator==(const String &,const String &);
    friend bool operator!=(const String &,const String &);

    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);

    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

private:
    char *_pstr;
};

String operator+(const String & lhs, const String & rhs)
{
    String tmp(lhs);
    tmp += rhs;
    return tmp;
}

String operator+(const String & lhs, const char *pstr)
{
    String tmp(lhs);
    tmp += pstr;
    return tmp;
}

String operator+(const char *pstr, const String & rhs)
{
    String tmp(pstr);
    tmp += rhs;
    return tmp;
}

bool operator==(const String & lhs, const String & rhs)
{
    return !strcmp(lhs._pstr,rhs._pstr);
}

bool operator!=(const String & lhs, const String & rhs)
{
    return strcmp(lhs._pstr,rhs._pstr);
}

bool operator<(const String & lhs, const String & rhs)
{
    if(strcmp(lhs._pstr,rhs._pstr)<0) return true;
    else return false;
}

bool operator>(const String & lhs, const String & rhs)
{
    if(strcmp(lhs._pstr,rhs._pstr)>0) return true;
    else return false;
}

bool operator<=(const String & lhs, const String & rhs)
{
    if(strcmp(lhs._pstr,rhs._pstr)<=0) return true;
    else return false;
}

bool operator>=(const String & lhs, const String & rhs)
{
    if(strcmp(lhs._pstr,rhs._pstr)>=0) return true;
    else return false;
}

std::ostream &operator<<(std::ostream &os, const String &s)
{
    os<<s._pstr<<endl;
    return os;
}

std::istream &operator>>(std::istream &is, String &s)
{
    size_t sz=10;
    size_t i=0;
    char *p=new char[sz]();
    bzero(s._pstr,strlen(s._pstr));
    cout<<"pls input a string:"<<endl;
    while(is.get(p[i])){
        if(p[i]=='\n') break;
        if(i==sz-1) {
            sz *= 2;
            p=(char*)realloc(p,sz);
        }
        i++;
    }
    p[i]='\0';
    s += p;
    delete [] p;
    return is;
}

int main()
{
    String s1("hello");
    String s2=s1;
    cout<<"s1="<<s1<<endl;
    cout<<"s2="<<s2<<endl;

    if(s1==s2) cout<<"s1==s2"<<endl;
    else cout<<"s1!=s2"<<endl;

    String s3(",world");
    s1 += s3;
    cout<<"s1="<<s1<<endl;

    for(size_t idx=0;idx!=s1.size();++idx)
    {
        cout<<s1[idx]<<" ";
    }
    cout<<endl;

    String s4="jhjhjjg";
    String s5;
    std::cin >> s4 >> s5;
    cout<<"s4="<<s4<<endl;
    cout<<"s5="<<s5<<endl;

    return 0;
}

