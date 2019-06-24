#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<int> numbers{1,2,3,4,5};
    vector<int>::const_reverse_iterator rit;
    for(rit = numbers.rbegin(); rit!=numbers.rend(); ++rit){
        cout<<*rit<<" ";
    }
    cout<<endl;

    //通过rbegin()/rend()得到的就是reverse_iterator
    for(auto it = numbers.rbegin(); it!=numbers.rend(); ++it){
        cout<<*it<<" ";
    }
    cout<<endl;


    //vector<int>::iterator it;
    //for(it=numbers.begin(); it!=numbers.end(); ++it){
    //    cout<<*it<<" ";
    //}
    //cout<<endl;

    //for(it = numbers.begin(); it!=numbers.end(); ++it){
    //    cout<<*it<<" ";
    //}
    //cout<<endl;

    return 0;
}

