#include <stdio.h>
void PrintVector(int v[], int n)
{
    int i;
    for (i=0;i<n;i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int Foo (int v[], int n)
{
    PrintVector(v,n);
    if (n == 0)
        return 0;
    else
        return Foo (v,n-1)*10+v[n-1];
}

int Foo2(int v[], int n)
{
    int result = 0;
    int i;
    for (i=0; i<n; i++)
    {
        result = result*10+v[i];
        printf("%d ",result);
    }
}

void main()
{
    int v[]= {3, 5, 7, 4, 6};
    Foo(v, 5);
    Foo2(v,5);
}