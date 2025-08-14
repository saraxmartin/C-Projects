// Degree: AI
// Subject: FP2
// Delivery: 3
// Implementation of functions related to bubble sort functionality

#include "bubble.h"
#include <stdio.h>


// A function to implement bubble sort
void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void bubbleSort(int array[], int N)
{
    int i, j;
    for (i = 0; i < N - 1; i++)
    {
    // Last i elements are already in place
        for (j = 0; j < N - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
               swap(&array[j], &array[j + 1]); 
            }
        }
    }
}