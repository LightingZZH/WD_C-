#include "textQuery.h"

void TextQuery::readFile(const string filename)
{
    ifstream is;
    is.open(filename);
    if(!is.good()){
        cout<<"open file error!"<<endl;
        return ;
    }

    string text;
    while(std::getline(is, text)){
        _lines.push_back(text);
        int n = _lines.size() - 1;
        istringstream line(text);
        string word;
        while(line >> word){
            auto ret = _word2Line.find(word);
            if(ret == _word2Line.end()){
                set<int> row = {n};
                _word2Line.insert({word, row});
                _dict.insert({word, 1});
            }else{
                ret->second.insert(n);
                ++_dict[word];
            }
        }
    }   
}

void TextQuery::query(const string & word)
{
    auto ret = _word2Line.find(word);
    if(ret == _word2Line.end()){
        cout<<word<<" occurs 0 times."<<endl;
    }else{
        auto ret1 = _dict.find(word);
        int cnt = ret1->second;
        cout<<word<<" occurs "<<cnt<<" times."<<endl;
        for(auto & c : ret->second){
            cout<<"    (line "<<c<<") "<<_lines[c]<<endl;
        }
    }
}
