#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

class Number
{
public:
    Number(int data = 0)
    : _data(data)
    {}

    void display() const
    {   cout<<_data<<" ";   }

    bool isEven() const
    {
        return !(_data%2);
    }

    bool isPrime() const
    {
        if(_data==1){
            return false;
        }
        for(int i=2; i<=_data/2; ++i){
            if(!(_data%i)) return false;
        }
        return true;
    }

private:
    int _data;
};

int main()
{
    vector<Number> numbers;
    for(int i=1; i!=21; ++i){
        numbers.push_back(Number(i));
    }
    for_each(numbers.begin(), numbers.end(), mem_fn(&Number::display));
    cout<<endl;

    using namespace placeholders;
    //for_each(numbers.begin(), numbers.end(), bind(&Number::display, &numbers));//出错了，Why?
    //cout<<endl;

    for_each(numbers.begin(), numbers.end(), bind(&Number::display, _1));
    cout<<endl;

    numbers.erase(
        remove_if(numbers.begin(), numbers.end(), mem_fn(&Number::isPrime)),
        numbers.end());
    for_each(numbers.begin(), numbers.end(), mem_fn(&Number::display));
    cout<<endl;

    return 0;
}

