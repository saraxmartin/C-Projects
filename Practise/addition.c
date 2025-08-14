#include <stdio.h>

int addition (int,int,int); /*define parameters of function*/

int addition(int x, int y, int z)
{
    z = x + y;
    printf("%d + %d = %d", x,y,z);
}

void main ()
{
    int a=2, b=3, c=25;
    addition (a,b,c);
    printf("%d + %d = %d", a,b,c);
}