#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

unordered_map<string, string> cache;

void readFile(const string & filename)
{
    ifstream ifs(filename);
    if(!ifs){
        cout<<"open file "<<filename<<" error!"<<endl;
        return ;
    }
    string line;
    while(std::getline(ifs, line)){
        istringstream iss(line);
        string query, ret1, ret2, ret3;
        while(!iss.eof()){
            iss >> query >> ret1 >> ret2 >> ret3;
            string ret = ret1+" "+ret2+" "+ret3;
            cache.insert({query,ret});
        }
    }
}

void writeFile(const string & filename)
{
    ofstream ofs(filename);
    if(!ofs){
        cout<<"open file "<<filename<<"error!"<<endl;
        return ;
    }
    ofs << "query1" << " "<< "apple pen push"<<"\n";
    ofs << "query2" << " "<< "bush is kool"<<"\n";
    ofs.close();
}

int main()
{
    readFile("test.txt");
    writeFile("test.txt");
    readFile("test.txt");
    for(auto & c : cache){
        cout<<c.first<<" "<<c.second<<endl;
    }
    return 0;
}

