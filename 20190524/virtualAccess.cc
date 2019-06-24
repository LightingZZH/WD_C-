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
    void display() 
    {
        cout<<"Base.display()"<<endl;
    }

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

    void display()
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
    Derived d(11,22);
    d.display();

    return 0;
}
