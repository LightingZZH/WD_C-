#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <iostream>
using std::cout;
using std::endl;
using namespace log4cpp;

int main()
{
    PatternLayout *patternLayout = new PatternLayout();
    patternLayout->setConversionPattern("%d [%p] %m%n");
    //%d date/%p priority/%m message/%n 换行
    
    OstreamAppender *ostreamAppender = 
        new OstreamAppender("ostreamAppender",&cout);
    ostreamAppender->setLayout(patternLayout);

    Category & myRecord=Category::getRoot().getInstance("myRecord");
    myRecord.setAppender(ostreamAppender);
    myRecord.setPriority(Priority::ERROR);

    myRecord.emerg("this is an emerg message");
    myRecord.fatal("this is a fatal message");
    myRecord.alert("this is an alert message");
    myRecord.crit("this is a crit message");
    myRecord.warn("this is a warn message");
    myRecord.error("this is an error message");
    myRecord.notice("this is a notice message");
    myRecord.info("this is an info message");
    myRecord.debug("this is a debug message");

    Category::shutdown();
    return 0;
}

