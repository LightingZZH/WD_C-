#include "MyLog.h"

Mylog * Mylog::_pMylog=nullptr;

Mylog::Mylog()
: _myRecord(Category::getRoot().getInstance("_myRecord")) 
{
    PatternLayout *pL = new PatternLayout();
    pL->setConversionPattern("%d [%c] [%p] %m%n");

    OstreamAppender *OsApp = new OstreamAppender("OsApp",&cout);
    OsApp->setLayout(pL);

    _myRecord.setAppender(OsApp);
    _myRecord.setPriority(Priority::DEBUG);
    cout<<"Mylog()"<<endl;
}

Mylog::~Mylog()
{
    Category::shutdown();
    cout<<"~Mylog()"<<endl;
}

void Mylog::warn(const char *msg)
{
    _myRecord.warn(msg);
}

void Mylog::error(const char *msg)
{
    _myRecord.error(msg);
}

void Mylog::debug(const char *msg)
{
    _myRecord.debug(msg);
}

void Mylog::info(const char *msg)
{
    _myRecord.info(msg);
}
