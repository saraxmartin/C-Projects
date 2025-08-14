#include <stdio.h>

// EXERCISE 2 - Search algorithms

void PrintArray( int arr[])
{
    int i;
    for (i=0; i<10; i++)
    {
        printf("%d ", arr[i]);
    }
}


int main()
{
    int arr[10] = {2,6,-1,4,-7,8,3,2,-6};
    int i, count = 0;
    
    printf("The input array is: ");
    PrintArray(arr);

    for (i=0; i<10; i++)
    {
        if (arr[i]<0)
        {
            count+=1;
            arr[i] *= -1;
        }
    }

    printf("\nThe output array is: ");
    PrintArray(arr);
    printf("\nThere are %d negative elements.", count);

}