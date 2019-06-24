#include <iostream>
#include <limits>
using std::cout;
using std::endl;

class Complex
{
public:
    Complex(double real=0,double image=0)
    : _real(real)
    , _image(image)
    {
        cout<<"Complex(double,double)"<<endl;
    }

    void print()
    {
        cout<<_real<<"+"<<_image<<"i"<<endl;
    }

    //前置形式/返回值必须使用引用/效率更高
    Complex & operator++()
    {
        ++_real;
        ++_image;
        return *this;
    }

    //后置形式/返回值是对象/int只是用作标记
    Complex operator++(int)
    {
        Complex tmp(*this);
        ++_real;
        ++_image;
        return tmp;
    }

    Complex & operator+=(const Complex & rhs)
    {
        _real += rhs._real;
        _image += rhs._image;
        return *this;
    }

    friend Complex operator+(const Complex & lhs,const Complex & rhs);
    friend bool operator==(const Complex & lhs,const Complex & rhs);
    friend std::ostream & operator<<(std::ostream & os,const Complex & rhs);
    friend std::istream & operator>>(std::istream & is,Complex & rhs);

private:
    double _real;
    double _image;
};


Complex operator+(const Complex & lhs,const Complex & rhs)
{
    cout<<"friend Complex operator+()"<<endl;

    //return Complex(lhs._real+rhs._real,lhs._image+rhs._image);

    Complex tmp(lhs);
    tmp += rhs; //充分利用已实现的函数
    return tmp;
}

bool operator==(const Complex & lhs,const Complex & rhs)
{
    return (lhs._real==rhs._real && lhs._image==rhs._image);
}

//所有流对象都不能进行复制，表达的是对象语义
std::ostream & operator<<(std::ostream & os,const Complex & rhs)
{
    os<<rhs._real<<"+"<<rhs._image<<"i"<<endl;
    return os;
}

void readDouble(std::istream & is,double & val)
{
    cout<<"pls input a valid double number:"<<endl;
    while(is>>val,!is.eof())
    {
        if(is.bad()){
            cout<<"istream is corrupted!"<<endl;
            return ;
        }else if(is.fail()){
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            cout<<"pls input a valid double number:"<<endl;
            continue;
        }
        break;
    }
}

std::istream & operator>>(std::istream & is,Complex & rhs)
{
    readDouble(is,rhs._real);
    readDouble(is,rhs._image);
    return is;
}

void test1()
{
    Complex c1(1,2);
    Complex c2(3,4);
    Complex c3=c1+c2;
    cout<<"c3="<<c3<<endl;
    //operator<<(operator<<(cout,"c3="),c3);
    
    c1 += c2;
    cout<<"c1="<<c1<<endl;
    
    cout<<"(++c1)="<<(++c1)<<endl;
    cout<<"c1="<<c1<<endl;
    cout<<"(c1++)="<<(c1++)<<endl;
    cout<<"c1="<<c1<<endl;
}

void test2()
{
    cout<<"pls input a inerger number:"<<endl;
    int a;
    std::cin>>a;

    Complex c;
    std::cin >> c;
    cout<<"c="<<c<<endl;
}

void test()
{
    int a=1;
    cout<<"(++a)="<<(++a)<<endl;
    //&(++a);   //ok
    cout<<"a="<<a<<endl;
    cout<<"(a++)="<<(a++)<<endl;
    //&(a++); //error a++ 为右操作数，不能取地址
    cout<<"a="<<a<<endl;
}

int main()
{
    //test1();
    test2();
    return 0;
}

