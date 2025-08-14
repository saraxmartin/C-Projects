#include <stdio.h>
#include <stdlib.h>

int Max (int a, int b)
{
    if (a < b) return b;
    return a;
}

int SumDiv (int num)
{
    int sum = 0;
    for (int i = 1; i <= num; i++)
    {
        for (int j = 1; j*j <= i; j++)
        {
            if (i % j == 0)
            {
                if (i / j == j)
                    sum += j;
                else
                    sum +=j + i / j;
            }
        }
    }
    return sum;
}

int main()
{
    int x,y,z,res_1,res_2;
    srand(1234);
    x = rand () % 10000;
    y = rand () % 10000;
    z = Max (x,y);
    printf("The maxiumum value between %d and %d is %d\n", x,y,z);
    res_1 = SumDiv (x);
    res_2 = SumDiv (y);
    printf("The sum of the divisors of %d is %d\n", x,res_1);
    printf("The sum of the divisors of %d is %d", y,res_2);
    return 0;
}
