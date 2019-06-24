#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::copy;
using std::vector;
using std::istream_iterator;
using std::ostream_iterator;

void test1()
{
    vector<int> numbers{1,2,3,4,5};

    //ostream_iterator内部要重载相应的运算符，模拟出一个迭代器功能来==>适配器模式
    ostream_iterator<int> osi(cout,",");
    copy(numbers.begin(),numbers.end(),osi);
    cout<<endl;
}

void test2()
{
    vector<int> numbers{1,2,3,4,5};
    istream_iterator<int> isi(cin);

    //begin(),end()是用来读取容器元素的
    //不能用来添加元素
    //copy(isi, istream_iterator<int>(),numbers.begin())    //error,会出错
    //具体出错看视频
    
    //std::back_inserter返回的是一个插入迭代器， std::back_insert_iterator
    copy(isi, istream_iterator<int>(), std::back_inserter(numbers));

    copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));
    cout<<endl;
}

int main()
{
    test1();
    cout<<"----------------------"<<endl;
    test2();
    return 0;
}

