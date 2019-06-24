#include <iostream>
using std::cout;
using std::endl;

template <typename T1, typename T2>
T2 multiply(T1 x, T2 y)
{
    return x*y;
}

template <typename T1, int NUMBER = 10>
T1 multiply(T1 x)
{
    return x*NUMBER;
}

int main()
{
    int x1 = 2;
    double x2 = 2.22;
    cout<<"multiply(x1, x2) = "<<multiply(x1, x2)<<endl;
    cout<<"multiply(x2) = "<<multiply(x2)<<endl;
    cout<<"multiply(x2) = "<<multiply<double, 3>(x2)<<endl;
    return 0;
}

