#include "rss.h"

int main()
{
    RssReader r1;
    r1.parseRss();
    r1.dump("pagelib.txt");
    return 0;
}

