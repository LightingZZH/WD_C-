#include <iostream>
#include <cmath>
#include <unordered_set>
using std::cout;
using std::endl;
using std::unordered_set;

class Point
{
public:
    Point(int x=0, int y=0)
    : _x(x)
    , _y(y)
    {   cout<<"Point(int, int)"<<endl;  }

    float getDistance() const
    {
        return sqrt(_x*_x + _y*_y);
    }

    int getX() const {return _x;}
    int getY() const {return _y;}

    friend std::ostream & operator<<(std::ostream &os, const Point & rhs);

private:
    int _x;
    int _y;
};

#if 1
bool operator<(const Point &lhs, const Point &rhs)
{
    return lhs.getDistance() < rhs.getDistance();
}

bool operator>(const Point &lhs, const Point &rhs)
{
    return lhs.getDistance() > rhs.getDistance();
}
#endif


std::ostream & operator<<(std::ostream& os, const Point & rhs)
{
    os<<"("<<rhs._x<<","<<rhs._y<<")"<<endl;
    return os;
}

namespace std
{
template <>
struct hash<Point>
{
    size_t operator() (const Point &rhs) const
    {
        return ((rhs.getX()*rhs.getX())>>1) ^ ((rhs.getY()*rhs.getY())>>1);
    }
};
}

struct PointHasher
{
    size_t operator() (const Point & rhs) const
    {
        return ((rhs.getX()*rhs.getX())>>1) ^ ((rhs.getY()*rhs.getY())>>1); 
    }
};

struct PointEqual
{
    bool operator() (const Point & lhs, const Point & rhs) const
    {
        return (lhs.getX() == rhs.getX()) &&
               (lhs.getY() == rhs.getY());
    }
};

void test()
{
    unordered_set<Point, PointHasher, PointEqual> points{
        Point(1,2),
        Point(1,2),
        Point(3,4),
        Point(5,6),
        Point(-1,-2),
        Point(-3,4)
    };

    auto it = points.begin();
    for(;it!=points.end();++it){
        cout<<*it;
    }
    cout<<endl;

    auto ret = points.insert(Point(-1,4));
    if(ret.second){
        cout<<"success"<<endl;
        cout<<*ret.first<<endl;
    }else{
        cout<<"fail"<<endl;
        cout<<*ret.first<<endl;
    }
}

int main()
{
    test();
    return 0;
}

