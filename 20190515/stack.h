#ifndef __STACK_H__
#define __STACK_H__
#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;

class Stack
{
public:
    Stack()
    : _arr(new int[10]())
    , _flag(0)
    {
        cout<<"Stack()"<<endl;
    }
    void push(int); //入栈
    void pop();     //出栈
    int top();      //读栈顶元素
    bool empty();   //判断栈空
    bool full();    //判断栈满
    ~Stack()
    {
        delete [] _arr;
        cout<<"~Stack()"<<endl;
    }
private:
    int *_arr;
    int _flag;
};


#endif
