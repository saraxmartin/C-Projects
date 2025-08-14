#include <stdio.h>
#include <stdlib.h>

struct Graph
{
    int numNodes;
    int **matrix;
};
struct node
{
    int data;
};

void PrintGraph(struct Graph * g)
{
    int i,j,c;
    for(i=0; i< 5; i++)
    {
        for (j=0; j< 4; j++)
        {
            int a = g->matrix[i][j];
            printf("%d=>",a);
        }
        int a = g->matrix[i][4];
        printf("%d",a);
        printf("\n");
    }
}
struct Graph * createGraph (int numNodes)
{
    struct Graph * g=malloc(sizeof(struct Graph));
    g->numNodes=numNodes;
    g->matrix=malloc(numNodes*sizeof(int*));
    for (int i=0; i<numNodes; i++)
    {
      g->matrix[i]=malloc(numNodes*sizeof(int));
    }
    return g;
}

void AddZero(struct Graph *g)
{
    int l,m;
    for (int l=0; l<g->numNodes; l++)
    {
      for (int m=0; m<g->numNodes; m++)
      {
        g->matrix[l][m] = 0;
      }
    }
}
void AddEdge(struct Graph *g, int src, int dest, int val)
{
    g->matrix[src][dest] = val;
    g->matrix[dest][src] = val;
}


int main ()
{
    struct Graph * g = createGraph (5);
    AddZero(g);
    AddEdge (g, 0, 1, 5);
    AddEdge (g, 0, 4, 3);
    AddEdge (g, 1, 2,2);
    AddEdge (g, 1, 3, 7);
    AddEdge (g, 1, 4, 6);
    AddEdge (g, 3, 4, 5);
    PrintGraph (g);
    return 0;
}