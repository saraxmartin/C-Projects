#include <stdio.h>
#include <stdlib.h>

#define N 100

void InitArray (float vect[N])
{
    int i;
    for (i=0; i<N; i++)
        vect[i] = (rand()%100)/100.0;
}

float MaxArray (float v[N])
{
    int max = 0;
    int i;
    for (i=0; v[i] > max; i++)
    {
        max = v[i];
    }
    return max;
}

float SumArray (float v[N])
{
    int res=0;
    res = sum(v);
    return res;
}

void AddVectors (float op1[N], float op2[N], float res[N])
{
    int i;
    for (i=0; i<N; i++)
    {
        res[i] = op1[i] + op2[i];
    }
}
void PrintArray(float v[N])
{
    int i;
    for (i=0; i<5; i++)
    {
        printf("%f",v[i]);
    }
}

int main()
{
    float v1[N], v2[N], max_v1,max_v2;
    srand(1234);
    InitArray (v1);
    InitArray (v2);
    max_v1 = MaxArray(v1);
    max_v2 = MaxArray(v2);
    printf("Maximum of v1 is: %d\n", max_v1 );
    printf("Maximum of v2 is: %d\n", max_v2 );
    float res[N];
    AddVectors(v1,v2,res);
    printf("%f", res);
    PrintArray(v1);
    PrintArray(v2);
    PrintArray(res);
    
    return 0;

}