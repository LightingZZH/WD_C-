#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

template <typename Type>
class Singleton
{
public:
    template <typename... Args>
    static Type * getInstance(Args... args)
    {
        if(!_pInstance){
            _pInstance = new Type(args...);
            atexit(destroy);
        }
        return _pInstance;
    }

    static void destroy()
    {
        if(_pInstance) delete _pInstance;
    }

private:
    Singleton() {   cout<<"Singleton()"<<endl;    }
    ~Singleton() {   cout<<"~Singleton()"<<endl;  }

    static Type* _pInstance;
};

template <typename Type>
Type* Singleton<Type>::_pInstance = nullptr;

class Point
{
public:
    Point(int x, int y)
    : _x(x)
    , _y(y)
    {   cout<<"Point(int, int)"<<endl;  }

    void print()
    {
        cout<<"("<<_x<<","<<_y<<")"<<endl;
    }

    ~Point()
    {   cout<<"~Point()"<<endl; }

    friend class Singleton<Point>;
private:
    int _x;
    int _y;
};

class Computer
{
public:
    Computer(string brand, int price)
    : _brand(brand)
    , _price(price)
    {   cout<<"Computer(string, int)"<<endl;    }

    void print()
    {
        cout<<"brand : "<<_brand<<"    price : "<<_price<<endl;
    }

    ~Computer()
    {   cout<<"~Computer()"<<endl;  }

    friend class Singleton<Computer>;

private:
    string _brand;
    int _price;
};

int main()
{
    Computer *p1 = Singleton<Computer>::getInstance("Xiaomi",6666);
    Computer *p2 = Singleton<Computer>::getInstance("Xiaomi",6666);
    
    p1->print();
    printf("p1 = %p\n",p1);
    printf("p2 = %p\n",p2);

    Point *p3 = Singleton<Point>::getInstance(1,2);
    Point *p4 = Singleton<Point>::getInstance(1,2);

    p3->print();
    printf("p3 = %p\n",p3);
    printf("p4 = %p\n",p4);

    return 0;
}

