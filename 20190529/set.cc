#include <cmath>
#include <iostream>
#include <set>
using std::cout;
using std::endl;
using std::set;
using std::string;

template <typename Container>
void display(const Container & c)
{
    for(auto & elem : c){
        cout<<elem<<" ";
    }
    cout<<endl;
}

class Point
{
public:
    Point(int x=0, int y=0)
    : _x(x)
    , _y(y)
    {   cout<<"Point(int , int)"<<endl; }

    float getDistance() const
    {
        return sqrt(_x*_x+_y*_y);
    }

    friend std::ostream & operator<<(std::ostream &os, const Point &rhs);
private:
    int _x;
    int _y;
};

std::ostream & operator<<(std::ostream &os, const Point &rhs)
{
    os<<"("<<rhs._x<<","<<rhs._y<<")";
    return os;
}

bool operator<(const Point &lhs, const Point &rhs)
{
    return lhs.getDistance()<rhs.getDistance();
}

struct PointComparator
{
    bool operator() (const Point &lhs, const Point &rhs)
    {
        return lhs.getDistance()>rhs.getDistance();
    }
};

void test()
{
    set<Point> numbers{
    //set<Point, PointComparator> numbers{
        Point(1,2),
        Point(3,4),
        Point(5,6),
        Point(7,8)
    };
    display(numbers);
}

void test1()
{
    set<int> numbers{1, 1, 6, 6, 2, 3, 5, 1, 6, 4};
    display(numbers);

    auto ret = numbers.insert(7);
    if(ret.second){
        cout<<"success"<<endl;
        cout<<*ret.first<<endl;
    }else{
        cout<<"fail"<<endl;
        cout<<*ret.first<<endl;
    }
    display(numbers);
}

int main()
{
    test();
    cout<<"-----------"<<endl;
    test1();
}
