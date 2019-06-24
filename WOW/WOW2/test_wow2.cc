#include "wow2.h"

int main()
{
    Headquarter h1(20,"red",3,4,5,6,7);
    Headquarter h2(20,"blue",3,4,5,6,7);
    while(h1.getFlag()!=-3 || h2.getFlag()!=-3)
    {
        h1.Create();
        h2.Create();
    }

    return 0;
}

