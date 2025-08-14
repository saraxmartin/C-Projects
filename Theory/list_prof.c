#include <stdio.h>
#include <stdlib.h>

struct Node
{
   int data; // key
   struct Node *next;
};

struct Node *head = NULL; // first​

void print_list() 
{ 
    struct Node * current = head; 
    while (current != NULL) 
    {  
        printf("%d=>", current->data); 
        current = current->next; 
    } 
	printf ("\n");
}

//insert new element after the indicated node​, if node==NULL, at the first position
void insertElement(int data, struct Node * node) 
{
   //create a new element
   struct Node *link=(struct Node*)malloc(sizeof(struct Node));
   //link->key = key;​
   link->data = data;
   // If head is empty, create new list​
	if(head==NULL) 
   	{
		printf("head NULL, creating the list\n");
    	head = link;
    	link->next = NULL;
    	return;
   	}
	//insert link at the first location​
	if(node==NULL)	
	{
		printf("Node NULL, insert as first\n");
 	 	//point it to old first node​
   		link->next = head;
		//point first to new first node​
   		head = link;
		return;
	}
	//insert link at the end 
	if (node->next==NULL)
	{
		printf("Insert as last\n");
		//point the new last node to NULL
		link->next=NULL; //link->next=node->next;
		//point the last node to the new node​
   		node->next=link;
		return;
	}
	printf("Inserting after node with data %d\n", node->data);
	link->next=node->next;
	node->next=link;
	return;
}
 
//remove the element after the indicated node​, if node==NULL, remove from the first position
void removeElement (struct Node * node)
{	
	if (head==NULL) 
	{
    	printf("Linked List not initialized");
    	return;
    }

	// remove the first element
   	if (node==NULL) 
	{
		struct Node * current=head;
		printf ("Remove the first element\n");
    	if(head->next != NULL)
		{
        	head = head->next;
			free (current);
	        return;
      	} 
		else //head->next==NULL
		{
			free (head);
         	head = NULL;
			//free (current);
         	printf("List is empty now");
         	return;
		} 
	}
	if (node->next==NULL) 
	{
		printf("nothing to remove\n");
		return;
	}
	else 
	{
		struct Node * to_remove=node->next;
		printf("Eliminating data %d\n", to_remove->data);	
		node->next=to_remove->next;
		free(to_remove);
		return;
	}
}

struct Node * SearchNode(int data)
{
	if (head==NULL) // list is empty
		return NULL;

	struct Node * current=head;
	while (current->next!=NULL)
	{
		if (current->data==data)
			return current;
		else current=current->next;
	}
	return current; //NULL; // not found
}

int main (int argc, char ** argv)
{
	printf ("Starting... \n");

    insertElement(10, NULL); 
    insertElement(20, NULL); 
    insertElement(30, NULL);
    print_list();
	struct Node * el = SearchNode(10);
    insertElement(40, el);
	print_list();
	el = SearchNode(20);
	insertElement(50, el);
	print_list();
	removeElement(NULL);
    print_list();
	el = SearchNode(20);
	removeElement(el);
    print_list();
	el = SearchNode(10);
	removeElement(el);
    print_list();
	insertElement(30, NULL);
    print_list();
	el = SearchNode(100);
	insertElement(60, el);
	print_list();
    return 0;
}