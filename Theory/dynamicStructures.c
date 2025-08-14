#include <stdio.h>
#include <stdlib.h>

// !DYNAMIC STRUCTURES

//& Dynamic array (vector)
#define size 10
int v[size];

int dynamic_array()
{
    int* v;
    v = (int*)malloc(size*sizeof(int));
    //Content: v[index] / *(v+index)
    //Adress: &v[index] / v+index
    // v is &v[0] (adress of element 0)
    int* p;
    p = v; // = &v[0]. Connect pointer with adress of vector
    //*p -> gives content of first element
    // Treat pointer as an array:p[i]=v[i]=*(p+i)=*(v+i)
    free(v);
}


// & Lists
struct Node
{
    int data;
    struct Node *next;
    // Next is a pointer to connect to next item in list (its adress)
    // If it is the last student, in memory: NULL
};
// We must have a pointer of the adress of the 1st element
struct Node *head = NULL;
struct Node *current = NULL;

int main_dynamic_data()
{
    //Lists: insert/remove from any position
    //Queues: insert end, remove begginning
    //Stacks: insert and remove from begginning
    struct Node * Nodes; //dinamic way
    // I want 100 elements in a list
    Nodes = (struct Node*)malloc(100*sizeof(struct Node));
    // To access an element in list, we will have to go 
    //   through all elements until finding the one (like Python)
}

//Insert element: Node * insert(type value, Node* position)
void Insert_Element_First(int data, struct Node *node)
{
    // Create a link
    struct Node *link= (struct Node*)malloc(sizeof(struct Node));
    // link->key = key
    link->data = data;
    // If head is empty, create new list
    if (head == NULL) 
    {
        head = link;
        link->next = NULL;
        return;
    }
    // Point it to old first node
    link->next = head;
    // Point first to new first node
    head = link;
}

void Insert_Element_Middle (int data, struct Node *node)
{
    
}

// Remove element from list: Node* remove(Node* position)
void Remove_Element(int data)
{
    if (head==NULL)
    {
        printf("Linked list not initialized");
        return;
    }
    if (head->data == data)
    {
        //If the next from the element we want to remove is not NULL,
        //  the new first will be the next
        if (head->next !=NULL){
            head = head->next;
            return;
        //If the next element is NULL
        } else{
            head = NULL;
            printf("List is empty now");
            return;
        }
    }
}

// Print the elements of the list
void Print_list()
{
    struct Node * current = head;
    while (current !=NULL)
    {
        printf("%d ",current = head);
        current = current->next;
    }
}




// &Stacks
struct Node
{
    int data;
    struct Node *next;
};
// In stack we need a pointer to top element
// If it's last item it will indicate NULL
struct Node *top = NULL;

void Print_Stack(int data, struct Node *next)
{
    // Define temporal variable to iterate
    struct Node *current = top;
    // Loop through stack to print all elements until current->next is NULL
    while (current->next!=NULL)
    {
        prinf("%d", current->data);
        current = current->next;
    }
}

// ~ STANDARD OPERATIONS
void push (int data) // Insert element on top of the stack
{
    // Create new element
    struct Node *new_element = malloc(sizeof(struct Node));
    // Link data to new element
    new_element->data = data;
    // If stack is empty:
    if (top == NULL)
    {
        top = new_element;
        printf("%d", top->data)
        top->next = NULL;
    }
    // Assign ...
    new_element->next = top;
    top = new_element;
}
void pop() // Removes top element
{
    // If stack is empty
    if (top == NULL)
    {
        // Nothing happens
        return;
    }
    // If I have 1 element
    if (top->next == NULL)
    {
        // Eliminate element
        free(top);
        top = NULL; // Stack is now empty
    }
    // If I have more than 1 element
    // Create temporal variable
    struct Node *temporal = top->next
    free(top);
    top = temporal;
}

int main_Stack()
{
    // Order of stack: 30, 20, 10
    push(10);
    push(20);
    push(30);
    pop(); // removes first/top element (30)
}

// &Queues
struct Node
{
    int data;
    struct Node *next;
};
struct Node *first = NULL;
struct Node *last = NULL;

void insert_element(int data)
{
    // Create new element and add data
    struct Node *new_element = malloc(sizeof(struct Node));
    new_element->data = data;
    // If queue is empty:
    if (first == NULL)
    { 
        first = new_element;
        first->next = NULL;
        last = first
    }
    // If queue is not empty
    last->next = new_element;
    last = new_element;
    last->next = NULL; 
}

void remove_element()
{
    if (first == NULL)
    {
        // Nothing happens
        return;
    }
    // If we have 1 element
    if (first->next == NULL)
    {
        free(first);
        first = NULL;
        last = NULL;
    }
    // If we have more than 1 element
    // Create temporal variable
    struct Node *temporal = first->next
    free(first);
    first = temporal;
}