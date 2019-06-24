#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
using std::cout;
using std::endl;
using std::vector;
using std::priority_queue;

void test1()
{
    int array[10] = {5, 7, 1, 2, 3, 4, 6, 9, 8, 0};
    priority_queue<int> que;
    //底层实现：堆排序
    // < ==> 大根堆
    for(int idx = 0; idx!=10 ;++idx){
        que.push(array[idx]);
        cout<<"此时优先级最高的元素是: "<<que.top()<<endl;
    }

    while(!que.empty()){
        cout<<que.top()<<" ";
        que.pop();
    }
    cout<<endl;
}

void test2()
{
    int array[10] = {5, 7, 1, 2, 3, 4, 6, 9, 8, 0};
    priority_queue<int, vector<int>, std::greater<int>> que;
    for(int idx = 0; idx!=10 ;++idx){
        que.push(array[idx]);
        cout<<"此时优先级最高的元素是: "<<que.top()<<endl;
    }

    while(!que.empty()){
        cout<<que.top()<<" ";
        que.pop();
    }
    cout<<endl;
}

class Point
{
public:
    Point(int ix = 0, int iy = 0)
        : _ix(ix)
          , _iy(iy)
    {   cout << "Point(int,int)" << endl;   }

    float getDistance() const
    {
        return sqrt(_ix * _ix + _iy * _iy);

    }

    friend std::ostream & operator<<(std::ostream &os, const Point & rhs);
private:
    int _ix;
    int _iy;

};

std::ostream & operator<<(std::ostream &os, const Point & rhs)
{
    os << "(" << rhs._ix
        << "," << rhs._iy
        << ")";
    return os;

}

bool operator<(const Point & lhs, const Point & rhs)
{
    return lhs.getDistance() < rhs.getDistance();
}

struct PointComparator
{
    bool operator()(const Point & lhs, const Point & rhs) const
    {
        return lhs.getDistance() > rhs.getDistance();

    }
};

void test3()
{
    priority_queue<Point, vector<Point>> que;
    //priority_queue<Point, vector<Point>, PointComparator> que;
    que.push(Point(1, 2));
    que.push(Point(-1, 2));
    que.push(Point(3, 2));
    que.push(Point(4, 2));
    que.push(Point(1, 6));

    while(!que.empty()){
        cout<<que.top()<<" ";
        que.pop();
    }
    cout<<endl;
}

int main()
{
    //test1();
    //cout<<"--------------"<<endl;
    //test2();
    test3();
    return 0;
}

