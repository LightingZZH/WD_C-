#include <string.h>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

class String
{
public:
    String(const char *pstr)
    : _pstr(new char[strlen(pstr)+1]())
    {
        cout<<"String(const char *)"<<endl;
        strcpy(_pstr, pstr);
    }

    String(String && rhs)
    : _pstr(rhs._pstr)
    {
        rhs._pstr = nullptr;
        cout<<"String(String &&)"<<endl;
    }

    String & operator=(String && rhs)
    {
        cout<<"String & operator=(String &&)"<<endl;
        if(this != &rhs){
            delete [] _pstr;
            _pstr = rhs._pstr;
            rhs._pstr = nullptr;
        }
        return *this;
    }

    String(const String & rhs)
    : _pstr(new char[strlen(rhs._pstr)+1]())
    {
        cout<<"String(const String &)"<<endl;
        strcpy(_pstr, rhs._pstr);
    }

    String & operator=(const String & rhs)
    {
        if(this!=&rhs){
            delete [] _pstr;
            _pstr = new char[strlen(rhs._pstr)+1]();
            strcpy(_pstr, rhs._pstr);
            cout<<"operator=(const String &)"<<endl;
        }
        return *this;
    }

    ~String()
    {
        if(_pstr){
            delete [] _pstr;
            cout<<"~String()"<<endl;
        }
    }

    friend ostream & operator<<(ostream & os, const String & rhs);

private:
    char *_pstr;
};

ostream & operator<<(ostream & os, const String & rhs)
{
    os<<rhs._pstr;
    return os;
}

void test()
{
    //如果不使用具有移动语义的函数时
    String s1(String("hello")); //生成一个临时对象，然后拷贝给s1,不太好，可以用移动复制函数
    cout<<"s1 = "<<s1<<endl;
    cout<<"--------"<<endl;
}

void test1()
{
    vector<String> strs;
    strs.push_back("hello,world");
    cout<<"......"<<endl;

    String str1 = "wangdao";
    cout<<"str1 = "<<str1<<endl;
    cout<<"-----------"<<endl;

    strs.push_back(move(str1)); //move 可以显式把一个左值变为右值
    cout<<"------------"<<endl;

    copy(strs.begin(), strs.end(), ostream_iterator<String>(cout, " "));
    cout<<endl;

    String str2("shenzhen");
    str2 = "henggang";
    cout<<"str2 = "<<str2<<endl;
    cout<<"-------------"<<endl;
    str2 = move(str2);
    cout<<"........"<<endl;
}

//String s1("hello");

String getString()
{
    //如果返回的是全局对象，则调用复制构造函数
    //如果返回的是局部对象，则调用移动构造函数
   String s1("hello");
    return s1;
}

void test2()
{
    int a = 1, b = 2;
    cout<<"a = "<<a<<", b = "<<b<<endl;
    b = move(a);
    cout<<"a = "<<a<<", b = "<<b<<endl;
    
    getString();
}

int main()
{
    test();
    //test1();
    //test2();
    return 0;
}

