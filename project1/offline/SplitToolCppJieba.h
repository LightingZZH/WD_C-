#ifndef __SPLITTOOLCPPJIEBA_H__
#define __SPLITTOOLCPPJIEBA_H__

#include "../cppjieba/include/cppjieba/Jieba.hpp"
#include "Configuration.h"
#include "SplitTool.h"

const char * const DICT_PATH = "/home/zzh/C++/project1/cppjieba/dict/jieba.dict.utf8";
const char * const HMM_PATH = "/home/zzh/C++/project1/cppjieba/dict/hmm_model.utf8";
const char * const USER_DICT_PATH = "/home/zzh/C++/project1/cppjieba/dict/user.dict.utf8";
const char * const IDF_PATH = "/home/zzh/C++/project1/cppjieba/dict/idf.utf8";
const char * const STOP_WORD_PATH = "/home/zzh/C++/project1/cppjieba/dict/stop_words.utf8";

class SplitToolCppJieba
: public SplitTool
{
public:
    SplitToolCppJieba()
    : _jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH)
    {}

    vector<string> cut(const string & sentence)
    {
        vector<string> words;
        _jieba.Cut(sentence, words, true);
        return words;
    }

    ~SplitToolCppJieba() {}

private:
    cppjieba::Jieba _jieba;
};

#endif
