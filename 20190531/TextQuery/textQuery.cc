#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

using line_no = vector<string>::size_type;

string make_plural(int x, string s1, string s2)
{
    return x > 1 ? s1+s2 : s1;
}


class QueryResult;
class TextQuery{
public:
    TextQuery(ifstream &);
    QueryResult query(const string &) const;
private:
    shared_ptr<vector<string>> file;    //其中一个元素为一行string,用来存放文本
    map<string, shared_ptr<set<line_no>>> wm;   //用来存放单词及所在行行号的集合
};

class QueryResult{
friend ostream& print(ostream &, const QueryResult &);
public:
    QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f)
    : sought(s)
    , lines(p)
    , file(f)
    {}

private:
    string sought;                      //要查询的单词
    shared_ptr<set<line_no>> lines;     //查询单词出现的行号集合
    shared_ptr<vector<string>> file;    //存储一行string的vector
};

TextQuery::TextQuery(ifstream & is)     //将文本中的信息通过该类存储起来
: file(new vector<string>)
{
    string text;
    while(getline(is, text)){
        file->push_back(text);      //向vector中添加一行字符串
        int n = file->size() - 1;   //计算当前行号
        istringstream line(text);
        string word;
        while(line >> word){
            auto &lines = wm[word]; //lines 是一个指向set<line_no>的shared_ptr
            if(!lines){
                lines.reset(new set<line_no>);  //调用reset来更新lines引用的shared_ptr， 使其指向新分配的set
            }
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const string & sought) const
{
    //定义了一个静态局部对象nodata， 它指向一个空的set
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto ret = wm.find(sought);
    if(ret == wm.end()) return QueryResult(sought, nodata, file);
    else return QueryResult(sought, ret->second, file);
}

ostream & print(ostream & os, const QueryResult & qr)
{
    os << qr.sought << " occurs "<< qr.lines->size() <<" "
       << make_plural(qr.lines->size(),"time","s") << endl;

    for(auto num : *qr.lines){
        os << "\t(line "<< num+1 <<") "<< *(qr.file->begin()+num) <<endl;
    }
    return os;
}

void runQueries(ifstream & infile)
{
    TextQuery tq(infile);
    
    while(1){
        cout<<"enter word to look for, or q to quit: ";
        string s;
        if(!(cin>>s) || s=="q") break;
        print(cout, tq.query(s)) << endl;
    }
}

int main()
{
    ifstream ifs;
    ifs.open("test.txt");
    runQueries(ifs);

    return 0;
}

