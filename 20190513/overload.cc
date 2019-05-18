#include <iostream>
using std::cout;
using std::endl;

#ifdef __cplusplus
extern "C"
{
#endif
    int add(int x,int y)
    {
        return x+y;
    }
#ifdef __cplusplus
}
#endif

double add(double x,double y) {return x+y;}
double add(int x,double y) {return x+y;}
int add(int x,int y,int z) {return x+y+z;}

int main()
{
    int a=3,b=4,c=5;
    double d1=1.11,d2=2.22;
    cout<<"add(a,b)="<<add(a,b)<<endl;
    cout<<"add(d1,d2)="<<add(d1,d2)<<endl;
    cout<<"add(a,d1)="<<add(a,d1)<<endl;
    cout<<"add(a,b,c)="<<add(a,b,c)<<endl;

    return 0;
}

