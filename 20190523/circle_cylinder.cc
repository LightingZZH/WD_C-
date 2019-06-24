#include <iostream>
using std::cout;
using std::endl;

class Circle
{
public:
    Circle()
    : _r(0)
    {
        cout<<"Circle()"<<endl;
    }

    Circle(double r)
    : _r(r)
    {
        cout<<"Circle(double)"<<endl;
    }

    double getArea()    //获取圆的面积
    {
        return 3.14*_r*_r;
    }

    double getPerimeter()   //获取圆的周长
    {
        return 6.28*_r;
    }

    void show()
    {
        cout<<"Circle's radius : "<<_r<<endl;
        cout<<"Circle's perimeter : "<<getPerimeter()<<endl;
        cout<<"Circle's area : "<<getArea()<<endl;
    }

private:
    double _r;
};

class Cylinder
: public Circle
{
public:
    Cylinder(double r, double h)
    : Circle(r)
    , _h(h)
    {
        cout<<"Cylinder(double, double)"<<endl;
    }

    double getVolume()  //获取圆柱体的体积
    {
        return getArea()*_h;
    }

    void showVolume()
    {
        cout<<"Cylinder's volume : "<<getVolume()<<endl;
    }

private:
    double _h;
};

int main()
{
    Cylinder cylider(2,5);
    cylider.show();
    cylider.showVolume();

    return 0;
}

