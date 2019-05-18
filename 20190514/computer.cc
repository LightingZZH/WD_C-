#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Computer
{
public:
    Computer(const char *brand,float price);    //构造函数声明
    void print();
#if 0
    ~Computer(){}
#endif
    void release() {delete [] _brand;}
    ~Computer()
    {
        release();
        cout<<"~Computer()"<<endl;
    }
private:
    char *_brand;
    float _price;
};

Computer::Computer(const char *brand,float price)
: _brand(new char[strlen(brand)+1]())   //初始化
, _price(price)
{
    cout<<"Computer(const char*,float)"<<endl;
    strcpy(_brand,brand);
}

void Computer::print()
{
    cout<<"brand: "<<_brand<<endl
        <<"price: "<<_price<<endl;
}

Computer pc3("Dell",7777);
int test()
{
    cout<<"------------"<<endl;
    Computer pc1("Lenovo",5555);
    pc1.print();
    
    cout<<"sizeof(Computer)="<<sizeof(Computer)<<endl
        <<"sizeof(pc1)="<<sizeof(pc1)<<endl;

    Computer *pc2=new Computer("Thinkpad",6666);
    pc2->print();
    delete pc2; //执行delete表达式时，要调用析构函数
    cout<<"-------------"<<endl;

    pc3.print();
    cout<<"-------------"<<endl;
    static Computer pc4("Xiaomi",8888);
    pc4.print();
    
    return 0;
}

int main()
{
    test();
    cout<<"--------------"<<endl;
    return 0;
}

