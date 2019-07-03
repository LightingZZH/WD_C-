#include "../include/WordQuerySever.h"

int main()
{
    Configuration conf("../conf/myconf.conf");
    string ip = conf.getConfigMap()["ip"];
    string s_port = conf.getConfigMap()["port"];
    unsigned short port;
    stringstream ss;
    ss << s_port;
    ss >> port;

    SplitToolCppJieba jieba;    
    WordQuerySever sever(conf, ip, port, jieba);
    cout<<"-------------WordQuerySever started----------------------"<<endl;
    sever.start();

    return 0;
}

