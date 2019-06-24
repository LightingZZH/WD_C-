#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;

//atexit + 静态方法

class Singleton
{
public:
    static Singleton * getInstance()
    {
        if(_pInstance==nullptr){
            _pInstance = new Singleton();
            atexit(destroy);
        }
        return _pInstance;
    }

    void print() const {cout<<"print()"<<endl;}

    static void destroy()
    {
        if(_pInstance) delete _pInstance;
    }

private:
    Singleton() {cout<<"Singleton()"<<endl;}
    ~Singleton() {cout<<"~Singleton()"<<endl;}
    
    static Singleton * _pInstance;
};

void getInstance() {cout<<"getInstanc()"<<endl;}

//Singleton * Singleton::_pInstance = nullptr;  //饿汉(Lazy)模式
Singleton * Singleton::_pInstance = getInstance();  //饱汉模式
//初始化，有类作用域，相当于在类内部

int main()
{
    Singleton::getInstance()->print();
    return 0;
}

