#include <iostream>
#include <sstream>
using namespace std;

bool isNum(string str);
int main( )
{

    string s1="2y5r";
    string s2="2";
    string s3="22";
    string s4="a";
    string s5="aa";
    isNum(s1);
    isNum(s2);
    isNum(s3);
    isNum(s4);
    isNum(s5);
    //if(isNum(ss1))
    //{
    //    cout<<"ss1 is a num"<<endl;

    //}
    //else{
    //    cout<<"ss1 is not a num"<<endl;


    //}
    //if(isNum(ss2))
    //{
    //    cout<<"ss2 is a num"<<endl;

    //}
    //else{
    //    cout<<"ss2 is not a num"<<endl;


    //}
    return 0;

}

bool isNum(string str)
{
    stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d)){
        cout<<"!(sin>>d)"<<"|"<<str<<" is not number"<<endl;
        return false;
    }
    if (sin >> c){
        cout<<"(sin>>c)"<<"|"<<str<<" is not number"<<endl;
        return false;
    }
    cout<<str<<" is number"<<endl;
    return true;
}
