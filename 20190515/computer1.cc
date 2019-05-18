#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Computer
{
public:
    Computer(const char *brand,float price);

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

    static void printTotalPrice();  //静态成员函数，没有隐含的this指针

    ~Computer()
    {
        delete [] _brand;
        cout<<"~Computer()"<<endl;
    }

private:
    char * _brand;
    float _price;
    static double _totalPrice;
};

//静态成员在类外初始化
double Computer::_totalPrice=0;

Computer::Computer(const char *brand,float price)
: _brand(new char[strlen(brand)+1]())
, _price(price)
{
    strcpy(_brand,brand);
    _totalPrice += _price;
    cout<<"Computer(const chat *,float)"<<endl;
}

void Computer::print()
{
    printf(">> _brand: %p\n",_brand);
    cout<<"_brand: "<<_brand<<endl
        <<"_price: "<<_price<<endl;
}

void Computer::printTotalPrice()
{
    //静态成员函数只能访问静态成员
    cout<<">>totalPrice: "<<_totalPrice<<endl;
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

    Computer::printTotalPrice();

    return 0;
}

int main()
{
    test();
    cout<<"------------"<<endl;
    return 0;
}

