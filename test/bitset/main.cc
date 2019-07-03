#include <iostream>
#include <bitset>
using namespace std;

int main()
{
    bitset<8> bst;
    cout<<bst<<endl;
    bst.set(0);
    cout<<bst<<endl;
    if(bst[0]) cout<<"ok"<<endl;
    if(!bst[7]) cout<<"no"<<endl;
    return 0;
}

