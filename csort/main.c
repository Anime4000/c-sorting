#include <stdio.h>
#include <stdlib.h>

struct node
{
	int id;
	int data;
	struct node *next;
};

int countSum(struct node *start);
void printList(struct node *start);

void insertAtTheBegin(struct node **start_ref, int id, int data);

void bubbleSort(struct node *start);
void selectionSort(struct node *start);
void insertionSort(struct node *start);
void swap(struct node *x, struct node *y);

void pressAnyKey();

// use int main() not void main(), don't hurt Operating System,
// OS need to know state of running program which is return 0 (OK) or else (Crash)
// Every OS always log running program, so use int main() { return 0; }
int main()
{
	// Ready data without prompt user input
	int dsId[5] = {
		101,
		221,
		98,
		3,
		186
	}; // Dropship Id

	int ds1[5] = {
		12800,
		11300,
		17765,
		21600,
		8900
	}; // Febuary

	int ds2[5] = {
		17765,
		14600,
		8900,
		15670,
		5560
	}; // March

	int ds3[5] = {
		8900,
		15670,
		12800,
		11300,
		10760
	}; // April

	while (1)
	{
		// start with empty linked list
		struct node *start = NULL;

		// automatically fill data into Linked List
		for (int i = 0; i < 5; i++)
			insertAtTheBegin(&start, dsId[i], ds1[i] + ds2[i] + ds3[i]);
		//                                    \______________________/
		//                                      Feb + March + April
		//                                        directly add to
		//                                          linked list

		// print list before sorting
		puts("Dropship ID\tSales (Total)");
		printList(start);

		printf("\nTotal:\t\tRM %d\n", countSum(start));

		puts("\n\nSorting\n"
			"1. Bubble Sort\n"
			"2. Selection Sort\n"
			"3. Insertion Sort\n"
			"4. Exit");

		printf("Enter choice: ");

		int select;
		scanf("%i", &select);
		getchar(); // bug preventer, scanf() is stupid and old function, now using C99 standards

		if (select == 4)
		{
			puts("Bye Bye. Press any key to quit.");
			getchar();
			return 0;
		}

		printf("\n\n");

		switch (select)
		{
		case 1:
			bubbleSort(start);
			puts("Bubble Sort\nDropship ID\tSales (Total)");
			break;

		case 2:
			selectionSort(start);
			puts("Selection Sort\nDropship ID\tSales (Total)");
			break;

		case 3:
			puts("Insertion Sort\nDropship ID\tSales (Total)");
			insertionSort(start);
			break;

		default:
			break;
		}

		// print list after sorting 
		printList(start);

		// pause
		pressAnyKey();
	}

	return 1; // loop error, tell OS this program was a problem
}

// Function to count total value
int countSum(struct node *start)
{
	struct node *temp = start;
	int sum = 0;

	while (temp != NULL)
	{
		sum += temp->data;
		temp = temp->next;
	}

	return sum;
}

// Function to print nodes in a given linked list
void printList(struct node *start)
{
	struct node *temp = start;

	while (temp != NULL)
	{
		printf("DC%03d\t\tRM %5d\n", temp->id, temp->data);

		temp = temp->next;
	}
}

// Function to insert a node at the begining of a linked lsit
void insertAtTheBegin(struct node **start_ref, int id, int data)
{
	struct node *ptr1 = (struct node*)malloc(sizeof(struct node));

	ptr1->id = id;
	ptr1->data = data;

	ptr1->next = *start_ref;
	*start_ref = ptr1;
}

// Bubble sort the given linked list 
void bubbleSort(struct node *start)
{
	int swapped, i;
	struct node *ptr1;
	struct node *lptr = NULL;

	do
	{
		swapped = 0;
		ptr1 = start;

		// Checking for empty list 
		if (ptr1 == NULL)
			return;

		while (ptr1->next != lptr)
		{
			/*             |-- change this > (low to high) or < (high to low) */
			if (ptr1->data > ptr1->next->data)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);
}

// Selection sort the given linked list 
void selectionSort(struct node *start)
{
	struct node *traverse;
	struct node *min;

	while (start->next)
	{
		min = start;
		traverse = start->next;

		while (traverse)
		{
			/* Find minimum element from array 
			              |--- change this > (low to high) or < (high to low) */
			if (min->data > traverse->data)
			{
				min = traverse;
			}

			traverse = traverse->next;
		}
		swap(start, min);			// Put minimum element on starting location
		start = start->next;
	}
}

// Insertion sort the given linked list 
void insertionSort(struct node *start)
{
	if (start == 0)
		return;

	// unsorted list - from the 2nd element
	struct node *unsorted = start->next;

	while (unsorted != 0)
	{
		// take key as an element in the unsorted list.
		struct node *prev = 0;
		struct node *iter = start;
		struct node *key = unsorted;

		// iterate within the sorted list and find the position
		while (iter != 0)
		{
			if (iter->data < key->data)
			{
				prev = iter;
				iter = iter->next;
			}
			else
				break;
		}
		unsorted = unsorted->next;

		// if reached the end of sorted list 
		if (iter == key)
			continue;

		// note down the position to replace in a sorted list
		struct node *replace = iter;

		//move iter to end of the sorted list 
		while (iter->next != key)
			iter = iter->next;

		// link to the upsorted list
		iter->next = unsorted;

		// delete the key and replace it in sorted list
		if (prev == 0)
		{
			start = key;
		}
		else
		{
			prev->next = key;
		}
		key->next = replace;

		// printList(start); // display how it arrange
	}
}

/* function to swap data of two nodes a and b*/
void swap(struct node *a, struct node *b)
{
	int tmpId = a->id;
	a->id = b->id;
	b->id = tmpId;

	int tmpData = a->data;
	a->data = b->data;
	b->data = tmpData;
}

void pressAnyKey()
{
	printf("Press any key to continue...\n");
	getchar();
}