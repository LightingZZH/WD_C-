#include "MyLog.h"
#include <string>
using std::string;

int main()
{
    Mylog *log1 = Mylog::getInstance();
    //Mylog *log3 = Mylog::getInstance();
    //log1->warn("this is a warn message");
    //log1->error("this is an error message");
    //log3->debug("this is a debug message");
    //log3->info("this is an info message");
    
    char s1[100] = "this is a warn message";
    char s2[100] = "this is an error message";
    char s3[100] = "this is a debug message";
    char s4[100] = "this is an info message";

    log1->warn((sprintf(s1,"%s%s%s%s%d%s%s",s1," ",__FILE__," ",__LINE__," ",__FUNCTION__),s1));
    log1->error((sprintf(s2,"%s%s%s%s%d%s%s",s2," ",__FILE__," ",__LINE__," ",__FUNCTION__),s2));
    log1->debug((sprintf(s3,"%s%s%s%s%d%s%s",s3," ",__FILE__," ",__LINE__," ",__FUNCTION__),s3));
    log1->info((sprintf(s4,"%s%s%s%s%d%s%s",s4," ",__FILE__," ",__LINE__," ",__FUNCTION__),s4));

    log1->destory();
    return 0;
}

