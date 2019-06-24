#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#define N 10

template <typename Type, int kSize = N>
class Que
{
public:
    Que()
    : _rear(0)
    , _front(0)
    , _pQue(new Type[kSize]())
    {
        cout<<"Que()"<<endl;
    }

    ~Que()
    {
        if(_pQue){
            delete [] _pQue;
            cout<<"~Que()"<<endl;
        }
    }

    bool empty() const;
    bool full() const;
    void push(const Type &);
    void pop();
    Type front();
    Type back();

private:
    int _rear;
    int _front;
    Type *_pQue;
};

template <typename Type, int kSize>
bool Que<Type, kSize>::empty() const
{
    return _rear==_front;
}

template <typename Type, int kSize>
bool Que<Type, kSize>::full() const
{
    return (_rear+1)%N == _front;
}

template <typename Type, int kSize>
void Que<Type, kSize>::push(const Type &t)
{
    if(!full()){
        _pQue[_rear] = t;
        _rear = (_rear+1)%N;
    }else{
        cout<<"Que is full, can't push data anymore!"<<endl;
    }
}

template <typename Type, int kSize>
void Que<Type, kSize>::pop()
{
    if(!empty()){
        _front = (_front+1)%N;
    }else{
        cout<<"Que is empty, can't pop!"<<endl;
    }
}

template <typename Type, int kSize>
Type Que<Type, kSize>::front()
{
    return _pQue[_front];
}

template <typename Type, int kSize>
Type Que<Type, kSize>::back()
{
    return _pQue[(_rear+N-1)%N];
}

void test1()
{
    Que<int> que;
    cout<<"此时队列是否为空？"<<que.empty()<<endl;
    que.push(1);
    cout<<"此时队列是否为空？"<<que.empty()<<endl;

    for(int i=2; i!=10; ++i){
        que.push(i);
    }
    cout << "此时队列是否已满? " << que.full() << endl;

    cout<<"front = "<<que.front()<<endl;
    cout<<"rear = "<<que.back()<<endl;

    while(!que.empty())
    {
        cout<<que.front()<<" ";
        que.pop();
    }
    cout<<endl;

    cout<<"此时队列是否为空？"<<que.empty()<<endl;
}

void test2()
{
    Que<string> que;
    cout<<"此时队列是否为空？"<<que.empty()<<endl;
    que.push("aaa");
    cout<<"此时队列是否为空？"<<que.empty()<<endl;

    for(int i=1; i!=10; ++i){
        que.push(string(3,'a'+i));
    }
    cout << "此时队列是否已满? " << que.full() << endl;

    cout<<"front = "<<que.front()<<endl;
    cout<<"rear = "<<que.back()<<endl;

    while(!que.empty())
    {
        cout<<que.front()<<" ";
        que.pop();
    }
    cout<<endl;

    cout<<"此时队列是否为空？"<<que.empty()<<endl;
}

int main()
{
    test1();
    cout<<"----------------"<<endl;
    test2();
    return 0;
}

