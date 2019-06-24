#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Buffer
{
public:
    Buffer(size_t sz)
    : _sz(sz)
    , _data(new char[_sz]())
    {
        cout<<"Buffer(size_t)"<<endl;
    }

    size_t size() const {return strlen(_data);}

    size_t capacity() const {return _sz;}

    char & operator[](size_t idx)
    {
        if(idx<capacity()){
            return _data[idx];
        }else{
            static char nullchar='\0';
            cout<<"小标越界!"<<endl;
            return nullchar;
        }
    }

    ~Buffer()
    {
        if(_data) delete [] _data;
        cout<<"~Buffer()"<<endl;
    }

private:
    size_t _sz;
    char * _data;
};

int main()
{
    const char * pstr="hello,world!";
    cout<<"pstr="<<pstr<<endl;
    Buffer buffer(20);
    size_t sz=strlen(pstr);
    for(size_t idx=0;idx!=sz;++idx)
    {
        buffer[idx]=pstr[idx];
        //buffer.operator[](idx)=pstr[idx];
    }
    cout<<"buffer :";
    for(size_t idx=0;idx!=buffer.size();++idx)
    {
        cout<<buffer[idx]<<" ";
    }
    cout<<endl;

    return 0;
}

