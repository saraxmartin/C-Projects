#include <stdio.h>
#include <stdlib.h>

struct Node
{
    char data;
    struct Node *next;
};
struct Node *head = NULL;

void print_list() 
{ 
    printf("Output list => ");
    struct Node * current = head; 
    while (current != NULL) 
    {  
        printf("%c ", current->data); 
        current = current->next; 
    } 
    printf ("\n");
}

struct Node * SearchNode(char newCharacter, struct Node *link)
{
    struct Node *current = head;
    // While the next position is not null and 
    // its character is lower or equal than our newCharacter:
    while (current->next != NULL && current->next->data <= newCharacter)
    {
        // If character already exists in list
        if (current->next->data == newCharacter)
        {
            printf("The character '%c' already exists in the list.\n", newCharacter);
            free(link);
            return 0;
        }
        current = current->next;
    }
    // 
    link->next = current->next;
    current->next = link;

}

void InsertNode(char newCharacter)
{
    // Create new element
    struct Node *link=(struct Node*)malloc(sizeof(struct Node));
    link->data = newCharacter;
    // a) If list is empty:
    // Create a new list
    if(head==NULL) 
       {
        head = link;
        link->next = NULL;
        return;
       }
    // b) If list is not empty
    // If the character is the same
    if (newCharacter == head->data)
    {
        printf("The character '%c' already exists in the list.\n", newCharacter);
        free(link);
        return;
    }
    // Insert node at the first location if is smaller
    if(newCharacter < head->data)    
    {
        link->next = head;
        head = link;
        return;
    }
    // If is bigger, search for place to insert character
    SearchNode(newCharacter, link);

}

void RemoveFirstAndLastNode()
{
    // If list is already empty
    if (head == NULL)
    {
        return;
    }
    // If there is only one element
    if (head->next == NULL)
    {
        free(head);
        head = NULL;
    }
    // If there is more than one element
    if (head->next!=NULL) 
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
    head = head->next;
    
}

int main()
{
    char newCharacter;
    printf("Welcome to the sorted list! \n");
    printf("Which character would you like to insert? ");
    scanf(" %c", &newCharacter);
    // Until char == 9, insert character to list
    while (newCharacter != '9')
    {
        InsertNode(newCharacter);
        print_list();
        printf("Which character would you like to insert? ");
        scanf(" %c", &newCharacter);
    }
    // If char == 9:
    RemoveFirstAndLastNode();
    print_list();
    return 0;
}
