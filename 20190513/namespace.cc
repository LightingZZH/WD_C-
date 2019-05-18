#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;

int number=1;

namespace tsl
{
    void show();
}

namespace wd
{
    int number=10;
    void display(int number)
    {
        cout<<"wd::display()"<<endl;
        cout<<"nubmer="<<number<<endl;
        cout<<"wd::number="<<wd::number<<endl;
        cout<<"::number="<<::number<<endl;
        ::printf("hello,world\n");
    }
    void show()
    {
        tsl::show();
    }
}

namespace tsl
{
    void display()
    {
        wd::display(100);
    }
    void show()
    {
        cout<<"tsl::show()"<<endl;
    }
}

int main()
{
    /* wd::show(); */
    tsl::display();
    return 0;
}


