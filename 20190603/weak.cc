#include <iostream>
#include <memory>
using namespace std;

class Point
{
public:
    Point(int ix = 0, int iy = 0)
        : _ix(ix)
          , _iy(iy)
    {   cout << "Point(int,int)" << endl;   }

    void print() const
    {
        cout << "(" << _ix
            << "," << _iy
            << ")" << endl;

    }

    ~Point() {  cout << "~Point()" << endl; }

private:
    int _ix;
    int _iy;

};

void test()
{
    weak_ptr<Point> wp;

    {
        shared_ptr<Point> sp(new Point(1,2));
        wp = sp;

        cout << "wp's use_count = " << wp.use_count() << endl;
        cout << "sp's use_count = " << sp.use_count() << endl;
        //weak_ptr所托管的对象是否还存活
        cout<<"wp's expired = "<<wp.expired()<<endl;

        shared_ptr<Point> sp2 = wp.lock();
        cout << "sp's use_count = " << sp.use_count() << endl;
        if(sp2){
            cout<<"wp 提升成功"<<endl;
            sp2->print();
        }else{
            cout<<"wp 提升失败"<<endl;
        }
    }
    cout<<"------------------"<<endl;
    cout << "wp's expired = " << wp.expired() << endl;//对象已经被销毁，到期

    shared_ptr<Point> sp2 = wp.lock();
    if(sp2){
        cout<<"wp 提升成功"<<endl;
        sp2->print();
    }else{
        cout<<"wp 提升失败"<<endl;
    }

}

int main()
{
    test();
    return 0;
}

