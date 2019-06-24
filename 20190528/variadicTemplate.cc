#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

template <typename... Args>
void display(Args... args)
{
    //获取可变参数的个数
    cout<<sizeof...(args)<<endl;
    cout<<sizeof...(Args)<<endl;
}

template <typename T>
void print(T t)
{
    cout<<t<<endl;
}

template <typename T, typename... Args> //模板参数包
void print(T t, Args... args)
{
    cout<<t<<" ";
    print(args...);
}

int main()
{
    string str="world";
    print(1, 1.1, "hello", 'a', str);

    return 0;
}

