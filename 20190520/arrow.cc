#include <iostream>
using std::cout;
using std::endl;

class Data
{
public:
    Data(int ix=0)
    : _ix(ix)
    {
        cout<<"Data(int)"<<endl;
    }

    int get_ix() const {return _ix;}

    ~Data() {cout<<"~Data()"<<endl;}

private:
    int _ix;
};

class MiddleLayer
{
public:
    MiddleLayer(Data * pMid)
    : _pMid(pMid)
    {
        cout<<"MiddleLayer()"<<endl;
    }

    Data * operator->() {return _pMid;} //返回指针
    Data & operator*() {return *_pMid;} //返回对象

    ~MiddleLayer()
    {
        cout<<"~MiddleLayer()"<<endl;
        if(_pMid) delete _pMid;
    }
private:
    Data * _pMid;
};

class ThirdLayer
{
public:
    ThirdLayer(MiddleLayer * ml)
    : _ml(ml)
    {
        cout<<"ThirdLayer()"<<endl;
    }

    MiddleLayer & operator->() {return *_ml;}   //返回对象

    ~ThirdLayer()
    {
        cout<<"~ThirdLayer()"<<endl;
    }

private:
    MiddleLayer * _ml;
};

void test()
{   
    MiddleLayer ml(new Data(10));
    ml->get_ix();
    (*ml).get_ix();

    cout<<ml->get_ix()<<endl;
    cout<<ml.operator->()->get_ix()<<endl;
    cout<<endl;

    ThirdLayer tl(new MiddleLayer(new Data(11)));
    cout<<tl->get_ix()<<endl;
    cout<<tl.operator->().operator->()->get_ix()<<endl;
}

int main()
{
    test();
    return 0;
}

