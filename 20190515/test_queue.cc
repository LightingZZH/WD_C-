#include "queue.h"

int main()
{
    Queue que;
    que.push(1);
    que.push(2);
    que.push(3);
    cout<<"队头元素："<<que.front()<<endl;
    cout<<"队尾元素："<<que.back()<<endl;
    que.pop();
    cout<<"队头元素："<<que.front()<<endl;
    que.pop();
    que.pop();
    if(que.empty()){
        cout<<"队列为空"<<endl;
    }
    return 0;
}

