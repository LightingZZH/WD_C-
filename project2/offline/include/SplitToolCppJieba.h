//jieba分词类
#ifndef __SPLITTOOLCPPJIEBA_H__
#define __SPLITTOOLCPPJIEBA_H__

#include "cppjieba/include/cppjieba/Jieba.hpp"
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

const char * const DICT_PATH = "/home/zzh/C++/project2/offline/include/cppjieba/dict/jieba.dict.utf8";
const char * const HMM_PATH = "/home/zzh/C++/project2/offline/include/cppjieba/dict/hmm_model.utf8";
const char * const USER_DICT_PATH = "/home/zzh/C++/project2/offline/include/cppjieba/dict/user.dict.utf8";
const char * const IDF_PATH = "/home/zzh/C++/project2/offline/include/cppjieba/dict/idf.utf8";
const char * const STOP_WORD_PATH = "/home/zzh/C++/project2/offline/stop_words.txt";

class SplitToolCppJieba
{
public:
    SplitToolCppJieba()
    : _jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH)
    {}

    vector<string> cut(const string & sentence)
    {
        vector<string> words;
        _jieba.CutAll(sentence, words);
        return words;
    }

private:
    cppjieba::Jieba _jieba;
};

#endif
