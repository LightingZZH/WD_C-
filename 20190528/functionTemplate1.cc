#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

template <typename T>
T add(T x, T y);

//模板也可以重载
template <typename T>
T add(T x, T y, T z)
{
    return x+y+z;
}

#if 1
int add(int x, int y)
{
    cout<<"int add(int ,int)"<<endl;
    return x+y;
}
#endif

//模板特化(Specialization)
//特化版本不唯一
template<>
const char * add<const char *>(const char *p1, const char *p2)
{
    char *ptmp = new char[strlen(p1)+strlen(p2)+1]();
    strcpy(ptmp, p1);
    strcat(ptmp, p2);
    return ptmp;
}

int main()
{
    int x1 = 3, x2 = 4, x9 = 5;
    double x3 = 1.1, x4 = 2.2;
    char x5 = 'a', x6 = 1;
    long x7 = 100, x8 = 101;
    const char *str1 = "hello,";
    const char *str2 = "world";

    cout << "add(x1, x2) = " << add(x1, x2) << endl;//隐式实例化
    cout << "add(x3, x4) = " << add<double>(x3, x4) << endl;//显式实例化
    cout << "add(x5, x6) = " << add(x5, x6) << endl;
    cout << "add(x7, x8) = " << add(x7, x8) << endl;
    cout << "add(x1, x2, x9) = " << add(x2, x2, x9) << endl;
    
    cout<<"add(str1, str2) = "<<add(str1, str2)<<endl;

    return 0;
}

template <typename T>
T add(T x, T y)
{
    cout<<"T add(T, T)"<<endl;
    return x+y;
}
