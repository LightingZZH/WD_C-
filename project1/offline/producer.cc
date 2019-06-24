#include "Configuration.h"
#include "DictProducer.h"
#include "SplitToolCppJieba.h"
#include <iostream>

int main()
{
    Configuration conf("../conf/my.conf");
    map<string, string> myconf = conf.getConfigMap();
    string dictpath = myconf["dict"];
    string indexpath = myconf["index"];

    SplitToolCppJieba cppjieba;
    SplitTool * splitTool = &cppjieba;

    DictProducer dictProducer("../yuliao", splitTool);
    dictProducer.build_dict();
    dictProducer.build_cn_dict();
    dictProducer.store_dict(dictpath.c_str());
    dictProducer.store_index(indexpath.c_str());

    return 0;
}

