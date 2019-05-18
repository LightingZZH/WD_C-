#include <iostream>
#include <stdlib.h>
using std::cout;
using std::endl;

void test()
{
    int *p=(int*)malloc(sizeof(int));
    *p=10;
    cout<<"*p="<<*p<<endl;
    free(p);
}

void test1()
{
    int *p1=new int(10);
    cout<<"*p1="<<*p1<<endl;
    delete p1;

    int *parray=new int[10]();
    for(int i=0;i!=10;++i){
        cout<<parray[i]<<" ";
    }
    cout<<endl;
    delete []parray;
}

int main()
{
    std::cout << "Hello world" << std::endl;
    test();
    test1();
    return 0;
}

