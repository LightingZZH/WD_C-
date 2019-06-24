#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;


string make_plural(int x, string s1, string s2)
{
    return x > 1 ? s1+s2 : s1;
}


class QueryResult;
class TextQuery{
public:
    using line_no = vector<string>::size_type;
    TextQuery(ifstream &);
    QueryResult query(const string &) const;
private:
    shared_ptr<vector<string>> file;    //其中一个元素为一行string,用来存放文本
    map<string, shared_ptr<set<line_no>>> wm;   //用来存放单词及所在行行号的集合
};

class QueryResult{
friend ostream& print(ostream &, const QueryResult &);
public:
    using line_no = TextQuery::line_no;
    QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f)
    : sought(s)
    , lines(p)
    , file(f)
    {}
    
    set<line_no>::iterator begin()
    {   return lines->begin();  }

    set<line_no>::iterator end()
    {   return lines->end();  }
    
    shared_ptr<vector<string>> get_file()
    {   return file;    }

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
        for(auto & c : text){
            if(ispunct(c) || isdigit(c)) c = ' ';
        }
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


class Query_base    //抽象基类
{
public:
    friend class Query;
protected:
    using line_no = TextQuery::line_no; //用于eval函数
private:
    virtual QueryResult eval(const TextQuery &) const = 0;
    virtual string rep() const = 0;
};

class Query     //管理Query_base继承体系的接口类
{
    friend Query operator~(const Query &);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);

public:
    Query(const string &);  //接受一个string参数，创建一个wordQuery对象
    QueryResult eval(const TextQuery &t) const
    {   return q->eval(t);  }
    string rep() const
    {   return q->rep();    }

private:
    Query(shared_ptr<Query_base> query)
    : q(query)
    {}

    shared_ptr<Query_base> q;
};

ostream & operator<<(ostream &os, const Query &query)
{
    //Query::rep通过它的Query_base指针对rep()进行虚调用
    return os<<query.rep();
}

class WordQuery
: public Query_base
{
    friend class Query;
    WordQuery(const string &s)
    : query_word(s)
    {}

    QueryResult eval(const TextQuery &t) const
    {   return t.query(query_word); }

    string rep() const
    {   return query_word;  }

    string query_word;  //要查找的单词
};

inline Query::Query(const string &s)
: q(new WordQuery(s))
{}

class NotQuery
: public Query_base
{
    friend Query operator~(const Query &);
    NotQuery(const Query &q)
    : query(q)
    {}

    QueryResult eval(const TextQuery &t) const;

    string rep() const
    {   return "~("+query.rep()+")";    }

    Query query;
};

inline Query operator~(const Query &operand)
{
    return shared_ptr<Query_base>(new NotQuery(operand));
}

class BinaryQuery   //抽象基类
: public Query_base
{
protected:
    BinaryQuery(const Query &l, const Query &r, string s)
    : lhs(l)
    , rhs(r)
    , opSym(s)
    {}

    string rep() const
    {   return "("+lhs.rep()+" "+opSym+" "+rhs.rep()+")";   }

    Query lhs, rhs;
    string opSym;   //运算符的名字
};

class AndQuery
: public BinaryQuery
{
    friend Query operator&(const Query &, const Query &);
    AndQuery(const Query &left, const Query &right)
    : BinaryQuery(left, right, "&")
    {}

    QueryResult eval(const TextQuery &) const;
};

inline Query operator&(const Query &lhs, const Query &rhs)
{
    return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery
: public BinaryQuery
{
    friend Query operator|(const Query & , const Query &);
    OrQuery(const Query &left, const Query &right)
    : BinaryQuery(left, right, "|")
    {}

    QueryResult eval(const TextQuery &) const;
};

inline Query operator|(const Query &lhs, const Query &rhs)
{
    return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResult OrQuery::eval(const TextQuery &text) const
{
    auto right = rhs.eval(text), left = lhs.eval(text);
    auto ret_lines = make_shared<set<line_no>>(left.begin(), left.end());
    ret_lines->insert(right.begin(), right.end());

    return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult AndQuery::eval(const TextQuery &text) const
{
    auto left = lhs.eval(text), right = rhs.eval(text);
    auto ret_lines = make_shared<set<line_no>>();

    set_intersection(left.begin(), left.end(), 
                     right.begin(), right.end(), 
                     inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult NotQuery::eval(const TextQuery &text) const
{
    auto result = query.eval(text);
    auto ret_lines = make_shared<set<line_no>>();
    auto beg = result.begin(), end = result.end();
    auto sz = result.get_file()->size();
    for(size_t n = 0; n != sz; ++n){
        if(beg == end || *beg != n)
            ret_lines->insert(n);
        else if(beg != end)
            ++beg;
    }
    return QueryResult(rep(), ret_lines, result.get_file());
}

ostream & print(ostream & os, const QueryResult & qr)
{
    os << "Executing Query for: "<< qr.sought << endl;
    os << qr.sought << " occurs "<< qr.lines->size() <<" "
       << make_plural(qr.lines->size(),"time","s") << endl;

    for(auto num : *qr.lines){
        os << "(line "<< num+1 <<") "<< *(qr.file->begin()+num) <<endl;
    }
    return os;
}

//void runQueries(ifstream & infile)
//{
//    TextQuery tq(infile);
//    
//    while(1){
//        cout<<"enter word to look for, or q to quit: "<<endl;
//        string s;
//        if(!(cin>>s) || s=="q") break;
//        print(cout, tq.query(s)) << endl;
//    }
//}

int main()
{
    ifstream ifs;
    ifs.open("test.txt");

    TextQuery tq(ifs);

    Query wdq = Query("Daddy");
    Query notq = ~Query("Alice");
    Query orq = Query("hair") | Query("Alice");
    Query andq = Query("hair") & Query("Alice");

    print(cout, wdq.eval(tq));
    cout<<"-----------"<<endl;
    print(cout, notq.eval(tq));
    cout<<"-----------"<<endl;
    print(cout, orq.eval(tq));
    cout<<"-----------"<<endl;
    print(cout, andq.eval(tq));
    cout<<"-----------"<<endl;
    return 0;
}

