#include <unordered_map>
#include <set>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

int main()
{
    int i=1;
    unordered_map<string, set<int>> index;
    string str("abcdeafghikk");
    cout<<str<<endl;
    for(auto  c : str){
        stringstream ss; 
        ss << c;
        string s = ss.str();
        index[s].insert(i);
        ++i;
    }
    for(auto & c : index){
        cout<<c.first<<" : ";
        for(auto & ret : c.second){
            cout<<ret<<" ";
        }
        cout<<endl;
    }
    return 0;
}

