#include "queue.h"

void Queue::push(int val)
{
    if((_rear+1)%N==_front){
        cout<<"队列已满，无法入队"<<endl;
    }else{
        _arr[_rear]=val;
        _rear=(_rear+1)%N;
    }
}

void Queue::pop()
{
    if(_rear==_front){
        cout<<"队列为空，无法出队"<<endl;
    }else{
        _front=(_front+1)%N;
    }
}

int Queue::front()
{
    if(_rear==_front){
        cout<<"队列为空，无法读取队头元素"<<endl;
        return 0;
    }else{
        return _arr[_front];
    }
}

int Queue::back()
{
    if(_rear==_front){
        cout<<"队列为空，无法读取队尾元素"<<endl;
        return 0;
    }else{
        return _arr[(_rear+N-1)%N];
    }
}

bool Queue::empty()
{
    if(_rear==_front) return true;
    else return false;
}

bool Queue::full()
{
    if((_rear+1)%N==_front) return true;
    else return false;
}
