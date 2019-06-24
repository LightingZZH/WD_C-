#include "MyLog.h"
#include <string>
using std::string;

void test()
{
    int number = 100;
    const char * pstr = "hello, log4cpp";
    LogInfo("this is an info message. number = %d, str = %s\n", number, pstr);
}

int main()
{
   // LogInfo("Info Message");
   // LogError("Error Message");
   // LogWarn("LogWarn Message");
   // LogDebug("Debug Message");
    test();
    Mylog::destory();
    return 0;
}

