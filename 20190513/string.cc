#include <iostream>
using std::cout;
using std::endl;
using std::string;

void test()
{
    char str[]="hello,world";
    cout<<"str="<<str<<endl;
    const char *pstr="hello,world";
    cout<<"pstr="<<pstr<<endl;
}

void test1()
{
    int number(1);
    cout<<"number="<<number<<endl;

    string s1="hello";  //C风格
    string s2(",world");
    string s3=s1+s2;
    cout<<"s3="<<s3<<endl;

    //c++风格--->c风格
    const char *p1=s3.c_str();
    const char *p2=s3.data();
    cout<<"p1="<<p1<<endl;
    cout<<"p2="<<p2<<endl;

    cout<<"s3.size()="<<s3.size()<<" "
        <<"s3.length()"<<s3.length()<<endl;

    s3.append("!how are you?");
    cout<<"s3="<<s3<<endl;
    string s4=" I'am fine";
    s3.append(s4);
    cout<<"s3="<<s3<<endl;

    size_t pos=s3.find("how");
    string s5=s3.substr(pos,12);
    cout<<"s5="<<s5<<endl;
}

int main()
{
    test();
    test1();
    return 0;
}

