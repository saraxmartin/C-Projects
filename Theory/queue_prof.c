#include <stdio.h>
#include <stdlib.h>

struct Node
{
   int data;
   struct Node *next;
};
struct Node *first = NULL; 
struct Node *last = NULL;

void print_queue() 
{ 
    struct Node * current = first; 
    while (current != NULL) 
    {  
        printf("%d=>", current->data); 
        current = current->next; 
    } 
	printf ("\n");
}
//add new element to the queue
void addElement (int data) 
{
   	//create a new element
   	struct Node *newElement=(struct Node*)malloc(sizeof(struct Node));
   	newElement->data = data;
   	// If the queue is empty, create new queue
	if(first==NULL) 
   	{
		printf("first NULL, creating the queue\n");
    	first = last = newElement;
    	newElement->next = NULL;
    	return;
   	}
	struct Node * current=first;
	while(current->next!=NULL) //current!=last
   	{
		current=current->next;
	}
	printf("Insert as last\n");
	newElement->next=NULL; 
	last->next=newElement;
	last=newElement;
	return;
}
 
void removeElement ()
{	
	if (first==NULL) 
	{
    	printf("nothing to remove");
    	return;
    }

	// remove the one element
   	if (first->next==NULL) //first==last
	{			
		printf("removing data %d\n", first->data);
		free (first);
        first = last = NULL;
        printf("List is empty now");
        return;
	} 
	struct Node * tmp=first;
	printf("removing data %d\n", tmp->data);	
	first=tmp->next;
	free(tmp);
	return;

}


int main (int argc, char ** argv)
{
	printf ("Starting... \n");

    addElement(10); 
    addElement(20); 
    addElement(30);
    print_queue();
	removeElement();
	print_queue();
	removeElement();
	print_queue();
	removeElement();
	print_queue();
	removeElement();
	print_queue();
    return 0;
}