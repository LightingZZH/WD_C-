#include <iostream>
#include <math.h>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

class Figure
{
public:
    virtual void display() const = 0;
    virtual double area() const = 0;

    virtual ~Figure() {}
};

class Rectangle
: public Figure
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

    ~Rectangle() {  cout << "~Rectangle()" << endl; }

private:
    size_t _length;
    size_t _width;

};

class Circle
: public Figure
{
public:
    Circle(double radius)
        : _radius(radius)
    {}

    void display() const
    {   cout << "circle";   }

    double area() const
    {   return 3.14159 * _radius * _radius; }

    ~Circle() { cout << "~Circle()" << endl;    }

private:
    double _radius;

};

class Triangle
: public Figure
{
public:
    Triangle(size_t a, size_t b, size_t c)
        : _a(a)
          , _b(b)
          , _c(c)
    {}

    void display() const
    {   cout << "triangle"; }

    double area() const
    {
        size_t p = (_a + _b + _c) / 2;
        return sqrt(p * (p - _a) * (p - _b) * (p - _c));

    }

    ~Triangle() {   cout << "~Triangle()" << endl;  }   

private:
    size_t _a;
    size_t _b;
    size_t _c;

};

class Factory
{
public:
    virtual Figure * create() = 0;
    virtual ~Factory() {}
};

class RectangleFactory
: public Factory
{
public:
    Figure * create()
    {   return new Rectangle(3,4);  }
};

class TriangleFactory
: public Factory
{
public:
    Figure * create()
    {   return new Triangle(3,4,5); }
};

class CircleFactory
: public Factory
{
public:
    Figure * create()
    {   return new Circle(10);  }
};

void display(Figure * f)
{
    f->display();
    cout<<"'s area = "<<f->area()<<endl; 
}

int main()
{
    unique_ptr<Factory> rectangleFactory(new RectangleFactory());
    unique_ptr<Figure> rectangle(rectangleFactory->create());
    display(rectangle.get());

    unique_ptr<Factory> triangleFactory(new TriangleFactory());
    unique_ptr<Figure> triangle(triangleFactory->create());
    display(triangle.get());

    unique_ptr<Factory> circleFactory(new CircleFactory());
    unique_ptr<Figure> circle(circleFactory->create());
    display(circle.get());

    return 0;
}

