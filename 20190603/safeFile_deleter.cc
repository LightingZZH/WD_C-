#include <iostream>
#include <memory>
using namespace std;

class SafeFile
{
public:
    SafeFile(FILE * fp)
    : _fp(fp)
    {}

    void write(const string & msg){
        fwrite(msg.c_str(), 1, msg.size(), _fp);
    }

    ~SafeFile()
    {
        if(_fp){
            fclose(_fp);
            cout<<"~SafeFile()"<<endl;
        }
    }

private:
    FILE * _fp;
};

struct FileClose
{
    void operator()(FILE * fp) const
    {
        if(fp){
            fclose(fp);
            cout<<"FileClose"<<endl;
        }
    }
};

void test()
{
    SafeFile sf(fopen("test.txt","a+"));
    sf.write("hello, world\n");
}

void test1()
{
    unique_ptr<FILE, FileClose> up(fopen("test.txt", "a+"));
    string msg("this is unique_ptr line\n");
    fwrite(msg.c_str(), 1, msg.size(), up.get());
}

void test2()
{
    shared_ptr<FILE> sp(fopen("test.txt", "a+"), FileClose());
    string msg("this is shared_ptr line\n");
    fwrite(msg.c_str(), 1, msg.size(), sp.get());
}

int main()
{
    test1();
    cout<<"----------------"<<endl;
    test2();
    return 0;
}
