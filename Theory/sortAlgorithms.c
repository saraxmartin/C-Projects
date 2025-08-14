#include <stdio.h>
#include <stdlib.h>

void print_array(int arr[10])
{
    int i;
    for (i=0; i<10; i++)
        printf("%d ",arr[i]);
}
//Bubble sort
void swap (int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i=0; i<n-1; i++)
        for (j=0; j<n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(&arr[j],&arr[j+1]);
}

//Rank sort
void rankSort(int arr[], int n)
{
    int i,j, rank = 0;
    int b[n]; //?? new array
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
            rank += (arr[i] > arr[j]);
        b[rank] = arr[i];
    }
    }
    

void main()
{
    int arr[10] = {2,3,1,10,3,5,8,-1,7,4};
    bubbleSort(arr, 10);
    print_array(arr);
}
