#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
using namespace std;

void test1()
{
    vector<int> numbers1{1,2,3,4,5};
    list<int> numbers2{11,12,13};
    copy(numbers1.begin(),numbers1.end(),
         back_insert_iterator<list<int>>(numbers2));
    cout<<endl;

    copy(numbers1.begin(), numbers1.end(), 
         front_insert_iterator<list<int>>(numbers2));
    cout<<endl;

    copy(numbers2.begin(), numbers2.end(), ostream_iterator<int>(cout, " "));


    deque<int> numbers3{22,23,24,25};
    auto it = numbers3.begin();
    ++it;

    copy(numbers1.begin(), numbers1.end(),
         insert_iterator<deque<int>>(numbers3, it));
    cout<<endl;
    copy(numbers3.begin(), numbers3.end(), ostream_iterator<int>(cout, " "));
    cout<<endl;
}

int main()
{
    test1();
    return 0;
}

