#include <log4cpp/Category.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <iostream>
using std::cout;
using std::endl;
using namespace log4cpp;
int main()
{
    Category & root=Category::getRoot();    //根分类root
    OstreamAppender * pOstreamAppender=new OstreamAppender("OstreamAppender",&cout);
    pOstreamAppender->setLayout(new BasicLayout()); //BasicLayout为一种日志输出格式

    root.setAppender(pOstreamAppender); //设置日志记录器输出到终端
    root.setPriority(Priority::DEBUG);  //设置日志记录器的优先级为DEBUG
    //DEBUG,INFO,WARN,ERROR,FATAL 优先级低到高

    root.debug("this is a debug message");  //一条debug类型的记录

    Category::shutdown();
    return 0;
}

