#include "HeaderProject.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	char* day, * month, * year, * debt;
	FILE* fp = NULL;//points to a file to read and write
	char str[] = ""; //a string to save a line on each call from the file
	List list = createNewList();//Creating a new list and initializing the list
	char* newFile = "customer.csv";;//String to receive the new name of the file
	fp = openFile(&fp, "r+", &newFile);//a file is opened for reading and writing - the program does not continue until a file is opened
	list = readFileAndCreateList(fp, str, list,&day,&month,&year,&debt);//Creates a linked list from the file
	printList(list);//Prints the entire list
	closeFile(fp);//Closes the file and checks that it closes properly
	frompt(list, fp, newFile);//Receives instructions/commands from the user
	freeList(&list);//Frees the memory allocation of all structures in the list

	return 0;
}
