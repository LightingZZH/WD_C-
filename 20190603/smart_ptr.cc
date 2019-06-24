#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Point
{
public:
    Point(int x = 0, int y = 0)
    : _x(x)
    , _y(y)
    {   cout<<"Point(int, int)"<<endl;  }

    void print() const
    {
        cout<<"("<<_x<<","<<_y<<")"<<endl;
    }

    ~Point() {  cout<<"~Point()"<<endl; }
private:
    int _x;
    int _y;
};

void test1()
{
    Point *pt = new Point(1,2);
    auto_ptr<Point> ap(pt);
    //get()返回指向被管理对象的指针 
    cout<<"ap's get = "<<ap.get()<<endl;
    cout<<"pt = "<<pt<<endl;

    ap->print();
    (*ap).print();

    auto_ptr<Point> ap2(ap);    //看起来是复制语义
    cout<<"ap2:"<<endl;         //但底层完成的是所有权的转移
    ap2->print();               //即原指针不能再使用
    (*ap2).print();
    //cout<<"ap:"<<endl;
    //ap->print();              //会发生段错误
    //(*ap).print();
}

unique_ptr<Point> getPoint()
{
    unique_ptr<Point> point(new Point(3,4));
    return point;
}

void test2()
{
#if 1
    Point *pt = new Point(1,2);
    unique_ptr<Point> ap(pt);
    cout<<"ap's get = "<<ap.get()<<endl;
    cout<<"pt = "<<pt<<endl;

    ap->print();
    (*ap).print();

    //unique_ptr不能进行复制或者赋值
    //unique_ptr<Point> ap2(ap);
    //unique_ptr<Point> ap2 = ap;

    //unique_ptr具有移动语义
    unique_ptr<Point> up = getPoint();
    up->print();
    cout<<"-----------"<<endl;
#endif

    //unique_ptr可以作为容器的元素存在
    vector<unique_ptr<Point>> points;
    points.push_back(unique_ptr<Point>(new Point(3,4)));
    points.push_back(unique_ptr<Point>(new Point(3,4)));
    points.push_back(unique_ptr<Point>(new Point(3,4)));

    points.push_back(move(ap));
    points.push_back(move(up));
}

shared_ptr<Point> getPoint1()
{
    shared_ptr<Point> point(new Point(3, 4));
    return point;
}

void test3()
{
    Point *pt = new Point(1,2);
    shared_ptr<Point> ap(pt);
    cout<<"ap's get = "<<ap.get()<<endl;
    cout<<"pt = "<<pt<<endl;

    ap->print();
    (*ap).print();

    cout<<"ap.get() = "<<ap.get()<<endl;
    cout<<"ap.use_cout() = "<<ap.use_count()<<endl;

    shared_ptr<Point> ap2(ap);
    cout<<"ap2.get() = "<<ap2.get()<<endl;
    cout<<"ap.use_cout() = "<<ap.use_count()<<endl;
    
    {
        shared_ptr<Point> ap3 = ap;
        cout<<"ap3.get() = "<<ap3.get()<<endl;
        cout<<"ap.use_cout() = "<<ap.use_count()<<endl;
    }

    cout<<"ap.use_cout() = "<<ap.use_count()<<endl;

    cout<<"-----------"<<endl;
    shared_ptr<Point> sp = getPoint1();
    cout<<"-----------"<<endl;
    sp = ap;
    cout<<"sp.get() = "<<sp.get()<<endl;
    cout<<"ap.use_cout() = "<<ap.use_count()<<endl;

    cout<<"shared_ptr可以作为容器的元素存在"<<endl;
    vector<shared_ptr<Point>> points;
    points.push_back(shared_ptr<Point>(new Point(3,4)));
    points.push_back(shared_ptr<Point>(new Point(3,4)));
    points.push_back(shared_ptr<Point>(new Point(3,4)));

    points.push_back(move(ap));
    points.push_back(sp);

    //move(ap)后ap不能够再使用
    cout<<"ap.use_count() = "<<ap.use_count()<<endl;
    cout<<"sp.use_count() = "<<sp.use_count()<<endl;
    cout<<"ap2.use_count() = "<<ap2.use_count()<<endl;
}

int main()
{
    //test1();
    //test2();
    test3();
    return 0;
}

