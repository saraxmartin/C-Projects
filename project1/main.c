/*
Degree: Artificial Intelligence
Subject: Fundamentals of Programming 2
Practical project: 1

Simulator - main program
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "project1.h" // header with all data structures

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
		printf("There is some argument missing.\n");
		exit(1);
	}
	else if (argc>2)
	{
		printf("Too many arguments in the instruction.\n");
		exit(1);
	}
	else if (atoi(argv[1]) < 0)
	{
		printf("The argument can't be smaller than 0.\n");
		exit(1);
	}
	else if (atoi(argv[1]) == 0)
	{
		printf("The given argument is 0 or not a number.\n");
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

int c_books = 0;// General variable to count books

// function to print a list of books
void PrintBooks()
{
	struct Book * currentBook = booksHead;
	while (currentBook != NULL)
	{
		printf("  - %s, %s, %d\n", currentBook->title, currentBook->author, currentBook->year);
		currentBook = currentBook->next;
	}
}

// function to simulate a sorting of books
void SimulateSortingBooks(struct Book * book)
{
	// If the list of books is empty -> add our book as the first
    if (booksHead == NULL)
    {
        printf("The book %s is the only one on the shelf.\n", book->title);
        booksHead = book;
        book->next = NULL;
        c_books+=1;
        return;
    }

	// If the list is not empty -> find the right spot for our book
    struct Book * current = booksHead;
    struct Book * previous = NULL;
    char * book_author = book->author;
    while (current != NULL)
    {
        char * current_author = current->author; 
        int result = strcmp(book_author,current_author);
        
        if (result > 0) // Our book's author is >, continue searching
        {
            previous = current;
            current = current->next; 
        }
        else if (result <= 0) // Our book's author is < or the same, put before current
        {
            if (previous == NULL) // If current == booksHead
            {
                booksHead = book;
            }
            else // Book should be inserted between previous and current
            {
                previous->next = book;
            }
            book->next = current;
            printf("We have found the perfect place for our book!\n");
            c_books+=1;
            printf("This is how our shelf is looking for now:\n");
            PrintBooks();
            return;
        }  
    }
    // Book should be inserted at the end
    previous->next = book;
    book->next = NULL;
    printf("We have found the perfect place for our book!\n");
    c_books+=1;
    printf("This is how our shelf is looking for now:\n");
    PrintBooks();     
}

// function to remove a list of books at the end of the program
int RemoveSortingBooks()
{
	int count = 0; // Count for statistics

	// If there are no books in the list
	if (booksHead == NULL)
	{
		return count;
	}

	// If the list is not empty
	struct Book *current = booksHead;
	while (current!=NULL)
	{
		// If there is only one book in list
		if (current->next == NULL)
		{
			booksHead = NULL;
			free(current);
			count+=1;
			break;
		}
		else // If there is more than one book in the list
		{
			booksHead = current->next;
			free(current);
			current = booksHead;
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

// array to be able to print the type of plate and colour of plate
const char *PlateTypeStrings[] = {"dinner", "soup", "dessert"};
const char *PlateColourStrings[] = {"white", "green", "yellow", "beige"};

// function to print all stacks of different plates
void PrintPlates()
{
	int i;
	for (i=0; i<3; i++)
	{
		// For every stack we print the number of plates there is in a stack
		struct Plate * currentPlate = Top_ofPlateStacks[i];
		printf("  - Stack of %s plates:\n", PlateTypeStrings[i]);
		printf("     Number of %s plates: %d\n",PlateTypeStrings[i], CurrentState[i]);
		
		// If there is at least 1 plate in the stack, we print the colors too
		if (CurrentState[i] != 0)
		{
			printf("     Different colors of the plates:");
			while (currentPlate != NULL)
			{
				printf(" %s", PlateColourStrings[currentPlate->color]);
				if (currentPlate->next != NULL)
				{
					printf(",");
				}
				else{
					printf(".\n");
				}
				currentPlate = currentPlate->next;
			}
		}
		
	}
	
}

// function to remove a given stack when its MAX_CAPACITY is reached
void RemoveStack(int type)
{
  	struct Plate * current = Top_ofPlateStacks[type];
  	while (current!=NULL)
	{
      	Top_ofPlateStacks[type] = current->next;
      	free(current);
      	current = Top_ofPlateStacks[type];
    }
    CurrentState[type] = 0;
	printf("Stack of %s plates was cleaned, now there are 0 %s plates at the sink.\n", PlateTypeStrings[type], PlateTypeStrings[type]);

}

// function to simulate putting a generated plate to a corresponding stack 
void SimulateManagingPlate(struct Plate * plate)
{
	// If our stack is empty -> we add our plate as the first
    if (Top_ofPlateStacks[plate->type] == NULL)
    {
		printf("The %s plate is the first in the stack.\n", PlateTypeStrings[plate->type]);
    	plate->next = NULL;
    	Top_ofPlateStacks[plate->type] = plate;
    }
    else // If the stack is not empty -> we add our plate
    {
		printf("The plate is now on the pile at the sink, waiting to be cleaned.\n");
    	plate->next = Top_ofPlateStacks[plate->type];
    	Top_ofPlateStacks[plate->type] = plate;
    }
    CurrentState[plate->type]+=1; // Add +1 to count of plates
    
	//Check if there's need to remove plates from a stack
    if (CurrentState[plate->type] == MAX_CAPACITY)
    {
    	RemoveStack(plate->type);
    }
	// Show how stacks of plates are at the moment
	printf("This is how our sink is looking now:\n");
	PrintPlates();
}

// function to clean all stacks before the end of the program
int CleanPlateStacks()
{
	// Save variable of total amount of plates for statistics
    int totalPlates = CurrentState[0] + CurrentState[1] + CurrentState[2];

	// Clean every stack one by one
    while(CurrentState[0] != 0)
    {
        struct Plate *temp = Top_ofPlateStacks[0];
        CurrentState[0]-=1;
        Top_ofPlateStacks[0]= temp->next;
        free(temp);
    }
    while(CurrentState[1] != 0)
    {
        struct Plate *temp = Top_ofPlateStacks[1];
        CurrentState[1]-=1;
        Top_ofPlateStacks[1]= temp->next;
        free(temp);
    }
    while(CurrentState[2] != 0)
    {
        struct Plate *temp = Top_ofPlateStacks[2];
        CurrentState[2]-=1;
        Top_ofPlateStacks[2]= temp->next;
        free(temp);
    }
	return totalPlates;
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
	struct Shopping *currentRobot = queueFirst;
	while (currentRobot != NULL)
	{
		printf("  - Robot ID: %d -> Things to buy: %d\n",currentRobot->robot_id, currentRobot->numberThingsToBuy);
		currentRobot = currentRobot->next;
	}
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
		printf("\nThe queue is empty, there are no robots to enter the supermarket.\n");
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

// function to simulate a robot going for shopping
void SimulateGoForShopping(struct Shopping * robot)
{
	printf("\nRobot %d needs to pick up %d things from the store.\n", robot->robot_id, robot->numberThingsToBuy);
	AddToQueue(robot);

	// If the later robot finished shopping, it's turn for the first in queue
	if (Events_left == 0)
	{
		// If the first in queue is our robot -> line is empty -> it can enter supermarket
		if (queueFirst == robot){
        	printf("How lucky! The line is empty! The robot will enter the supermarket now.\n");
		}
		// If the our robot is not the first -> first robot will enter supermarket
		else{
            printf("The supermarket is empty now, it's turn for the first robot in the queue to enter.\n");
		}
		Events_left = queueFirst->numberThingsToBuy;
		Dequeue();
	}
	// If the later robot didn't finish shopping but ours is first in line
	else if (queueFirst == robot){
        printf("The robot is first in line, however, it must wait for its turn to enter the supermarket.\n");
	}
	// If the later robot didn't finish shopping and isn't the first in line
	else{
        printf("The robot gets in line and he finds his robot friends who also went shopping:\n");
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
	int skip = 0;
	struct Book *book;
	struct Plate *plate;
	struct Shopping *robot;
	struct Shopping * robot_shopping = NULL; // pointer to robot shopping at the moment

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
			book = GenerateBook();
			printf("\nA new book was bought, let's put it in our bookshelf.\n");
			// Simulate sorting books
			SimulateSortingBooks(book);
		}
		// event type 1:
		if (Event_Number == 1)
		{
			// generate plate
			plate = GeneratePlate();
			printf("\nSomeone used a %s plate, let's stack it at the sink.\n", PlateTypeStrings[plate->type]);
			// Simulate managing plate
			SimulateManagingPlate(plate);
		}
		// event type 2:
		if (Event_Number == 2)
		{
			// generate shopping
			robot = GenerateShopping();
			printf("\nRobot %d was generated.", robot->robot_id);
			if (Events_left == 0) // If shopping of later robot is over, we won't count the new robot that goes shopping as an event
			{
				skip = 1;
			}
			// Simulate shopping
			SimulateGoForShopping(robot);
		}

		// Update shopping
		if (Events_left != 0 && skip == 0) // If there is a robot shopping
		{
			Events_left -=1;
			printf("\nRobot shopping has now %d items left to buy.\n",Events_left);
			if (Events_left == 0)  // If robot shopping has finished
			{
				printf("Robot finished shopping.\n");
				if (queueFirst != NULL)  // If there is a robot in the queue, it enters the supermarket
				{
					Events_left = queueFirst->numberThingsToBuy;
					printf("Robot %d will now enter the supermarket.\n", queueFirst->robot_id);
					Dequeue();
				}
			}
		}
		skip = 0;

	}
			
	// CLEANING THE SIMULATION
	count_books = RemoveSortingBooks();
	count_plates = CleanPlateStacks();
	count_robots = CleanShoppingQueue();

	// Print statistics
	printf("\nprogram %d\n", EventNumbers);
	printf("\nSTATISTICS WHEN CLEANING THE SIMULATION:\n");
	printf("\nRemoving books...\n    %d books have been removed.", count_books);
	printf("\nCleaning all stacks of plates...\n    %d plates have been removed.",count_plates);
	printf("\nCleaning shopping queue...\n    %d robots have been removed.", count_robots);
}

int main (int argc, char ** argv)
{
	int EventNumbers;

	// Check if the arguments are valid
	CheckArguments(argc, argv);

	    // If so, we start the simulation
	printf ("Starting... \n");
	// initialize EventNumbers 
	EventNumbers = atoi(argv[1]);

	SimulationLoop(EventNumbers);
	
	return 0;
}