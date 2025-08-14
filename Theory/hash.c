#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

struct Element {
   int data;   
   int key;
};

struct Element * hashArray[SIZE]; 

//return the index to the hash table
int hashCode(int key) 
{
    return key % SIZE;
}

struct Element * search(int key) 
{
    printf("Searching for key %d... ", key);
    //get the hash 
    int hashIndex = hashCode(key); 
	int hashIndexOrig=hashIndex; 
    int iter=0;
    //search for the key in array until found or empty 
    while(1) 
    {
        iter++;
        if (hashArray[hashIndex] != NULL) 
        {
            if(hashArray[hashIndex]->key == key)
            {
                printf("Element found: key=%d, value=%d, iterated %d times\n", hashArray[hashIndex]->key, hashArray[hashIndex]->data, iter);
                return hashArray[hashIndex]; 
            }
        }

        //go to next cell
        hashIndex++;
	    //wrap around the table
        hashIndex %= SIZE;
        if (hashIndex == hashIndexOrig) 
            break;
    }        
    printf("Element not found, iterated %d times\n", iter);
    return NULL;        
}

//reserve the memory for the element and assign key/value 
//calculate the hashIndex
//search for the position (hashIndex) to insert
//      if the position is ocupied, move in the table until an empty cell
//insert the element to the hash table on the found position
void insert(int key, int data) 
{
    // Get new index
    int new_index = hashCode(key); // Fixed: added missing declaration and used HashNode() function to compute index
    // Create new Element
    struct Element *new = (struct Element*) malloc(sizeof(struct Element));
    new->key = key;
    new->data = data;

    // Insert element
    while (hashArray[new_index] != NULL && hashArray[new_index]->key!=key)
    {
        new_index++;
        new_index %= SIZE;
    }
    if (hashArray[new_index]!=NULL)
    {
        printf("Error: Key %d already exists in hash table.\n", key);
    }
    hashArray[new_index] = new;
    return;
}

//calculate the hashIndex
//move in the hash table to find the element to remove
//      if the key of the place is equal to the key of the element, 
//          release the element
//      if not, go to the next position
// you can assume that the element is found
void removeElement(struct Element * element) 
{
    int index = hashCode(element->key);
    while (hashArray[index]!=NULL)
    {
        if (hashArray[index] == element)
        {
            hashArray[index] = NULL;
            free(element);
            return;
        }
        index++;
        index %= SIZE;
    }

}

void display() {
    for(int i=0; i<SIZE; i++) {
	
    if(hashArray[i] != NULL)
        printf(" (%d,%d)", hashArray[i]->key, hashArray[i]->data);
    else
        printf(" -- ");
    }
    printf("\n");
}

int main() 
{
    insert(0, 0);
    insert(1, 20);
    insert(2, 70);
    insert(42, 80);
    insert(4, 25);
    insert(13, 78);
    insert(37, 97);
    insert(20, 0);
    insert(10, 0);
    insert(19, 20);

    display();
    struct Element * item = (struct Element*) malloc(sizeof(struct Element));
    item = search(103);  
    item = search(2);        
    removeElement(item);
    display();
    
    item = search(2);
    display();

    item = search(42);
    removeElement(item);
    display();

    item = search(19);
    removeElement(item);
    display();

    item = search(0);
    removeElement(item);
    display();

    item = search(20);
    removeElement(item);
    display();
}