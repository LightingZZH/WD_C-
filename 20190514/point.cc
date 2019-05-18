#include <iostream>
using std::cout;
using std::endl;

class Point
{
public:
    Point(int x=0,int y=0)
    : _x(x)
    , _y(y)
    {
        cout<<"Point(int,int)"<<endl;
    }

    Point(const Point & rhs)
    : _x(rhs._x)
    , _y(rhs._y)
    {
        cout<<"Point(const Point &)"<<endl;
    }

    Point & operator=(const Point & rhs)
    {
        this->_x=rhs._x;
        this->_y=rhs._y;
        cout<<"Point & operator=(const Point & rhs)"<<endl;
        return *this;
    }
    
    //隐含的this指针，在编译时会自动加上
    void print()
    {
        cout<<"("<<this->_x
            <<","<<this->_y
            <<")"<<endl;
    }

    ~Point()
    {
        cout<<"~Point()"<<endl;
    }
private:
    int _x;
    int _y;
};

int main()
{
    Point pt;
    pt.print();
    Point pt1(1,2);
    pt1.print();

    Point pt2=pt1;
    cout<<"pt2-->"<<endl;
    pt2.print();
    cout<<"----------"<<endl;

    pt=pt2=pt1;
    cout<<"pt-->"<<endl;
    pt.print();
    cout<<"---------------"<<endl;

    Point *pt3=new Point(3,4);
    pt3->print();
    delete pt3;

    return 0;
}
