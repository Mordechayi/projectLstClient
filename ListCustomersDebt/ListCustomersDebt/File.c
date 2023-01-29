#include "File.h"

void openFile(FILE** fp, char* mode, char** newFile)
{
	while (!((*fp) = fopen(*newFile, mode)))//if not correct gets a new file name if correct continues on
	{
		putchar('\n');
		printf("the file did not open!\n\n>>>>please enter the file name again->\n\n");
		readFileAndStdinWithMemoryAllocation(stdin,newFile);
		
		//*newFile = readStdin();//The function receives a string from the user and allocates memory according to the length of the lines
	}
}
void readFileAndStdinWithMemoryAllocation(FILE* fp, char** str1)
{
	char str[200];
	char* input = NULL,* tmp = NULL;
	char tempbuf[CHUNK];//An array of size 10 to receive the row in parts
	size_t inputlen = 0, templen = 0;
	if (fgets(str, 200, fp))//If there is content in the file, reads up to the end of the line or up to 200 characters
	{
		if (!(input = _strdup(str)))
		    return;
		if (strlen(str) == 199 && str[198] != '\n' && (fgets(tempbuf, 10, fp)))
		{
			inputlen += strlen(str);
			do {
				templen = strlen(tempbuf);//Gets the number of characters received from the file
				if (!(tmp = realloc(input, inputlen + templen + 1)))//Allocates it space according to the number of characters received in the current and previous reading
				{
					printf("allocation failed!");
					return;
                }
				input = tmp;
				strcpy(input + inputlen, tempbuf);//Copies the characters in the array
				inputlen += templen;//and increments the character counter
			} while (templen == CHUNK - 1 && tempbuf[CHUNK - 2] != '\n' && fgets(tempbuf, CHUNK, fp));
		}
	}
	if (input && input[strlen(input) - 1] == '\n')//removing \n from the end of the string
		input[strlen(input) - 1] = '\0';
	*str1 = input;
	input = NULL;
}
void closeFile(FILE* fp)
{
	if ((fclose(fp)) != 0)
		printf("ERROR in fclose()");
}
void printToFile(FILE* fp, Client* temp, float tempDebt)
{

	if (!(fprintf(fp, "%s,%s,%s,%s,%.2f,%d/%d/%d", temp->firstName, temp->lastName, temp->id, temp->phone, tempDebt, temp->date.day, temp->date.month, temp->date.year)))
		puts("error in the fprintf - to print in to the file");
}
