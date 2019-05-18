#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;

void test()
{
    double number=1.6;
    int a=(int)number;
    int b=int(number);
    cout<<"a="<<a<<endl<<"b="<<b<<endl;
}

void test1()
{
    double a=1.666;
    int b=static_cast<int>(a);
    cout<<"a="<<a<<endl<<"b="<<b<<endl;

    int *p=static_cast<int*>(malloc(sizeof(int)));
    *p=10;
    free(p);
}

int main()
{
    test();
    test1();
    return 0;
}

