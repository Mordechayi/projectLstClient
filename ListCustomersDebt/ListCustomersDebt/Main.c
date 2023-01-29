#include "Prompt.h"


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    FILE* fp = NULL;//points to a file to read and write
	List list = createNewList();//Creating a new list and initializing the list
	char* nameFile = "customers2.csv";
	char* newFile = nameFile;//String to receive the new name of the file
	openFile(&fp, "r+", &newFile);//a file is opened for reading and writing - the program does not continue until a file is opened
	readFileAndCreateList(fp, &list);//Creates a linked list from the file
	printList(list);//Prints the entire list
	closeFile(fp);//Closes the file and checks that it closes properly
	prompt(list, &fp, &newFile);//Receives instructions/commands from the user
	freeList(&list);//Frees the memory allocation of all structures in the list
	if(newFile != nameFile)
	    free(&newFile);

	return 0;
}
