#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ostringstream;
using std::stringstream;
using std::pair;

bool isNum(string str)
{
    stringstream sin(str);
    double d;
    char c;
    if(!(sin>>d)) return false;
    if(sin>>c) return false;
    return true;
}

bool cmp(const pair<string,int>& a,const pair<string,int>& b)
{
    return a.second<b.second;
}

string int2str(int number)
{
    ostringstream oss;
    oss<<number;
    return oss.str();
}

class Dictionary
{
public:
    void read(const string & filename);
    void store(const string & filename);
private:
    map<string,int> _map;
};


void Dictionary::read(const string & filename)
{
    ifstream ifs;
    ifs.open(filename);
    if(!ifs.good()){
        cout<<"ifstream open file error!"<<endl;
    }
    string word;
    while(ifs>>word)
    {
        if(!isNum(word)){
            auto ret=_map.insert({word,1});     //ret 是 pair<iterator,bool>
            if(!ret.second) ++ret.first->second;    //ret.first是map迭代器
        }
    }
    ifs.close();
}

void Dictionary::store(const string & filename)
{
    vector<pair<string,int>>  vec(_map.begin(),_map.end());
    sort(vec.begin(),vec.end(),cmp);
    
    ofstream ofs(filename);
    if(!ofs){
        cout<<"ofstream open file error"<<endl;
        return ;
    }

    for(auto & ret : vec){
        ofs<<ret.first<<" "<<int2str(ret.second)<<"\n";
    }
    ofs.close();
}

int main()
{
    string filename="/home/zzh/C++/20190516/The_Holy_Bible.txt";
    Dictionary dic;
    dic.read(filename);
    dic.store("word_count.txt");
    return 0;
}

