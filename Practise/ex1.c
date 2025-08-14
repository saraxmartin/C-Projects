#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv[])
{
    int x, y;
    if (argc < 2)
    {
        printf( "Argument is missing (integer)\n");
        exit (1);
    }
    x = atoi(argv[1]);
    if ( x < 0 ) x*=-1;
    // for (initialization; condition; increment)
    // y+=x%10 means y=y+(x%10)
    for (y=0; x > 0; y+=x%10, x/=10);
    printf ("Resultat %d\n", y);
    return 0;
}