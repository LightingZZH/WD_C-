#include <iostream>
#define N 11
using std::cout;
using std::endl;

class Queue
{
public:
    Queue()
    : _arr(new int[N]())
    , _front(0)
    , _rear(0)
    {
        cout<<"Queue"<<endl;
    }
    void push(int); //元素入队
    void pop();     //元素出队
    int front();    //读队列头
    int back();     //读队列尾
    bool empty();   //判断队列是否为空
    bool full();    //判断队列是否为满
    ~Queue()
    {
        delete [] _arr;
        cout<<"~Queue"<<endl;
    }
private:
    int* _arr;
    int _front;
    int _rear;
};
