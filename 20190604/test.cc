#include <iostream>
#include <memory>
using namespace std;

class A
{
public:
    virtual void display() = 0;
}; 

class B
: public A
{
//public:
//    void display()
//    {
//        cout<<"B::display()"<<endl;
//    }
};

class C
: public B
{
public:
    void display()
    {
        cout<<"C::display()"<<endl;
    }

    ~C()
    {   cout<<"~C()"<<endl; }
};

class D
: public B
{
public:
    void display()
    {
        cout<<"D::display()"<<endl;
    }

    ~D()
    {   cout<<"~D()"<<endl; }
};

int main()
{
    shared_ptr<A> p(new C());
    //A *p = new C();
    p->display();

    shared_ptr<A> q(new D());
    //A *q = new D();
    q->display();

    return 0;
}

