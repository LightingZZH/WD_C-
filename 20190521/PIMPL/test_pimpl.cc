#include "pimpl.h"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
    Line line(1,2,3,4);
    line.printLine();

    /* Line::Point pt(11,22); */    //error
    /* pt.print(); */
    return 0;
}

