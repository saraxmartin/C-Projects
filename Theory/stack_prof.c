#include <stdio.h>
#include <stdlib.h>

struct Node
{
   int data;
   struct Node *next;
};
struct Node *top = NULL; 

void print_stack() 
{ 
    struct Node * current = top; 
    while (current != NULL) 
    {  
        printf("%d=>", current->data); 
        current = current->next; 
    } 
	printf ("\n");
}

//add new element to the stack
void push (int data) 
{
   	//create a new element
   	struct Node *newElement=(struct Node*)malloc(sizeof(struct Node));
   	newElement->data = data;
   	// If the stack is empty, create new stack
	if(top==NULL) 
   	{
		printf("top NULL, creating the stack\n");
    	newElement->next = NULL;
		top = newElement;
    	return;
   	}
	//struct Node * current=top;
	printf("Insert to the top\n");
	newElement->next=top; 
	top=newElement;
	return;
}
 
void removeElement ()
{	
	if (top==NULL) 
	{
    	printf("nothing to remove");
    	return;
    }

	// remove the one element
   	if (top->next==NULL)
	{			
		printf("removing data %d\n", top->data);
		free (top);
        top = NULL;
        printf("List is empty now");
        return;
	} 
	struct Node * tmp=top;
	printf("removing data %d\n", tmp->data);	
	top=tmp->next;
	free(tmp);
	return;
}

int main (int argc, char ** argv)
{
	printf ("Starting... \n");

    push(10); 
    push(20); 
    push(30);
    print_stack();
	removeElement();
	print_stack();
	removeElement();
	print_stack();
	removeElement();
	print_stack();
	removeElement();
	print_stack();
    return 0;
}