#include <iostream>
using std::cout;
using std::endl;

class Point
{
public:

    void show()
    {
        cout<<"show()"<<endl;
    }

    Point(int x,int y)
    : _x(x)
    , _y(y)
    {
        cout<<"Point(int,int)"<<endl;
    }
    
#if 1
    void print(/* Point * const this*/)
    {
        _x=100;
        cout<<"("<<_x<<","<<_y<<")"<<endl;
    }
#endif

    void print(/* const Point * const this*/) const //const 成员函数不能修改数据成员，不能调用非const成员函数
    {
       // show();//error
       // _x=1000;//error
        cout<<"("<<_x<<","<<_y<<")"<<endl;
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
    Point pt1(1,2); //非const对象两者都可调用
    pt1.print();

    const Point pt2(3,4);   //const对象只能调用const成员函数
    pt2.print();

    return 0;
}

