#include <iostream>
using std::cout;
using std::endl;

class Singleton
{
public:
    static Singleton * getInstance()
    {
        if(_pInstance==NULL){
            _pInstance=new Singleton();
        }
        return _pInstance;
    }

    static void destroy()
    {
        if(_pInstance){
            delete _pInstance;
        }
    }

    void print() const
    {
        cout<<"Singleton::print()"<<endl;
    }
private:
    static Singleton *_pInstance;

    Singleton()
    {
        cout<<"Singleton()"<<endl;
    }
    ~Singleton()
    {
        cout<<"~Singleton()"<<endl;
    }
};

Singleton * Singleton::_pInstance=NULL;

int main()
{
    Singleton *p1=Singleton::getInstance();
    Singleton *p2=Singleton::getInstance();

    cout<<"p1="<<p1<<endl;
    cout<<"p2="<<p2<<endl;

    Singleton::getInstance()->print();
    p1->print();
    p2->print();

    Singleton::destroy();
    return 0;
}

