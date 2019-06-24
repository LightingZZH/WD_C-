#include <iostream>
using std::cout;
using std::endl;

template <typename T, typename Compare = std::less<T> >
class HeapSort
{
public:
    HeapSort(T *arr, int size)
    : _arr(arr)
    , _size(size)
    {}

    void heapAdjust(int);
    void sort();
private:
    T * _arr;
    int _size;
    Compare _compare;
};

template <typename T, typename Compare>
void HeapSort<T, Compare>::heapAdjust(int adjustPoint)
{
    int child = 2 * adjustPoint + 1;
    while(child < _size){
        int max = child;
        if(child+1<_size && _compare(_arr[child],_arr[child+1]))
            max = child + 1;
        if(_compare(_arr[adjustPoint],_arr[max])){
            T tmp = _arr[adjustPoint];
            _arr[adjustPoint] = _arr[max];
            _arr[max] = tmp;
            adjustPoint = max;
            child = 2 * max + 1;
        }
        else break;
    }
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::sort()
{
    for(int adjustPoint = _size/2 - 1; adjustPoint >= 0; --adjustPoint)
        heapAdjust(adjustPoint);
    for(int n = _size-1; n > 0; --n){
        T tmp = _arr[0];
        _arr[0] = _arr[n];
        _arr[n] = tmp;
        --_size;
        heapAdjust(0);
    }
}

void test1()
{
    int arr[10] = {3,1,6,7,4,2,0,8,9,5};
    HeapSort<int> sort1(arr, 10);
    sort1.sort();
    for(int i=0;i!=10;++i){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

void test2()
{
    char c[10] = {'a','c','h','e','d','g','j','i','f','b'};
    HeapSort<char> sort2(c,10);
    sort2.sort();
    for(int i=0;i!=10;++i){
        cout<<c[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    test1();
    cout<<"-----------"<<endl;
    test2();

    return 0;
}
