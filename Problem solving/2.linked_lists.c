#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};
struct Node *head = NULL;


//& Insert element in the beggining, middle or end of the list
void Insert_Element(int element, int position, int middle_position)
{
    //!General case
    struct Node *new= (struct Node*)malloc(sizeof(struct Node));
    new->data = element;
    // If list is empty
    if (head == NULL)
    {
        head = new;
        new->next = NULL;
        return;
    }
    // If there is one element
    if (head->next == NULL)
    {
        head->next = new;
        new->next = NULL;
        return;
    }
    // If there is more than one element
    //!Specific case
    struct Node *current = (struct Node*)malloc(sizeof(struct Node));
    current = head;
    // Beggining of the list
    if (position == 0)
    {
        new->next = head;
        head = new;
    }
    // Middle of the list
    if (position == 1)
    {
        //Count positions
        int count = 0;
        while (count<middle_position-1 && current->next != NULL)
        {
            current = current->next;
            count += 1;
        }
        // Insert in middle_position
        new->next = current->next;
        current->next = new;
    }
    // End of the list
    if (position == 2)
    {
        while (current->next != NULL)
        {
        current = current->next;
        }
        current->next = new;
        new->next = NULL;
    }
    
}

//& Delete element in first position, middle or end of list
void Delete_Element (int position, int middle_position)
{
    //! General case
    // If list is empty
    if (head == NULL)
    {
        return;
    }
    // If there is one element
    if (head->next == NULL)
    {
        free(head);
        head = NULL;
        return;
    }
    // If there is more than one element
    //! Specific case
    struct Node *current = (struct Node*)malloc(sizeof(struct Node));
    current = head;
    // Delete first element
    if (position == 0)
    {
        head = head->next;
        free(current);
    }
    // Delete middle element
    
    if (position == 1)
    {
        struct Node *eliminate = (struct Node*)malloc(sizeof(struct Node));
        eliminate = current->next;
        int count = 0;
        while (count<middle_position-1)
        {
            current = current->next;
            eliminate = eliminate->next;
            count += 1;
        }
        current->next = current->next->next;
        free(eliminate);
    }
    if (position == 2)
    {
        struct Node * first = head;
        struct Node * last = head->next;
        // Find last element of list
        while (last->next != NULL)
        {
            last = last->next;
            first = first->next;
        }
        // Once found, eliminate last element
        first->next = NULL;
        free(last);
    }
}

//& Count number of nodes in list
void Count_nodes()
{
    struct Node *current = (struct Node*)malloc(sizeof(struct Node));
    int i;
    for (i=0; current->next != NULL; i++)
    {
        current = current->next;
    }
    printf("Number of nodes = ", i);
}

//& Return position of an element in list
void Search_element(int element)
{
    struct Node *current = (struct Node*)malloc(sizeof(struct Node));
    int count = 0;
    while (current->data != element)
    {
        current = current->next;
        count +=1;
    }
    printf("Element found in position %d", count);
}

//& Print list
void print_list()
{
    struct Node *current = (struct Node*)malloc(sizeof(struct Node));
    current = head;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
}

//& Merge two sorted linked lists
void Merge_lists ()
{
    
}

//& MAIN PROGRAM
int main()
{
    int option, element, position, middle_position;
    printf("\nMENU:\n(1) Insert element\n(2) Remove element\n(3) Lenght of list\n(4) Search element\n(5) Exit\n");
    scanf("%d", &option);
    while (option != 5)
    {
        if (option == 1)
        {
            scanf("Element to insert: %d", &element);
            scanf("\nPosition: %d", &position);
            if (position == 1){
                scanf("\nInsert position in middle: %d", &middle_position);
                }
            else{
                middle_position = 0;
                }
            Insert_Element(element, position, middle_position);
        }
        if (option == 2)
        {
            scanf("\nPosition: %d", position);
            if (position == 1){
                scanf("\nInsert position in middle: %d", &middle_position);
                }
            else{
                middle_position = 0;
                }
            Delete_Element(position, middle_position);
        }
        if (option == 3)
        {
            Count_nodes();
        }
        if (option == 4)
        {
            scanf("Element to search: %d", &element);
            Search_element(element);
        }
        printf("\nMENU:\n(1) Insert element\n(2) Remove element\n(3) Lenght of list\n(4) Search element\n(5) Exit\n");
        scanf("%d", &option);
    }
    if (option == 5)
    {
        return 0;
    }
}