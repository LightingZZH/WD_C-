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

    void print()
    {
        cout<<"("<<_x<<","<<_y<<")";
    }

    ~Point()
    {
        cout<<"~Point()"<<endl;
    }
private:
    int _x;
    int _y;
};

class Line
{
public:
    Line(int x1,int y1,int x2,int y2)
    : _pt1(x1,y1)
    , _pt2(x2,y2)
    {
        cout<<"Line(int,int,int,int)"<<endl;
    }
    
    void printLine()
    {
        _pt1.print();
        cout<<"--->";
        _pt2.print();
        cout<<endl;
    }
    ~Line()
    {
        cout<<"~Line()"<<endl;
    }
private:
    Point _pt1;
    Point _pt2;
};

int main()
{
    Line line(1,2,3,4);
    line.printLine();
    return 0;
}

