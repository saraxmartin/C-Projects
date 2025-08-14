/*
Degree: Artificial Intelligence
Subject: Fundamentals of Programming 2
Practical project: 1

project1.h
Header of all necessary data structures required by the project 1.
It also contains enumeration types and additional variables, 
arrays for managing data structures and their initial values
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum EventType { book=0, plate=1, shopping=2 };

//--------------------------------------------------------------------------Books
// predefined authors of books; there are 8 books
char authors[8][20]={{"Philip Roth"}, {"Dan Brown"}, {"Charlotte Bronte"}, {"Stephenie Meyer"},{"Katarzyna Grochola"}, {"J.K. Rowling"}, {"Veronica Roth"}, {"Yann Martel"}};

// predefined titles of books; there are 8 books
char titles[8][20]={{"Nemesis"}, {"Origin"}, {"Jane Eyre"}, {"The host"},{"Zielone drzwi"}, {"Harry Potter"}, {"Divergente"}, {"Life of Pi"}};

// a pointer to the head of the book list
struct Book * booksHead=NULL;

struct Book
{
	char author[20];
	char title[20];
	int year; 
   struct Book *next;
};

//--------------------------------------------------------------------------Plates

#define NUMBER_STACKS 3
#define MAX_CAPACITY 3

enum PlateType { dinner_plate=0, soup_plate=1, dessert_plate=2 };
enum Colors { white=0, green=1, yellow=2, beige=3 };

// There are 3 different stacks, each one for each type of plate
// Here we create a static array to have 3 pointers to a top element of each stack
struct Plate * Top_ofPlateStacks[NUMBER_STACKS];

// Each stack has a current number of plates
// At the beginning each stack has 0 plates
// Here we create a static array where we will store a number of plates for each stack
// We assume here that the capacity of each stack is MAX_CAPACITY (which is 3)
int CurrentState[NUMBER_STACKS];

struct Plate
{
   enum PlateType type;
   enum Colors color;
   struct Plate *next;
};

//--------------------------------------------------------------------------Shopping

// a pointer to the first element of the shopping list
struct Shopping * queueFirst=NULL;
// a pointer to the last element of the shopping list
struct Shopping * queueLast=NULL;

// global variable that is used for assigning a next identifier 
// when a next robot is generated
int nextRobotID=-1;

struct Shopping
{
   int numberThingsToBuy; 
   int robot_id;
   struct Shopping *next;
};

/*
Degree: Artificial Intelligence
Subject: Fundamentals of Programming 2
Practical project: 1

Simulator - main program
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//----------------------------------------------------------General
// WARNING: do not change this function
enum EventType GenerateEventType()
{
	return rand()%3;
}

void CheckArguments (int argc, char ** argv)
{
	if (argc<2)
	{
		printf("There are some argument missing\n");
		exit(1);
	}
	else if (argc>2)
	{
		printf("Too many arguments in the instruction\n");
		exit(1);
	}
	else if (atoi(argv[1])== 0)
	{
		printf("The given argument is 0 or not a number\n");
		exit(1);
	}
}

//----------------------------------------------------------Books
// WARNING: do not change this function
struct Book * GenerateBook()
{
	// reserve memory for a book
	struct Book * book=malloc(sizeof(struct Book));
	int bookNum=rand()%8;
	// initialize the book's fields
	strcpy (book->author, authors[bookNum]);
	strcpy (book->title, titles[bookNum]);
	int year=rand()%40+1980;
	book->year=year;
	return book;
}

// function to print a list of books
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

// function to search for a book
struct Book * SearchBook(char *author, char *title, int *year)
{
	if (booksHead == NULL) // If list is empty
		return NULL;

	struct Book *currentBook = booksHead;
	while (currentBook->next != NULL)
	{
		if (currentBook->title == title) // Compare title
			return currentBook;
		else currentBook = currentBook->next;
	}
	return currentBook; // not found or NULL

}

// function to simulate a sorting of books
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

// function to remove a list of books at the end of the program
int RemoveSortingBooks()
{
	struct Book *current = booksHead;
	int count = 0;
	while (current!=NULL)
	{
		// If there is only one book in list
		if (booksHead->next == NULL)
		{
			free(booksHead);
			booksHead = NULL;
		}
		else
		{
			booksHead = current->next;
			free(current);
		}
		count+=1;
	}
	return count;
}

//----------------------------------------------------------Stack
// WARNING: do not change this function
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

// function to clean all stacks before the end of the program
int CleanPlateStacks()
{
	printf("\nClean stacks of plates...\n");
    int totalPlates;
    totalPlates = c_dinner;
    totalPlates= totalPlates + c_soup;
    totalPlates = totalPlates + c_dessert;
	int count_total_plates = totalPlates;
    printf("\n%d plates have been removed\n",totalPlates);
    while(c_dinner>0)
    {
        struct Plate *temp = Top_ofPlateStacks[0];
        c_dinner-=1;
        Top_ofPlateStacks[0]= temp->next;
        free(temp);
    }
    while(c_soup>0)
    {
        struct Plate *temp = Top_ofPlateStacks[1];
        c_soup-=1;
        Top_ofPlateStacks[1]= temp->next;
        free(temp);
    }
    while(c_dessert>0)
    {
        struct Plate *temp = Top_ofPlateStacks[2];
        c_dessert-=1;
        Top_ofPlateStacks[2]= temp->next;
        free(temp);
    }
	return count_total_plates;
}


//----------------------------------------------------------Shopping
// WARNING: do not change this function
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
	int count = 0;
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
	printf("\nRobot %d needs to pick up %d things from the store...\n", robot->robot_id, robot->numberThingsToBuy);
	AddToQueue(robot);

	// If the later robot finished shopping, it's turn for the first in queue
	if (Events_left == 0)
	{
		if (queueFirst == robot){
        	printf("\nHow lucky! The line is empty! The robot will enter the supermarket now...\n");
		}
		else{
            printf("\nThe supermarket is empty now, it's turn for the first robot in the queue to enter\n");
		}
		Events_left = queueFirst->numberThingsToBuy;
		Dequeue();
	}
	// If the later robot didn't finish shopping but ours is first in line
	else if (queueFirst == robot){
        printf("\nHow lucky! There is no one in line! However, I must wait my turn to enter the supermarket...\n");
	}
	// If the later robot didn't finish shopping and isn't the first in line
	else{
        printf("\nThe robot gets in line. He finds his robot friends who also went shopping:\n");
		PrintShopping();
	}
	return;
}

// function to clean shopping queue before the end of the program
int CleanShoppingQueue()
{
	int count = 0;
	while (queueFirst != NULL)
	{
		if (queueFirst->next == NULL)
		{
			free(queueFirst);
			queueFirst = queueLast = NULL;
		}
		else
		{
			struct Shopping *currentRobot = queueFirst;
			queueFirst = currentRobot->next;
			free(currentRobot);
		}
		count+=1;
	}
	return count;
}

//----------------------------------------------------------main
// Global variables
int count_books, count_plates, count_robots;

// This is the main loop of the program. 
// It generates and consumes events.
void SimulationLoop(int EventNumbers)
{
	// declare and initialize necessary variables
	int Event_Number;
	int count_books, count_plates, count_robots;
	bool Skip = false;
	struct Book *book;
	struct Plate *plate;
	struct Shopping *robot;
	struct Shopping * robot_shopping = NULL;

	InitStacks();
	
	for (int i=0; i<EventNumbers; i++)    
	{
		// generate event type
		Event_Number = GenerateEventType();
		// depending on the generated event type:
		// event type 0: 
		if (Event_Number == 0)
		{
			// generate book
			printf("\nGenerating a new book...\n");
			book = GenerateBook();
			// Simulate sorting books
			printf("Sorting books...\n");
			SimulateSortingBooks(book);
		}
		// event type 1:
		if (Event_Number == 1)
		{
			// generate plate
			printf("\nGenerating a new plate...\n");
			plate = GeneratePlate();
			// Simulate managing plate
			printf("Managing plates...\n");
			SimulateManagingPlate(plate);
		}
		// event type 2:
		if (Event_Number == 2)
		{
			// generate shopping
			printf("\nGenerating a new robot...");
			robot = GenerateShopping();
			// If shopping of later robot is over, we won't count the
			// new robot that goes shopping as an event
			if (Events_left == 0){
				Skip = true;
				robot_shopping = robot;
			}
			else{
				Skip = false;
			}
			// Simulate shopping
			printf("Going for shopping...\n");
			SimulateGoForShopping(robot);
		}

		if (Events_left != 0 && Skip == false){
				Events_left -=1;
		}
		// Update shopping
		if (robot_shopping != NULL)
		{
			printf("\nRobot %d has now %d items left to buy.\n", robot_shopping->robot_id, Events_left);
		}
		
	}
	// CLEANING THE SIMULATION
	count_books = RemoveSortingBooks();
	count_plates = CleanPlateStacks();
	count_robots = CleanShoppingQueue();

}

int main (int argc, char ** argv)
{
	int EventNumbers;
	printf ("Starting... \n");
	CheckArguments(argc, argv);
	
	// initialize EventNumbers 
	EventNumbers = atoi(argv[1]);

	SimulationLoop(EventNumbers);

	// Print statistics
	printf("\nprogram %d\n", argc);
	printf("\nSTATISTICS WHEN CLEANING THE SIMULATION:\n");
	printf("\nRemoving books...\n    %d books have been removed.", count_books);
	printf("\nCleaning all stacks of plates...\n    %d plates have been removed.",count_plates);
	printf("\nCleaning shopping queue...\n    %d robots have been removed.", count_robots);
	
	return 0;
}