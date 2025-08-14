#include <stdio.h>
#include <stdlib.h>
#define SIZE 40 // Size of the graph

// BFS = Breadth First Search
// DFS = Deep First Search

struct QueueNode //for BFS
{
    int data;
    struct QueueNode *next;
};
struct QueueNode *first;
struct QueueNode *last;

struct StackNode // for DFS
{
    int data;
    struct StackNode *next;
};
struct StackNode *top;

struct Node // general structure
{
    int data;
    struct Node *next;
};

// If we have adjacency matrix: adjMatrix[N][N]; // static array (global)
// To create adjancency matrix: (in struct Graph)
//  int ** adjMatrix; // dynamic 2D array (malloc)
//  adjMatrix[i][j];
//  int * adjMatrix; // dynamic 1D array (malloc)
//  adjMatrix[i*N+j];

struct Graph
{
    int numNodes;
    struct Node **adjLists; // array of pointers to nodes
    int **adjMatrix;
    int *visited;
};

// Creating a node
struct Node * CreateNode(int data)
{
    struct Node *new = malloc(sizeof(struct Node));
    new->data = data;
    new->next = NULL;
    return new;
}

// FUNCTIONS FOR GRAPHS
// Creating a graph
struct Graph * CreateGraph(int numNodes)
{
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->numNodes = numNodes;

    // Create space for list of adj and visited nodes
    graph->adjLists = malloc(numNodes * sizeof(struct Node*));
    graph->visited = malloc(numNodes * sizeof(int));

    // Initialise lists
    for (int i=0; i<numNodes; i++)
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}
// Add edge to graph (LIST)
void AddEdge (struct Graph *graph, int source, int destination)
{
    // 1. Add edge from source to destination
    struct Node *new = createNode(destination);
    new->next = graph->adjLists[source];
    graph->adjLists[source] = new;
    // 2. Add edge from destination to source
    new = createNode(source);
    new->next = graph->adjLists[destination];
    graph->adjLists[destination] = new;
}
// Add Edge to graph (MATRIX)
void AddEdgeM (struct Graph *graph, int source, int destination)
{
    graph->adjMatrix[source][destination] = 1;
    graph->adjMatrix[source][destination] = 1;
}
// Delete Graph
void DestroyGraph(struct Graph *graph);
// Print Graph
void PrintGraph(struct Graph *graph);

// FUNCTIONS FOR QUEUE
// Create a queue
struct QueueNode * createQueue();
// Check if queue is empty // Not used?
int isEmpty ()
{
    if (first = last = NULL)
        return 1;
        
    else
        return 0;
}
// Add elements to queue
void AddToQueue (int data)
{
    struct QueueNode *node=(struct QueueNode*)malloc(sizeof(struct QueueNode));
   	node->data = data;
	if(first==NULL)
   	{
    	first = last = node;
    	node->next = NULL;
    	return;
   	}
	struct QueueNode * current=first;
	while(current->next!=NULL)
   	{
		current=current->next;
	}
	node->next=NULL; 
	last->next=node;
	last=node;
	return;
}
// Remove elements from queue
void Dequeue ()
{	
	if (first == NULL) 
    	return;
   	if (first->next==NULL) //first==last
	{			
		free (first);
        first = last = NULL;
        return;
	} 
	struct QueueNode *current=first;	
	first = current->next;
	free(current);
	return;

}
// Print queue
void PrintQueue()
{ 
    struct QueueNode *current = first; 
    while (current != NULL) 
    {  
        printf("%d=>", current->data); 
        current = current->next; 
    } 
	printf ("\n");
}

// BFS ALGORITHM
void bfs(struct Graph *graph, int root)
{
    //struct Queue *queue = createQueue();
    graph->visited[root] = 1;
    AddToQueue(root); // root = data of root

    while (first != NULL) // queue is not empty
    {
        PrintQueue();
        struct QueueNode *currentNode = first;
        Dequeue();
        printf("Visited node %d\n", currentNode->data);

       //.... 
    }

}
// DFS ALGORITHM
void dfs(struct Graph *graph, int root);



int main()
{
    struct Graph *graph = createGraph(6);
    // AddEdge(graph,0,1)
    // AddEdge(graph,0,2) ...
    return 0;
}
