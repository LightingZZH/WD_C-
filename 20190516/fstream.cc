#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::string;
using std::vector;

vector<string> v;

void test()
{
    string filepath="/home/zzh/C++/20190516/file";
    ifstream ifs;
    ifs.open(filepath);
    if(!ifs.good()){
        cout<<">> ifstream open file error!"<<endl;
        return ;
    }

    string word;
    while(ifs >> word)
    {
        cout<<word<<endl;
        v.push_back(word);
    }

    ifs.close();
}

void test1()
{
    ofstream ofs("test.txt");
    if(!ofs){
        cout<<"ofstream open file error!"<<endl;
        return ;
    }
    for(auto & word : v){
        ofs<<word<<"\n";
    }
    ofs.close();
}

int main()
{
    test();
    test1();
    return 0;
}

