#include <iostream>
using namespace std;

template<class T>
class RAII
{
public:
    RAII(T * data)
        : _data(data)
    {   cout<<"RAII(T *)"<<endl;    }

    T * operator->()
    {   return _data;   }

    T & operator*()
    {   return *_data;  }

    T * get()   {   return _data;   }

    void reset(T *data)
    {
        if(_data) delete _data;
        _data = data;
    }

    ~RAII()
    {
        if(_data){
            delete _data;
            cout<<"~RAII()"<<endl;
        }
    }
private:
    T *_data;
};

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

int main()
{
    Point *pt = new Point(3,4);
    pt->print();
    (*pt).print();
    delete pt;
    cout<<"-------------"<<endl;
    RAII<Point> p(new Point(1,2));
    p->print();
    (*p).print();
    cout<<"--------------"<<endl;
    p.reset(new Point(5,6));
    p->print();
    (*p).print();

    return 0;
}
