#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class CowString
{
    class CharProxy
    {
    public:
        CharProxy(CowString &str,int index)
        : _str(str)
        , _index(index)
        {
            cout<<"CharProxy(CowString &,int)"<<endl;
        }

        char & operator=(char ch);

        operator char()
        {
            return _str._pstr[_index];
        }
    private:
        CowString & _str;
        size_t _index;
    };
public:
    CowString();
    CowString(const char *pstr);
    CowString(const CowString & rhs);
    CowString & operator=(const CowString & rhs);
    ~CowString();

    const char * c_str() const {return _pstr;}
    int size() const {return strlen(_pstr);}
    int refcount() {return *((int*)(_pstr-4));}
    CharProxy operator[](int idx);

    friend std::ostream & operator<<(std::ostream & os,const CowString & rhs);

private:
    void initRefCount() {*((int*)(_pstr-4))=1;}
    void increaseRefCount() {++*((int*)(_pstr-4));}
    void decreaseRefCount() {--*((int*)(_pstr-4));}
    void release()
    {
        decreaseRefCount();
        if(refcount()==0){
            delete [] (_pstr-4);
            cout<<">> delete data!"<<endl;
        }
    }

private:
    char * _pstr;
};

CowString::CowString()
: _pstr(new char[5]()+4)   //4+1=5
{
    cout<<"CowString()"<<endl;
    initRefCount();
}

CowString::CowString(const char *pstr)
: _pstr(new char[strlen(pstr)+5]()+4)
{
    cout<<"CowString(const char *)"<<endl;
    initRefCount();
    strcpy(_pstr,pstr);
}

CowString::CowString(const CowString & rhs)
: _pstr(rhs._pstr)
{
    cout<<"CowString(const CowString &)"<<endl;
    increaseRefCount();
}

CowString & CowString::operator=(const CowString & rhs)
{
    cout<<"CowString & operator=(const CowString &)"<<endl;
    if(this!=&rhs){
        release();
        _pstr=rhs._pstr;
        increaseRefCount();
    }
    return *this;
}

CowString::~CowString()
{
    release();
}


std::ostream & operator<<(std::ostream & os, const CowString & rhs)
{
    os<<rhs._pstr;
    return os;
}

CowString::CharProxy CowString::operator[](int idx)
{
    cout<<"CharProxy & operator[](int)"<<endl;
    return CharProxy(*this,idx);
}

char & CowString::CharProxy::operator=(char ch)
{
    cout<<"char & opreator=(char)"<<endl;
    if(_index>=0 && _index<strlen(_str._pstr))
    {
        if(1==_str.refcount()){
            _str._pstr[_index] = ch;
            return _str._pstr[_index];
        }else{
            _str.decreaseRefCount();
            char *stmp = new char[strlen(_str._pstr)+5]()+4;
            strcpy(stmp,_str._pstr);
            _str._pstr=stmp;
            _str._pstr[_index] = ch;
            _str.initRefCount();
            return _str._pstr[_index];
        }
    }else{
        cout<<"下标越界!"<<endl;
        static char nullchar='\0';
        return nullchar;
    }
}

int main()
{
    CowString s;
    cout<<"s = "<<s<<endl;

    CowString s1("hello,world");
    CowString s2(s1);
    CowString s3("shenzhen");
    s3=s2;

    cout<<"s1= "<<s1<<endl;
    cout<<"s2= "<<s2<<endl;
    cout<<"s3= "<<s3<<endl;
    printf("s1's address: %p\n",s1.c_str());
    printf("s2's address: %p\n",s2.c_str());
    printf("s3's address: %p\n",s3.c_str());
    cout<<"s1's refcount()= "<<s1.refcount()<<endl;
    cout<<"s2's refcount()= "<<s2.refcount()<<endl;
    cout<<"s3's refcount()= "<<s3.refcount()<<endl;
    
    cout<<endl<<"------------s1[0]='H'--------------"<<endl;
    s1[0]='H';
    cout<<"s1= "<<s1<<endl;
    cout<<"s2= "<<s2<<endl;
    cout<<"s3= "<<s3<<endl;
    printf("s1's address: %p\n",s1.c_str());
    printf("s2's address: %p\n",s2.c_str());
    printf("s3's address: %p\n",s3.c_str());
    cout<<"s1's refcount()= "<<s1.refcount()<<endl;
    cout<<"s2's refcount()= "<<s2.refcount()<<endl;
    cout<<"s3's refcount()= "<<s3.refcount()<<endl;
    
    cout<<endl<<"--------------------------"<<endl;
    cout<<"s2[0]= "<<s2[0]<<endl;
    cout<<"s1= "<<s1<<endl;
    cout<<"s2= "<<s2<<endl;
    cout<<"s3= "<<s3<<endl;
    printf("s1's address: %p\n",s1.c_str());
    printf("s2's address: %p\n",s2.c_str());
    printf("s3's address: %p\n",s3.c_str());
    cout<<"s1's refcount()= "<<s1.refcount()<<endl;
    cout<<"s2's refcount()= "<<s2.refcount()<<endl;
    cout<<"s3's refcount()= "<<s3.refcount()<<endl;

    return 0;
}

