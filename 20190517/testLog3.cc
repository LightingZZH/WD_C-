#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <iostream>
using std::cout;
using std::endl;
using namespace log4cpp;

int main()
{
    PatternLayout *patternLayou1=new PatternLayout();
    patternLayou1->setConversionPattern("%d [%p] %m%n");

    PatternLayout *patternLayou2=new PatternLayout();
    patternLayou2->setConversionPattern("%d [%p] %m%n");

    PatternLayout *patternLayou3=new PatternLayout();
    patternLayou3->setConversionPattern("%d [%p] %m%n");

    OstreamAppender *ostreamAppender =
        new OstreamAppender("ostreamAppender",&cout);
    ostreamAppender->setLayout(patternLayou1);

    FileAppender *fileAppender = 
        new FileAppender("fileAppender","file.log");
    fileAppender->setLayout(patternLayou2);

    RollingFileAppender *rollingFileAppender =
        new log4cpp::RollingFileAppender(
            "rollingFileAppender",
            "test.log",
            1024,
            10);
    rollingFileAppender->setLayout(patternLayou3);

    Category & myRecord = Category::getRoot().getInstance("myRecord");
    myRecord.setAppender(ostreamAppender);
    myRecord.addAppender(fileAppender);
    myRecord.addAppender(rollingFileAppender);
    myRecord.setPriority(Priority::ERROR);

    for(int idx=0;idx!=50;++idx)
    {
        myRecord.emerg("this is an emerg message");
        myRecord.fatal("this is a fatal message");
        myRecord.alert("this is an alert message");
        myRecord.crit("this is a crit message");
        myRecord.warn("this is a warn message");
        myRecord.error("this is an error message");
        myRecord.notice("this is a notice message");
        myRecord.info("this is an info message");
        myRecord.debug("this is a debug message");
    }

    Category::shutdown();
    return 0;
}

