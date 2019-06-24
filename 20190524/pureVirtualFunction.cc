#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
    Base() {cout<<"Base()"<<endl;}
    
    virtual
    void display() = 0; //纯虚函数作为接口存在，没有实现

    virtual void show() = 0;
};

class Derived1  //也是个抽象类
: public Base
{
public:
    void display() {cout<<"Derived1.display()"<<endl;}
};

class Derived2
: public Derived1
{
public:
    void show() {cout<<"Derived2.show()"<<endl;}
    void display() {cout<<"Derived2.display()"<<endl;}
};

void display(Base *p)
{
    p->display();
    p->show();
}

int main()
{
    //Base base;  //variable type 'Base' is an abstract class 抽象类不能创建对象
    //Base *p = nullptr;    //可以定义指针

   // Derived1 d1;    //variable type 'Derived1' is an abstract class
   // display(&d1);

    Derived2 d2;
    display(&d2);

    return 0;
}

