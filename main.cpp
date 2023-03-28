#include "header.h"
#include "level.h"
#include "menu.h"


    //Xem them o phan define cach khai bao con tro
    // ppc(C,n+2,m+2);
    // ppb(ate,n+2,m+2);
    // ppc(view,n * hei - (n - 2) + 1, m * wid - (m - 2) + 1);
    // ppc(pic,n * hei - (n - 2) + 1, m * wid - (m - 2) + 1);
    // ppb(movingOn,n * hei - (n - 2) + 1, m * wid - (m - 2) + 1);
    // ppb(selected,n * hei - (n - 2) + 1, m * wid - (m - 2) + 1);
    // ppc(cpy,n * hei - (n - 2) + 1, m * wid - (m - 2) + 1);

int main()
{
    srand(time(0));
    displayMenu();
    return 0;
}