#include <iostream>
#include <math.h>
#include <functional>
using std::cout;
using std::endl;
using std::function;

class Figure
{
public:
    typedef function<void()> DisplayCallback;
    typedef function<double()> AreaCallback;

    void setDisplayCallback(DisplayCallback cb)
    {   _cb1 = cb;  }

    void setAreaCallback(AreaCallback cb)
    {   _cb2 = cb;  }

    void handleDisplayCallback()
    {
        if(_cb1){
            _cb1();
        }
    }

    double handleAreaCallback()
    {
        if(_cb2){
            return _cb2();
        }else{
            return 0;
        }
    }

private:
    DisplayCallback _cb1;   //回调函数
    AreaCallback _cb2;
};

class Rectangle
{
public:
    Rectangle(size_t length, size_t width)
        : _length(length)
          , _width(width)
    {}

    void display() const 
    {   cout << "rectangle";    }

    double area() const
    {   return _length * _width;    }

private:
    size_t _length;
    size_t _width;

};

class Circle
{
public:
    Circle(double radius)
        : _radius(radius)
    {}

    void print() const
    {   cout << "circle";   }

    double getArea() const
    {   return 3.14159 * _radius * _radius; }

private:
    double _radius;

};

class Triangle
{
public:
    Triangle(size_t a, size_t b, size_t c)
        : _a(a)
          , _b(b)
          , _c(c)
    {}

    void show() const
    {   cout << "triangle"; }

    double calcArea() const
    {
        size_t p = (_a + _b + _c) / 2;
        return sqrt(p * (p - _a) * (p - _b) * (p - _c));

    }

private:
    size_t _a;
    size_t _b;
    size_t _c;

};

void display(Figure & fig)
{
    fig.handleDisplayCallback();
    cout<<"'s area is "<<fig.handleAreaCallback()<<endl;
}

int main()
{
    Rectangle rectangle(3, 4);
    Triangle triangle(3, 4, 5);
    Circle circle(10);

    Figure figure;
    figure.setDisplayCallback(std::bind(&Rectangle::display, &rectangle));
    figure.setAreaCallback(std::bind(&Rectangle::area, &rectangle));
    display(figure);

    figure.setDisplayCallback(std::bind(&Triangle::show, &triangle));
    figure.setAreaCallback(std::bind(&Triangle::calcArea, &triangle));
    display(figure);

    figure.setDisplayCallback(std::bind(&Circle::print, &circle));
    figure.setAreaCallback(std::bind(&Circle::getArea, &circle));
    display(figure);

    return 0;
}

