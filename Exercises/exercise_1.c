#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv[])
{
    int x, y;
    //argc = 23;
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
// This program enters an argument if none is entered then argv will miss one and the massage "Argument is missing (integer)" will be printed. 
// Otherwise if the value entered is a string the function atoi will change it for an integer. Then if x (being that the integer) is negative it will have
// the same value but as positive (if the value was -345 then it will be converted in 345). 
// Then in the  for loop you will sum the "residu" until the dividend is less than 10 at that point it will end. (For exemple having 34 you will divide it
// by 10 and the "quocient" will be 3 and the "residu" = 4 (this will be a new value of y) then 3 as the quocient will be devided by 10, so the "quocient"
// will ne 0'... and the "residu"= 3. So 4+3 =7. That will be the result)
// if the terminal tries with value 1 the result is 1
// if the terminal tries with value -3456 the result is 18
// if the terminal tries with value 1000000 the result is 1
// if the terminal tries with value "Hello" the result is 0
// if the terminal tries with value 9999.9 the result is 36
