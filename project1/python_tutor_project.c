#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//BOOKS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char authors[8][20]={{"Philip Roth"}, {"Dan Brown"}, {"Charlotte Bronte"}, {"Stephenie Meyer"},{"Katarzyna Grochola"}, {"J.K. Rowling"}, {"Veronica Roth"}, {"Yann Martel"}};
char titles[8][20]={{"Nemesis"}, {"Origin"}, {"Jane Eyre"}, {"The host"},{"Zielone drzwi"}, {"Harry Potter"}, {"Divergente"}, {"Life of Pi"}};
struct Book
{
    char author[20];
    char title[20];
    int year; 
   struct Book *next;
};
struct Book * booksHead = NULL;
struct Book * GenerateBook()
{
    struct Book * book=malloc(sizeof(struct Book));
    int bookNum=rand()%8;
    strcpy (book->author, authors[bookNum]);
    strcpy (book->title, titles[bookNum]);
    int year=rand()%40+1980;
    book->year=year;
    return book;
}
void PrintBooks()
{
    struct Book * currentBook = booksHead;
    while (currentBook != NULL)
    {
        printf("\n%c, %c, %d\n", currentBook->author, currentBook->title, currentBook->year);
        currentBook = currentBook->next;
    }
    printf("\n");
}
void SimulateSortingBooks(struct Book * book)
{
    if (booksHead == NULL)
    {
        printf("\nOh! The shelf is empty! Our book %c is the only on the shelf.",book->title);
        booksHead = book;
        book->next = NULL;
        return;
    }
    struct Book * current = booksHead;
    while (current != NULL)
    {
        char *book_author = book->author;
        char *current_author = current->author; 
        int result;
        result = strcmp(book_author,current_author);
        if (result == 0)
        {
            printf("\nThis book is already in the shelf, let's donate it.\n");
            free(book);
        }
        if (result > 0) // Our book's author is >, continue searching
        {
            current = current->next;
        }
        if (result < 0) // Our book's author is <, put before current
        {
            if (current == booksHead)
            {
              booksHead = book;
            }
            book->next = current;
            printf("\nWe have found the perfect place for our book!\n");
            return;
        }
    }
    printf("\nThis is how our shelf is looking for now...:");
    PrintBooks();      
}
main()
{
  struct Book *book;
  int i;
  for (i=0; i<10; i++)
  {
    book = GenerateBook();
    SimulateSortingBooks(book);
  }
}

// SHOPPING
struct Shopping * queueFirst=NULL;
struct Shopping * queueLast=NULL;
int nextRobotID=-1;
int Things_to_buy = 0;
struct Shopping
{
   int numberThingsToBuy; 
   int robot_id;
   struct Shopping *next;
};
struct Shopping * GenerateShopping()
{
	// reserve memory for a Shopping
	struct Shopping * shopping=malloc(sizeof(struct Shopping));
	// initialize the shopping's fields
	int n=rand()%5+1;
	shopping->numberThingsToBuy = n;
	nextRobotID++;
	shopping->robot_id=nextRobotID;
	return shopping;
}

// Global variable to get track of time / events
int Events_left = 0;

// function to print a list of robots in a shopping queue
void PrintShopping()
{
	int count = 1;
	struct Shopping *currentRobot = queueFirst;
	while (currentRobot != NULL)
	{
		printf("\nRobot %d -> Things to buy: %d, Robot_ID: %d\n", count, currentRobot->numberThingsToBuy, currentRobot->robot_id);
		currentRobot = currentRobot->next;
		count += 1;
	}
	printf("\n");
}

// function to add a robot to a shopping queue
void AddToQueue(struct Shopping * robot)
{
	// If queue is empty, create new queue
	if (queueFirst == NULL)
	{
		queueFirst = queueLast = robot;
		robot->next = NULL;
		return;
	}
	// If queue is not empty
	struct Shopping *currentRobot = queueFirst;
	while (currentRobot->next != NULL) // If the current is not the last
	{
		currentRobot = currentRobot->next;
	}
	robot->next = NULL;
	queueLast->next = robot;
	queueLast = robot;
	return;

}

// function to remove a robot from the queue and serve it
void Dequeue ()
{
	// If the queue is empty
	if (queueFirst == NULL)
	{
		printf("\nQueue is empty, nothing to remove.\n");
		return;
	}
	// If there is only one robot in the queue
	if (queueFirst->next == NULL) // If first == last
	{
		free(queueFirst);
		queueFirst = queueLast = NULL;
		return;
	}
	// If there is more than one robot in the queue
	struct Shopping *currentRobot = queueFirst;
	queueFirst = currentRobot->next;
	free(currentRobot);
	return;
}

// function to simulate the time the robot is in the queue
void UpdateShopping ()
{
	// NOT USED :)
}

