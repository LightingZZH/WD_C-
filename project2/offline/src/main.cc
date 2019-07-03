#include "../include/Configuration.h"
#include "../include/DirScanner.h"
#include "../include/SplitToolCppJieba.h"
#include "../include/PageLib.h"
#include "../include/PageLibProcessor.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
using namespace std;

int main()
{
    Configuration conf("../conf/myconf.conf");
    conf.print();

    DirScanner dirScanner(conf);
    dirScanner();
    dirScanner.print();

    SplitToolCppJieba jieba;

    PageLib pageLib(conf, dirScanner);
    time_t t1 = time(NULL);
    pageLib.create();
    pageLib.store();
    time_t t2 = time(NULL);
    printf("raw lib create and store time: %ld s\n", t2-t1);

    PageLibProcessor pageLibProcessor(conf, jieba);
    pageLibProcessor.doProcess();

    return 0;
}

