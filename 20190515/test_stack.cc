#include "stack.h"

int main()
{
    Stack sk;
    sk.push(10);
    sk.push(12);
    sk.push(14);
    cout<<sk.top()<<endl;
    sk.pop();
    cout<<sk.top()<<endl;

    return 0;
}