// function to simulate a robot going for shopping
void SimulateGoForShopping(struct Shopping * robot)
{
	printf("\nRobot %d needs to pick up %d things from the store.\n", robot->robot_id, robot->numberThingsToBuy);
	AddToQueue(robot);

	// If the later robot finished shopping, it's turn for the first in queue
	if (Events_left == 0)
	{
		if (queueFirst == robot){
        	printf("How lucky! The line is empty! The robot will enter the supermarket now.\n");
		}
		else{
            printf("The supermarket is empty now, it's turn for the first robot in the queue to enter.\n");
		}
		Events_left = queueFirst->numberThingsToBuy;
		Dequeue();
	}
	// If the later robot didn't finish shopping but ours is first in line
	else if (queueFirst == robot){
        printf("How lucky! There is no one in line! However, I must wait my turn to enter the supermarket.\n");
	}
	// If the later robot didn't finish shopping and isn't the first in line
	else{
        printf("The robot gets in line. He finds his robot friends who also went shopping:\n");
		PrintShopping();
	}
	return;
}
int main()
{
  struct Shopping * shopping;
  shopping = GenerateShopping();
  SimulateGoForShopping(shopping);
  Things_to_buy-=1;
  shopping = GenerateShopping();
  AddToQueue(shopping);
    shopping = GenerateShopping();
    AddToQueue(shopping);
    Things_to_buy = 0;
    shopping = GenerateShopping();
  SimulateGoForShopping(shopping);
}

//PLATES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMBER_STACKS 3
#define MAX_CAPACITY 3
enum PlateType { dinner_plate=0, soup_plate=1, dessert_plate=2 };
enum Colors { white=0, green=1, yellow=2, beige=3 };
struct Plate * Top_ofPlateStacks[NUMBER_STACKS];
int CurrentState[NUMBER_STACKS];
struct Plate
{
   enum PlateType type;
   enum Colors color;
   struct Plate *next;
};
struct Plate * GeneratePlate()
{
	// reserve memory for a Plate
	struct Plate * plate=malloc(sizeof(struct Plate));
	// initialize the plate's fields
	enum PlateType type=rand()%3;
	enum Colors color=rand()%4;
	plate->type = type;
	plate->color = color;
	return plate;
}

// function to initialize all stacks of plates 
void InitStacks()
{
	int a;
	for (a = 0; a<3; a++)
	{
		Top_ofPlateStacks[a] = NULL;
	}
}

// General variables
int c_dinner = 0;
int c_soup = 0;
int c_dessert = 0;

// function to print all stacks of different plates
void PrintPlates()
{
	struct Plate * currentPlate0 = Top_ofPlateStacks[0];
	struct Plate * currentPlate1 = Top_ofPlateStacks[1];
	struct Plate * currentPlate2 = Top_ofPlateStacks[2];
	while (currentPlate0 != NULL)
	{
		printf("%c\n", currentPlate0->color);
		currentPlate0 = currentPlate0->next;
	}
	while (currentPlate1 != NULL)
	{
		printf("%c\n", currentPlate1->color);
		currentPlate1 = currentPlate1->next;
	}
	while (currentPlate2 != NULL)
	{
		printf("%c\n", currentPlate2->color);
		currentPlate2 = currentPlate2->next;
	}
	printf("\n");
}

// function to remove a given stack when its MAX_CAPACITY is reached
void RemoveStack()
{
	int countering = 0;
    struct Plate * current0 = Top_ofPlateStacks[0];
    struct Plate * current1 = Top_ofPlateStacks[1];
    struct Plate * current2 = Top_ofPlateStacks[2];
    if (c_dinner == MAX_CAPACITY)
    {
        int s;
        for (s=0;s<3;s++)
        {
          free(current0);
          current0=current0->next;
          countering +=1;
        }
        Top_ofPlateStacks[0] = NULL;
    }
    if (c_soup == MAX_CAPACITY)
    {
        int z;
        for (z=0;z<3;z++)
        {
          free(current1);
          current1=current1->next;
          countering+=1;
        }
        Top_ofPlateStacks[1] = NULL;
    }
    if (c_dessert == MAX_CAPACITY)
    {
        int h;
        for (h=0;h<3;h++)
        {
          free(current2);
          current2=current2->next;
          countering+=1;
        }
        Top_ofPlateStacks[2] = NULL;
    }
}

// function to simulate putting a generated plate to a corresponding stack 
void SimulateManagingPlate(struct Plate * plate)
{
	if (plate->type == 0)
	{
		if (Top_ofPlateStacks[0] ==NULL)
		{
			printf("\nThe stuck for dinner plates has not been initialize, let's begging\n");
			plate->next = NULL;
			Top_ofPlateStacks[0] = plate;
			c_dinner+=1;
			return;
		}
		else
		{
			printf("\nInsert at the top the new plate -dinner-\n");
			plate->next = Top_ofPlateStacks[0];
			Top_ofPlateStacks[0] = plate;
			c_dinner+=1;
			return;

		}
	}
	if (plate->type == 1)
	{
		if (Top_ofPlateStacks[1] ==NULL)
		{
			printf("\nThe stuck for soup plates has not been initialize, let's begging\n");
			plate->next = NULL;
			Top_ofPlateStacks[1] = plate;
			c_soup+=1;
			return;
		}
		else
		{
			printf("\nInsert at the top the new plate -soup-\n");
			plate->next = Top_ofPlateStacks[1];
			Top_ofPlateStacks[1] = plate;
			c_soup+=1;
			return;
		}
	}
	if (plate->type == 2)
	{
		if (Top_ofPlateStacks[2] ==NULL)
		{
			printf("\nThe stuck for dessert plates has not been initialize, let's begging\n");
			plate->next = NULL;
			Top_ofPlateStacks[2] = plate;
			c_dessert+=1;
			return;
		}
		else
		{
			printf("\nInsert at the top the new plate -dessert-\n");
			plate->next = Top_ofPlateStacks[2];
			Top_ofPlateStacks[2] = plate;
			c_dessert+=1;
			return;

		}
	}
}