#include <iostream>
using std::cout;
using std::endl;

void test()
{
    int number=1;
    int &ref=number;    //reference

    cout<<"ref="<<ref<<endl<<"number"<<number<<endl;
    ref=2;
    cout<<"ref="<<ref<<endl<<"number"<<number<<endl;
    
    int number1=3;
    ref=number1;    //赋值语句
    cout<<"ref="<<ref<<endl<<"number"<<number<<endl;
    
    cout<<"&ref="<<&ref<<endl;
    cout<<"&number"<<&number<<endl;
    cout<<"&number1"<<&number1<<endl;
}

void swap(int &a,int &b)
{
    int tmp=a;
    a=b;
    b=tmp;
}

void test1()
{
    int a=3,b=4;
    cout<<"a="<<a<<" "<<"b="<<b<<endl;
    swap(a,b);
    cout<<"a="<<a<<" "<<"b="<<b<<endl;
}

int arr[3]={0,1,2};
int &index(int idx)
{
    return arr[idx];
}
int &func()
{
    int *p=new int(10);
    return *p;
}

void test2()
{
    index(0)=3;
    cout<<"arr[0]="<<arr[0]<<endl;

    int &ret=func();
    cout<<"ret="<<ret<<endl;
    delete &ret;
}

int main()
{
    test();
    cout<<"---------"<<endl;
    test1();
    cout<<"----------"<<endl;
    test2();
}
