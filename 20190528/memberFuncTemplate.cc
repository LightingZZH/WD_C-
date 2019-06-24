#include <iostream>
#include <vector>
#include <list>
using std::cout;
using std::endl;
using std::vector;
using std::list;

class Point
{
public:
    Point(double x, double y)        
    : _x(x)
    , _y(y)
    {   cout<<"Point(double, double)"<<endl;    }

    template <typename T>
    T cast(T t)
    {
        return t*_x;
    }

private:
    double _x;
    double _y;
};

class Data
{
public:
    Data(int sz)
    : _sz(sz)
    , _data(new int[_sz]())
    {   cout<<"Data(int)"<<endl;    }

    template <typename Iterator>
    Data(Iterator beg, Iterator end)
    : _sz(end-beg)
    , _data(new int[_sz]())
    {
        setData(beg, end);
    }

    template <typename Iterator>
    void setData(Iterator beg, Iterator end)
    {
        int idx=0;
        while(beg!=end)
        {
            _data[idx] = *beg;
            ++beg;
            ++idx;
        }
    }

    ~Data()
    {
        if(_data){
            delete [] _data;
            cout<<"~Data()"<<endl;
        }
    }

    void print() const
    {
        for(int idx=0; idx!=_sz; ++idx)
        {
            cout<<_data[idx]<<" ";
        }
        cout<<endl;
    }

private:
    int _sz;
    int *_data;
};

void test()
{
    Point pt(1.11, 2.22);
    int a = 3;
    cout<<pt.cast(a)<<endl;
}

void test1()
{
    vector<int> number {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    list<int> number1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    Data data(10);
    data.setData(number.begin(), number.end());
    data.print();
}

void test2()
{
    vector<int> number {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Data data(number.begin(), number.end());
    data.print();
}

int main()
{
    test();
    test1();
    test2();
    return 0;
}

