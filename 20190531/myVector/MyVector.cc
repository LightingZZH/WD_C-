#include <iostream>
#include <memory>
using namespace std;

template <typename T>
class Vector
{
public:
    Vector()
    : _start(nullptr)
    , _finish(nullptr)
    , _end_of_storage(nullptr)
    {}

    //~Vector();

    void push_back(const T &);
    void pop_back();

    int size() const
    {   return _finish - _start;  }

    int capacity() const
    {   return _end_of_storage - _start;  }
    
public:
    typedef T* iterator;
    typedef const T* const_iterator;

    const_iterator begin() const
    {   return _start;  }

    const_iterator end() const
    {   return _finish;}

private:
    void reallocate();
private:
    static allocator<T> _alloc;

    T *_start;
    T *_finish;
    T *_end_of_storage;
};

template <typename T>
allocator<T> Vector<T>::_alloc;

template <typename T>
void Vector<T>::push_back(const T &t)
{
    if(size() == capacity()) reallocate();
    _alloc.construct(_finish++, t); //对象构造
}

template <typename T>
void Vector<T>::pop_back()
{
    if(size() > 0){
        _alloc.destroy(--_finish);
    }else{
        cout<<"vector is empty, can't pop"<<endl;
    }
}

template <typename T>
void Vector<T>::reallocate()
{
    int oldSpace = capacity();
    int newSpace = oldSpace > 0 ? 2 * oldSpace : 1;
    
    T *ptmp = _alloc.allocate(newSpace);

    if(_start){
        uninitialized_copy(_start, _finish, ptmp);
        while(_finish != _start){
            _alloc.destroy(--_finish);
        }
    }
    _start = ptmp;
    _finish = ptmp + oldSpace;
    _end_of_storage = ptmp + newSpace;
}

template <typename Container>
void display(const Container & c)
{
    typename Container::const_iterator it = c.begin();
    while(it != c.end()){
        cout<<*it<<" ";
        ++it;
    }
    cout<<endl;
    cout<<"vector's size = "<<c.size()<<endl;
    cout<<"vector's capacity = "<<c.capacity()<<endl;
}

int main()
{
    Vector<int> v;
    display(v);

    for(int i=0; i!=10; ++i){
        v.push_back(i);
        display(v);
    }
    cout<<"---------------"<<endl;
    for(int i=0; i!=11; ++i){
        v.pop_back();
    }
    display(v);
    return 0;
}

