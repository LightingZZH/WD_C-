#include <iostream>
using std::cout;
using std::endl;

class Point
{
public:
    Point()=default;
    
    //explicit
    Point(int x,int y=0)
    : _x(x)
    , _y(y)
    {
        cout<<"Point(int,int)"<<endl;
    }

    Point(const Point & rhs)
    {
        _x=rhs._x;
        _y=rhs._y;
        cout<<"Point(const Point &)"<<endl;
    }
 //委托函数   
#if 0
    Point(int x)
    : Point(x,0)
    {
        cout<<"Point(int)"<<endl;
    }
#endif

    void print()
    {
        cout<<"("<<_x<<","<<_y<<")"<<endl;
    }

    ~Point()
    {
        cout<<"~Point()"<<endl;
    }
private:
    int _x=10;
    int _y=10;
};

int main()
{
    Point pt;
    pt.print();

    Point pt1=5;
    pt1.print();

    return 0;
}

