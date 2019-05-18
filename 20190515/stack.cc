#include "stack.h"

void Stack::push(int val)
{
    if(_flag==10){
        cout<<"栈满,无法入栈"<<endl;
    }else{
        _arr[_flag]=val;
        ++_flag;
    }
}

void Stack::pop()
{
    if(!_flag){
        cout<<"栈空，无法出栈"<<endl;
    }else{
        --_flag;
    }
}

int Stack::top()
{
    if(!_flag){
        cout<<"栈空，无法读出"<<endl;
        return 0;
    }else{
        return _arr[_flag-1];
    }
}

bool Stack::empty()
{
    if(!_flag) return true;
    else return false;
}

bool Stack::full()
{
    if(_flag==10) return true;
    else return false;
}
