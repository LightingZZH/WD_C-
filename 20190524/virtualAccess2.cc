#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
    Base(double base)
    : _base(base)
    {
        cout<<"Base(double)"<<endl;
    }

    virtual
    void display() const 
    {
        cout<<"Base.display()"<<endl;
    }

    void func() 
    {
        this->display();
    }    //在普通成员函数中表现多态性
private:
    double _base;
};

class Derived
: public Base
{
public:
    Derived(double base, double derived)
    : Base(base)
    , _derived(derived)
    {
        cout<<"Derived(double, double)"<<endl;
    }

    void display() const
    {
        cout<<"display()"<<endl;
    }

    void display(int x) 
    {
        cout<<"Derived.display()"<<x<<endl;
    }

private:
    double _derived;
};

int main(void)
{
    Base b(22);
    b.func();

    Derived d(11,22);
    d.func();
    return 0;
}
