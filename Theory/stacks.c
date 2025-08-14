#include <stdio.h>
#include <stdlib.h>

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
        printf("%d", top->data);
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
    struct Node *temporal = top->next;
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
