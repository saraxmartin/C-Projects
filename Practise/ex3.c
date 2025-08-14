#include <stdio.h>
#include <stdlib.h>

void InitVector (int* v, int nElements)
{
    int i;
    for (i=0; i<nElements; i++)
    {
        v[i] = i;
    }
    
}

void AddVectors (int* v1, int* v2, int* vSuma, int nElements)
{
    
    int i;
    for (i=0; i<nElements; i++)
    {
        *(vSuma + i) = *(v1 + i) + *(v2 + i);
    }
}

void ShowVector(int* v, int nElements)
{
    int i;
    for (i=0; i<nElements; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main()
{
    int size;
    int *vector1, *vector2, *vector3;
    scanf("%d",&size);
    vector1 = (int*)malloc(size * sizeof(int));
    vector2 = (int*)malloc(size * sizeof(int));
    vector3 = (int*)malloc(size * sizeof(int));
    InitVector(vector1, size);
    ShowVector(vector1, size);
    InitVector(vector2, size);
    ShowVector(vector2, size);
    AddVectors(vector1, vector2, vector3, size);
    ShowVector(vector3, size);
    free(vector1);
    free(vector2);
    free(vector3);

}