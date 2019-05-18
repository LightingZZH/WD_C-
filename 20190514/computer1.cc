#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Computer
{
public:
    Computer(const char *brand,float price);
#if 0
    Computer(const Computer & rhs)  //默认复制构造函数
    : _brand(rhs._brand)    //浅拷贝
    , _price(rhs.price)
    {}
#endif

#if 0
    Computer & operator=(const Computer & rhs)  //默认运算符函数
    {
        _brand=rhs._brand;
        _price=rhs._price;
        return *this;
    }
#endif

    Computer & operator=(const Computer & rhs)
    {
        cout<<"Computer & operator=(const Computer &)"<<endl;
        if(this != &rhs)
        {
            delete [] _brand;
            //深拷贝
            _brand=new char[strlen(rhs._brand)+1]();
            strcpy(_brand,rhs._brand);
            _price=rhs._price;
        }
        return *this;
    }

    Computer(const Computer & rhs)
    : _brand(new char[strlen(rhs._brand)+1]())  //深拷贝
    , _price(rhs._price)
    {
        strcpy(_brand,rhs._brand);
        cout<<"Computer(const Computer &)"<<endl;
    }

    void print();

    ~Computer()
    {
        delete [] _brand;
        cout<<"~Computer()"<<endl;
    }

private:
   char * _brand;
    float _price;
};

Computer::Computer(const char *brand,float price)
: _brand(new char[strlen(brand)+1]())
, _price(price)
{
    strcpy(_brand,brand);
    cout<<"Computer(const chat *,float)"<<endl;
}

void Computer::print()
{
    printf(">> _brand: %p\n",_brand);
    cout<<"_brand: "<<_brand<<endl
        <<"_price: "<<_price<<endl;
}

int test()
{
    Computer pc1("Xiao mi",1111);
    cout<<"pc1-->"<<endl;
    pc1.print();

    Computer pc2=pc1;   //调用复制构造函数
    cout<<"pc2-->"<<endl;
    pc2.print();

    Computer pc3("Thinkpad",3333);
    cout<<"pc3-->"<<endl;
    pc3.print();

    pc2=pc3;    //调用赋值运算符函数 pc2=pc2 自复制
    cout<<"pc2-->"<<endl;
    pc2.print();

    return 0;
}

int main()
{
    test();
    cout<<"------------"<<endl;
    return 0;
}

