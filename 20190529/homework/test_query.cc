#include "textQuery.h"

int main()
{
    string queryWord("the");
    TextQuery tq;
    tq.readFile("china_daily.txt");
    tq.query(queryWord);

    return 0;
}

