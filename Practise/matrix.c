#include<stdio.h>
#define size 3
void main()
{
    int vector[size] = {3,3,1};
    int matrix[size][size] = {{1,1,1},{2,1,2},{2,2,2}};
    int result[size];
    int i,j;
    
    /*initialization of result vector*/
    for (i=0; i<size; i++)
        result[i] = 0;

    /*calculate result*/
    for (i=0; i<size; i++)
        for (j=0; j<size; i++)
            result[i]+=matrix[i][j] * vector [j];
    
    /*print*/
    for (i=0; i<size; i++)
        printf(" row %d -> %d \n", i, result[i]);
    
}
