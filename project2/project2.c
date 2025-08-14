/*
Degree: Artificial Intelligence
Subject: Fundamentals of Programming 2
Practical project: 2

Sara Martín (1669812) and Lara Rodriguez (1667906)

Main program

How to execute:
1. From cmd terminal: gcc -DSIZE=\"small.h\" project2.c -o project2 and then project2.exe
2. From linux terminal: gcc -DSIZE=\"small.h\" project2.c -o project2 and then ./project2
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Compilation to include header with necessary structures
#ifdef SIZE
    #include SIZE
#endif

// Global variables
#define INF 99999
int total_cost = 0;
int dfs_arr[NUMBER_CITIES]; // Array to store dfs order
int bfs_arr[NUMBER_CITIES]; // Array to store bfs order
int length_dfs = -1; // Size of array dfs_arr
int length_bfs = -1; // Size of array bfs_arr

// ROAD MAP FUNCTIONS
struct RoadMap * head = NULL; // Pointer to head of list
// Function to add a new city to the Road Map - list
void addToRoadMap(int path[], int total_cost)
{
    // Create new element with Struct RoadMap
    struct RoadMap * city = (struct RoadMap*)malloc(sizeof(struct RoadMap));
    memcpy(city->path,path, sizeof(int) * NUMBER_CITIES);
    city->total_cost = total_cost;
    city->next = NULL;
    
    if (head == NULL) // If list of RoadMap is empty:
    {
        head = city;
        return;
    }
    // If list of RoadMap is not empty, insert as the last:
    struct RoadMap * current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = city;
    return;
}
// Function to print the partial road map
void printPartialRoadMap()
{
    struct RoadMap * current = head;
    while (current != NULL)
    {
        int length = sizeof(current->path) / sizeof(int);
        for (int i=0; i<length; i++)
        {
            if (current->path[i] == -1)
                break;
            struct CivilRegistry city = citiesInfo[current->path[i]];
            printf("%s", city.city_name);
            if (current->path[i+1] != -1)
                printf("->");
        } 
        printf("; Cost = %d\n", current->total_cost);
        current = current->next;
    }
}
// Function to print the Road Map
void printRoadMap()
{
    struct RoadMap * current = head; 
    while (current != NULL) 
    {
        int length = sizeof(current->path) / sizeof(int);
        for (int i=0; i<length; i++)
        {
            struct CivilRegistry city = citiesInfo[current->path[i]];
            if (current->next == NULL && current->path[i] == -1) // If its the last element of the list and the last city has been printed
                break;
            else if (current->next != NULL && current->path[i+1] == -1) // If is the last city of that element, we don't print it
                break;
            else if (current->next == NULL && current->path[i+1] == -1)
                printf("%s", city.city_name);
            else{
                printf("%s=>", city.city_name);
            }
        } 
        current = current->next;
    } 
	printf ("\n");
}
// Function to delete the Road Map at the end of execution
void deleteAllRoadMap()
{
	if (head == NULL) // If the roadmap is empty
	    return;

	// If the list is not empty
	struct RoadMap *current = head;
	while (current!=NULL)
	{
		if (current->next == NULL) // If there is only one book in list
		{
			head = NULL;
			free(current);
			break;
		}
		else // If there is more than one book in the list
		{
			head = current->next;
			free(current);
			current = head;
		}
	}
}

// Function to choose the route with less cost - Dijkstra's algorithm
void RouteSearch(int src, int dest)
{
    // Initialize variables
    int visited[NUMBER_CITIES] = {0}; // Mark all cities as unvisited
    int distance[NUMBER_CITIES]; // Array with distance from source to each city
    for (int i = 0; i < NUMBER_CITIES; i++) {
        distance[i] = INF;
    }
    distance[src] = 0;
    int previous[NUMBER_CITIES]; // Array to store the previous city in shortest path

    // Dijkstra algorithm
    for (int i = 0; i<NUMBER_CITIES; i++)
    {
        // Find city with minimum distance that hasn't been visited yet
        int min_distance = INF;
        int min_city = -1;
        for (int j = 0; j<NUMBER_CITIES; j++)
        {
            // If the city hasn't been visited and the distance is lower than the minimum
            if (!visited[j] && distance[j] < min_distance){
                min_distance = distance[j]; // New min distance
                min_city = j; // New min city
            }
        }
        if (min_city == -1) // If there are no more reachable cities
            break; // Exit the loop
        visited[min_city] = 1;

        // Update distances of the unvisited cities of the current city
        for (int j = 0; j<NUMBER_CITIES; j++)
        {
            if (adjacency_matrix[min_city][j] != 0 && distance[min_city] != INF)
            {
                int new_distance = distance[min_city] + adjacency_matrix[min_city][j];
                if (new_distance < distance[j]){
                    distance[j] = new_distance;
                    previous[j] = min_city;
                }
                    
            }
        }
    }
    // Traverse previous array to construct path
    int path[NUMBER_CITIES];
    int path_length = 0;
    int current_city = dest;
    while (current_city != src){
        path[path_length++] = current_city;
        current_city = previous[current_city];
    }
    path[path_length++] = src;
    
    // Reverse the path array
    for (int i = 0; i<path_length/2; i++)
    {
        int temp = path[i];
        path[i] = path[path_length-i-1];
        path[path_length-i-1] = temp;
    }

    // Fill in array with -1
    for (int i=path_length; i<NUMBER_CITIES; i++){
        path[path_length++] = -1;
    }

    total_cost += distance[dest]; // Update global variable
    addToRoadMap(path,distance[dest]); // Add route to road map

    return; 
}

// Function to create the road map once we have the array of the order of the route
void CreateRoadMap(int arr[], int length)
{
    // Fill in array with -1
    for (int i=++length; i<NUMBER_CITIES; i++){
        arr[length] = -1;
    }
    // Traverse through array 2 by 2 and compute route
    for (int i=0; i<length; i++){
        if (arr[i+1] == -1)
            break;
        int city_1 = arr[i];
        int city_2 = arr[i+1];
        RouteSearch(city_1, city_2);
    }
}

// ANCESTORS' TREE
// Function to create a new node
struct FamilyTreeNode* createNode(char* motherName, char* fatherName, int city_id)
{
    struct FamilyTreeNode * node=(struct FamilyTreeNode*)malloc(sizeof(struct FamilyTreeNode));
    strcpy(node->motherName,motherName);
    strcpy(node->fatherName,fatherName);
    node->city_id = city_id;
    node->mother_parents = NULL;
    node->father_parents = NULL;
    return node;
}
// Function to create Tree using the DFS algoritm
struct FamilyTreeNode* CreateTree(char* motherName, char* fatherName, int city_id)
{
    struct FamilyTreeNode *node = createNode(motherName,fatherName,city_id);

    if (city_id == -1) // No city information
        return node;

    // Get city information
    struct CivilRegistry city = citiesInfo[city_id];
    
    // Build mother's family tree recursively
    if (city.mother_parents_city_id != -1)
        node->mother_parents = CreateTree(city.mother_name,city.father_name,city.mother_parents_city_id);
    else
        node->mother_parents = NULL;
    // Build father's family tree recursively
    if (city.father_parents_city_id != -1)
        node->father_parents = CreateTree(city.mother_name,city.father_name,city.father_parents_city_id);      
    else
        node->father_parents = NULL;

    return node;
}
// Function to print tree DFS and store order by DFS in dfs_arr[]
void DFS(struct FamilyTreeNode *node)
{
    if (node == NULL)
        return;
    struct CivilRegistry city = citiesInfo[node->city_id]; // Get info of the city of node
    printf("%s and %s (%s)\n", city.mother_name,city.father_name,city.city_name); // Print parents from city
    dfs_arr[++length_dfs] = node->city_id; // Store city_id in the dfs array
    DFS(node->mother_parents);
    DFS(node->father_parents);
}
// Function to print tree BFS and store order by BFS in bfs_arr[]
void BFS(struct FamilyTreeNode *node)
{
    if (node == NULL)
        return;

    struct FamilyTreeNode *queue[NUMBER_CITIES]; // array for a queue
    int first = -1;
    int last = -1;
    queue[++last] = node; // enqueue the root node
    
    while (first != last){
        struct FamilyTreeNode * current = queue[++first]; // Put current as queue first
        struct CivilRegistry city = citiesInfo[current->city_id]; // Get info of the city of the current node
        printf("%s and %s (%s)\n",city.mother_name,city.father_name,city.city_name); // Print parents from city
        bfs_arr[++length_bfs] = current->city_id; // Store city_id in bfs array

        // Enqueue parent nodes
        if (current->mother_parents != NULL)
            queue[++last] = current->mother_parents;
        if (current->father_parents != NULL)
            queue[++last] = current->father_parents;
    }
}


void main()
{
    // Initialize root node city information
    struct CivilRegistry city = citiesInfo[0]; 
    // Create Family Tree
    struct FamilyTreeNode *root = CreateTree(city.mother_name,city.father_name,city.city_id);

    // Print start
    printf("\nThis program is using the header file %s.\n", SIZE);
    printf("\nAncestor's tree:\n");
    
    // FamilyTree and RoadMap with BFS algorithm
    printf("\nBFS -> Names:\n");
    BFS(root); // While printing the tree by BFS, we store the order of the cities we need to visit
    CreateRoadMap(bfs_arr,length_bfs); // We create the road map following the order from the bfs_array created above
    printf("\nPartial road map: \n");
    printPartialRoadMap(); // Printing the road map of each route with its final cost
    printf("\nTotal Road Map: \n");
    printRoadMap(); // Printing the road map of each city we have visited
    printf("\nTotal cost: %d\n", total_cost);

    total_cost = 0; // Set global variable to 0 again
    deleteAllRoadMap(); // Delete RoadMap to create the new one

    // FamilyTree and RoadMap with DFS algorithm
    printf("\nDFS -> Names:\n");
    DFS(root); // While printing the tree by DFS, we store the order of the cities we need to visit
    CreateRoadMap(dfs_arr, length_dfs); // We create the road map following the order from the dfs_array created above
    printf("\nPartial road map: \n");
    printPartialRoadMap(); // Printing the road map of each route with its final cost
    printf("\nTotal Road Map: \n");
    printRoadMap(); //  Printing the road map of each city we have visited
    printf("\nTotal cost: %d\n", total_cost);
    
}

