/*函数适配器*/

#include <iostream>
#include <functional>
using namespace std;

void display()
{
    cout<<"display()"<<endl;
}

void (*f)() = display;  //函数指针

typedef void (*Function)();

void test0()
{
    f();
    Function f1 = display;
    f1();
}

void add(int x, int y)
{
    cout<<"add()"<<endl;
    cout<<"x+y = "<<x+y<<endl;
}

struct Example
{
    void add(int x, int y)
    {
        cout<<"Example::add()"<<endl;
        cout<<"x+y = "<<x+y<<endl;
    }
//private:
    int _x = 10;
};

void test1()
{
    auto f = display;
    f();
    cout<<"-------------"<<endl;
    auto f1 = bind(&add, 1, 2); //可以绑定普通函数
    f1();
    cout<<"-------------"<<endl;
    auto f6 = bind(add, 1, 2);  //对于普通函数也可以不&，函数名就是函数首地址
    f6();
    cout<<"-------------"<<endl;
    
    Example example;

    //对于成员函数，绑定时必须要加上&
    auto f2 = bind(&Example::add, &example, 1, 2);  //this指针，传递地址
    f2();
    cout<<"-------------"<<endl;

    auto f3 = bind(&Example::add, example, 1, 2);   //传递对象，值传递
    f3();
    cout<<"-------------"<<endl;

    //占位符
    using namespace std::placeholders;
    auto f4 = bind(&Example::add, &example, _1, _2);
    f4(11, 22);
    cout<<"-------------"<<endl;

    auto f5 = bind(&Example::_x, &example);
    cout<<f5()<<endl;
}

void print(int x1, int x2, int &x3, int x4)
{
    cout<<"("<<x1<<","<<x2<<") -> ("
        <<x3<<","<<x4<<")"<<endl;
}

void test2()
{
    using namespace std::placeholders;
    int a = 100;

    //占位符本身所占位置为形参的位置
    auto f = bind(&print, _1, _2, ref(a), a);
    a = 101;
    f(11,22,33,44,55);
    cout<<"-------------"<<endl;
    
    //占位符本身的数字代表实参的位置
    auto f1 = bind(print, _3, _4, ref(a), _1);
    a = 102;
    f1(11, 22, 33, 44, 55);
}

void test3()
{
    using namespace std::placeholders;
    int a = 100;

    //std::function称为函数的容器，只能保存一个函数
    function<void(int, int)> f = bind(print, _1, _2, ref(a), a);
    a = 101;
    f(11, 22);
    cout<<"-------------"<<endl;

    function<void(int)> f1 = bind(print, _1, 100, ref(a), a);
    f1(111);
    cout<<"-------------"<<endl;

    function<void()> f2 = display;
    f2();
    cout<<"-------------"<<endl;

    f2 = bind(&Example::add, Example(), 1, 2);
    f2();
    cout<<"-------------"<<endl;

    f2 = bind(print, 1, 2, ref(a), 4);
    a = 3;
    f2();

}

int main()
{
    cout<<"--------------test0-------------"<<endl;
    test0();    //函数指针
    cout<<"--------------test1-------------"<<endl;
    test1();    //bind
    cout<<"--------------test2-------------"<<endl;
    test2();    //占位符
    cout<<"--------------test3-------------"<<endl;
    test3();    //function<>

    return 0;
}

