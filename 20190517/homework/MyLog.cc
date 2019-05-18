#include "MyLog.h"

Mylog * Mylog::_pMylog=nullptr;

Mylog::Mylog()
: _pL1(new PatternLayout())
, _pL2(new PatternLayout()) 
, _OsApp(new OstreamAppender("_OsApp",&cout))
, _fApp(new FileAppender("_fApp","file.log"))
, _myRecord(Category::getRoot().getInstance("_myRecord")) 
{
    _pL1->setConversionPattern("%d [%p] %m%n");
    _pL2->setConversionPattern("%d [%p] %m%n");
    _OsApp->setLayout(_pL1);
    _fApp->setLayout(_pL2);
    _myRecord.setAppender(_OsApp);
    _myRecord.addAppender(_fApp);
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
    _myRecord.alert(msg);
}

void Mylog::debug(const char *msg)
{
    _myRecord.debug(msg);
}

void Mylog::info(const char *msg)
{
    _myRecord.info(msg);
}
