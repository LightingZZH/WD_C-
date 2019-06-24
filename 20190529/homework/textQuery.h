#ifndef __TESTQUERY_H__
#define __TESTQUERY_H__
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;
using std::map;
using std::vector;
using std::set;
using std::string;
using std::ifstream;
using std::istringstream;

class TextQuery
{
public:
    void readFile(const string filename);
    void query(const string &word);

private:
    vector<string> _lines;
    map<string, set<int>> _word2Line;
    map<string, int> _dict;
};

#endif
