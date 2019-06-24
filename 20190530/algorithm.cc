#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

void test()
{
   vector<int> numbers;    //容器中没有元素时，不要使用begin、end添加元素
   // auto it = numbers.begin();
   // *it = 10;
   // for(;it!=numbers.end();++it){
   //     cout<<*it<<" ";
   // }
   // cout<<endl;

    numbers.push_back(1);

    bool flag = true;
    for(auto it = numbers.begin(); it != numbers.end(); ++it){
        cout<<*it<<" ";
        if(flag){
            numbers.push_back(2);
            flag = false;
            it = numbers.begin();   //如果不加会出错
            //当容器完成扩容操作后，原来的迭代器失效
            //此时必须重新获取迭代器
        }
    }
    cout<<endl;
}

void display(int & number)
{
    ++number;
    cout<<number<<" ";
}

void test1()    //for_each & lambda
{
    vector<int> numbers{1, 2, 3, 4, 5};
    for_each(numbers.begin(), numbers.end(), display);
    cout<<endl;

    cout<<"&numbers[0] = "<<&numbers[0]<<endl;

    //lambda表达式 =》匿名函数
    for_each(numbers.begin(), numbers.end(), [](int a){
        cout<<a<<" ";
    });
cout<<endl;

    //[]表示捕获上下文中的对象
    //= 表示以值传递的方式捕获
    //& 表示以引用的方式捕获
    auto f1 = [&](){
        cout<<"lambda expression"<<endl;
        cout<<"numbers[0] = "<<numbers[0]<<endl;
        cout<<"&numbers[0] = "<<&numbers[0]<<endl;
    };
    f1();
}

void test2()    //erase-remove
{
    vector<int> numbers{1,2,3,4,5,6,7,8,9};
    numbers[0] = numbers[3] = numbers[4] = 10;
    copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout," "));
    cout<<endl;

    ostream_iterator<int> osi(cout," ");
    auto it = remove(numbers.begin(), numbers.end(), 10);
    cout<<"*it = "<<*it<<endl;
    copy(numbers.begin(), numbers.end(), osi);
    cout<<endl;

    //numbers.erase(remove(numbers.begin(), numbers.end(), 10), numbers.end());
    //erase-remove惯用法
    numbers.erase(it,numbers.end());
    copy(numbers.begin(), numbers.end(), osi);
    cout<<endl;
}

bool greaterThan(int number)
{
    return number>5;
}

void test3()    //replace_if
{
    vector<int> numbers{1,2,3,4,5,6,7,8,9};
    vector<int> numbers1 = numbers;
    vector<int> numbers2 = numbers;
    std::less<int> lt;  //operator() (const int & lhs, const int & rhs)
    replace_if(numbers.begin(), numbers.end(), bind1st(lt, 5), 10);
    replace_if(numbers1.begin(), numbers1.end(), bind2nd(lt, 5), 10);
    replace_if(numbers2.begin(), numbers2.end(), greaterThan, 10);

    ostream_iterator<int> osi(cout," ");
    copy(numbers.begin(), numbers.end(), osi);
    cout<<endl;
    copy(numbers1.begin(), numbers1.end(), osi);
    cout<<endl;
    copy(numbers2.begin(), numbers2.end(), osi);
    cout<<endl;
}

void test4()    //search
{
    string s1 = "this is a search test";
    string s2("search");

    auto it = search(s1.begin(), s1.end(), s2.begin(), s2.end());
    cout<<*it<<endl;
    for(;it!=s1.end();++it){
        cout<<*it;
    }
    cout<<endl;
}

int main()
{
    //test();
    //cout<<"-----------for_each & lambda--------------"<<endl;
    //test1();
    //cout<<"------------erase & remove----------------"<<endl;
    //test2();
    //cout<<"----------------replace_if------------------"<<endl;
    //test3();
    test4();
    return 0;
}

