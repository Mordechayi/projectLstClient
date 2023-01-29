#include "List.h"

List createNewList()
{
	List list = { NULL };//initializes the list
	return list;
}
void readFileAndCreateList(FILE* fp, PList list)
{
	char* str = NULL;
	do {
		readFileAndStdinWithMemoryAllocation(fp, &str);//reads from the file and allocates memory according to the length of the lines
		if (str) {
			createsASortedList(list, str);//Creates a node and puts it in a sorted list
			free(str);//Frees the memory allocation of str
		}
	} while (str);

}
void freeList(PList list)
{
	Client* ptr = list->head;
	Client* temp = ptr ;
	while (ptr)
	{
		temp = temp->next;
		freeClient(ptr);
		free(ptr);
		ptr = temp;
	}
	ptr = NULL;
}
void freeClient(Client* ptr)
{
	free(ptr->firstName);
	free(ptr->lastName);
	free(ptr->id);
	free(ptr->phone);
	free(ptr->errorStr.dayErrStr);
	free(ptr->errorStr.monthErrStr);
	free(ptr->errorStr.YearErrStr);
	free(ptr->errorStr.debtErrStr);
}
Client* initializationClient()
{
	Client* client;
	//gets Allocates memory of struct size and resets it all and checks that the allocation is correct
	if (!(client = (Client*)calloc(1, sizeof(Client))))
	{
		printf("memory allocation failed!");
		return NULL;
	}
	return client;
}
void createsASortedList(PList list, char* str)
{
	Client* temp = NULL;
	createClient(list, str, &temp);// Creates a new struct and returns a new pointer
	if (temp)
	{
		checkIdClient(list, temp);//Checking if there is already a debt in his name - and the debt scheme
		addToSortedList(list, temp);
	}
}
void addToSortedList(PList list, Client* temp)
{
	Client* prev = list->head;
	if (temp == NULL)
		return;
	if (list->head == NULL)//If the list is empty
	{
		list->head = temp;//The top of the list is worth renewing
		if (temp->next)
			list->head->next = temp->next;
		return;
	}
	if (list->head->debt <= temp->debt)
	{
		temp->next = list->head;
		list->head = temp;
		return;
	}
	while (prev->next && prev->next->debt > temp->debt)//as long as the debt is large, advance to the next strat
		prev = prev->next;
	temp->next = prev->next;//Income to the middle of the list
	prev->next = temp;
}
Error initializationError()
{
	Error err = { NULL,NULL,NULL,NULL };//Initializes the list
	return err;
}
void createClient(PList list, char* str, PClient* client)
{
	char* token = NULL;//saves the string that will be divided into sections
	int flag = 0, tempToken = 0;
	Client* temp;
	if (!(temp = initializationClient()))//new Client restart
		return;
	temp->errorStr = initializationError();//Initializes the error struct
	if (str != NULL)
		toLower(str);//Accepts a string and converts uppercase to lowercase
	void(*PoinersToFuncCheck[8])(Client*, char*) = { checkFirstName,checkLastName,checkId,checkPhone,checkDebt,checkDay,checkMonth,checkYear };
	for (int i = 0, j = 1; i < 8; i++)//check if all the values are vallid
	{
		if (i == 0 || (token && (token[strlen(token) + j] != ','))) {//check if one or more of the values in the file are null
			if (i == 0) {
				token = strtok(str, ",");
				if (!token) //if  all the values in the fields ar empty with out ','
					return;
				tempToken = 2;
				/* check if the first entries or more is NLLL */
				while (str &&(*(token - tempToken) == ',' || ((str[-1] && *(token - tempToken) == str[-1] && tempToken != 2) ||
					(*(token - 1) == ',' && *(token - tempToken) == str[-1])))) {
					if (i == 4) // if There are no entries until the date
						token = strtok(str + 5, "/");
					PoinersToFuncCheck[i](temp, NULL); //updates in the struct
					tempToken++;//to check one before him
					i++;
					if ((*(token - tempToken + 1) == str[-1] && tempToken != 2))//check if the  first entries is NLLL
						break;
				}
			}
			else if (token && (i < 5 || i == 7))
				token = strtok(NULL, ",");
			else if (token && i < 7) //to divide the date to day,month
				token = strtok(NULL, "/");
			PoinersToFuncCheck[i](temp, token);
			j = 1;
		}
		else {
			PoinersToFuncCheck[i](temp, NULL);
			j++;
		}
	}
	temp->next = NULL;// Unless otherwise specified the next is NULL  
	*client = temp;
}
void checkDate(Client* temp, Client* ptr)
{
	/*Save the later date in temp*/
	if (ptr->date.year < temp->date.year || ((ptr->date.year) == ((temp->date.year)) && ((ptr->date.month) < (temp->date.month))) ||
		(((temp->date.year) == (ptr->date.year)) && ((temp->date.month) == (ptr->date.month)) && ((ptr->date.day) < (temp->date.day))))
		return;
	else
		temp->date = ptr->date;

}
void sameId(Client* temp, PList list, char* token)
{
	if (list == NULL || token == NULL)
		return;
	Client* prev = list->head;
	Client* ptr = list->head;
	while (ptr)
	{
		if ((sumSameId(list, &temp, &ptr, &prev) == -1))
			return;
			if (sameIdAndDifName(temp))
				return;
			if (ptr != prev)
				prev = prev->next;
			ptr = ptr->next;
	}
}
int sumSameId(PList list, Client** temp, Client** ptr, Client** prev)
{
	if (((*temp)->id != NULL) && ((*ptr)->id != NULL) && strcmp((*ptr)->id, (*temp)->id) == 0 && (!GetBitError(((*ptr)->error), errGeneral)))//If the id Their is the same as concluded and returns the new date
	{
		if (((*ptr)->firstName != NULL) && (strcmp((*ptr)->firstName, (*temp)->firstName) == 0)
			&& ((*ptr)->lastName != NULL) && (strcmp((*ptr)->lastName, (*temp)->lastName) == 0) && (!GetBitError(((*ptr)->error), errGeneral)))//If the names are the same and there is no error
		{
			(*temp)->debt += (*ptr)->debt;//Schema and providing the value within the already existing customer
			checkDate(*temp, *ptr);//Checking the latest date among them
			if ((*ptr) == (*prev))//If the cell worth renewing is the new cell 
			{
				if (list->head->next == NULL) {//If the only one on the list
					list->head = (*ptr)->next = NULL;
				}
				else if (list->head == (*ptr))
					list->head = list->head->next;
				else
					//(*prev)->next = (*temp);
					(*prev)->next = (*ptr)->next;//links it to the next one in the list
				freeClient(*ptr);
				free((*ptr));//Deletes the current one
			}
			else
			{
				if (list->head == (*ptr))
					list->head = (*ptr)->next;
				else
					(*prev)->next = (*ptr)->next;//links it to the next one in the list
				freeClient(*ptr);
				free((*ptr));//Deletes the current one
			}
			return -1;
		}
		else if (!((*temp)->error << diffName) && !((*ptr)->error << diffName))//If there are no errors in the node
		{
			if ((*ptr)->firstName == NULL || (*ptr)->lastName == NULL)
				return 1;
			if ((strcmp((*ptr)->firstName, (*temp)->firstName) != 0) || (strcmp((*ptr)->lastName, (*temp)->lastName) != 0))
			{
				SetBitError((&((*temp)->error)), diffName);
				SetBitError((&((*temp)->error)), errGeneral);

			}
		}
	}
	return 0;
}
void printClient(Client* client, int i)//Printing one customer from the list
{
	printf("    |   |                |                |                |                |                |                |\n");
	printf("    |%2d.%-4s%-13.10s%-4s%-13.10s%-4s%-13.10s%-4s%-13.10s%-4s%02d/%02d/%04d   %-0s%12.2f%5s\n", i, "|", client->firstName,
		"|", client->lastName, "|", client->id, "|", client->phone, "|", client->date.day, client->date.month, client->date.year, "|", client->debt, "|");
	printf("    |___|________________|________________|________________|________________|________________|________________| \n");
}
void printClientErr(Client* client, int  i)//Printing one customer with errors from the list
{

	printf("    |   |                |                |                |                |                |                |\n");
	printf("    |%2d.%-4s%-13.10s%-4s%-13.10s%-4s%-13.10s%-4s%-13.10s", i, "|", client->firstName, "|", client->lastName, "|", client->id, "|", client->phone);//Prints the fields that are saved as strings
	//prints the fields that are saved as a number, if they are correct prints as a number, otherwise prints the strings in which the errors were saved
	(GetBitError(client->error, errDay)) ? printf("%-3s%02.3s%0.1s/", "|", client->errorStr.dayErrStr, "") : printf("%-4s%02d/", "|", client->date.day);
	(GetBitError(client->error, errMonth)) ? printf("%02.2s%0.1s/", client->errorStr.monthErrStr, "") : printf("%02d/", client->date.month);
	(GetBitError(client->error, errYear)) ? printf("%4.4s%3s", client->errorStr.YearErrStr, "") : printf("%04d%3s", client->date.year, "");
	(GetBitError(client->error, errDebt)) ? printf("%-0s%12.8s%5s\n", "|", client->errorStr.debtErrStr, "|") : printf("%-0s%15.2f%2s\n", "|", client->debt, "|");

	printf("    |___|________________|________________|________________|________________|________________|________________| \n");
}
void printList(List list)//print the list
{
	int i = 1, wasATitel = 0;
	Client* ptr = list.head;//Pointer to the beginning of the list
	while (ptr)
	{
		if (!GetBitError(ptr->error, errGeneral)) {//clients without errors
			if (!wasATitel)
			{
				printTitles("     LIST OF CLIENTS DEBT");
				wasATitel = 1;
			}
			if (ptr->debt < -9999999) ptr->debt = -9999999;// Limits the amount of the debt, so that it does not go off the table
			else if (ptr->debt > 0)  ptr->debt = 0; //Prints only debts and not a balance
			printClient(ptr, i++);
		}
		ptr = ptr->next;//Promotion by one node until the end of the list is reached
	}
	ptr = list.head;//Resets the pointer to the beginning of the list
	i = 1;//Resets the list numbers
	wasATitel = 0; //Resets the flag
	while (ptr)//clients with errors
	{
		if (GetBitError(ptr->error, errGeneral))//clients with errors
		{
			if (wasATitel == 0)
				printTitlesErr(&wasATitel);//one-time use - for a table header
			if (ptr->debt < -9999999) ptr->debt = -9999999;// Limits the amount of the debt, so that it does not go off the table
			else if (ptr->debt > 0)  ptr->debt = 0; //Prints only debts and not a balance
			printClientErr(ptr, i++);//prints the client with error
			errorToPrint(ptr);// prints where the error is
			printf("\n    |___|________________|________________|________________|________________|________________|________________| \n");
		}
		ptr = ptr->next;//Promotion by one node until the end of the list is reached
	}
}
void printTitles(char* str)//one-time use - for a table header
{
	printf("\n                                            %s \n", str);//title
	printf("    ___________________________________________________________________________________________________________\n");
	printf("    |   |                |                |                |                |                |                |\n");
	printf("    |   |   first name   |   last name    |       id       |     phone      |     date       |      debt      |\n");
	printf("    |___|________________|________________|________________|________________|________________|________________| \n");
}
void printTitlesErr(int* wasATitel)//one-time use - for a table header
{
	*wasATitel = 1;
	printf("\n\n\n\n\n\n                                        LIST OF CLIENTS DEBT - WITH ERRORS \n");//title
	printf("    ___________________________________________________________________________________________________________\n");
	printf("    |   |                |                |                |                |                |                |\n");
	printf("    |   |   first name   |   last name    |       id       |     phone      |     date       |      debt      |\n");
	printf("    |___|________________|________________|________________|________________|________________|________________| \n");
}
void errorToPrint(Client* temp)//prints where the error is
{
	char* c1 = (char*)malloc(17 * sizeof(char));
    if (!temp)
		return;
	uint16_t mask = 1;
	printf("    |   |");
	for (int i = errFirstName; i <= errDebt; i++)//go through the error types
	{
		if (i == errId && (temp->error & mask << diffName)) {
			c1 = strcpy(c1, "same ID-dif name");
			printf("%s|", c1);
			i++;
		}
		if (temp->error & mask << i)
			c1 = strcpy(c1,"ERROR");
		else
			c1 = strcpy(c1,"VALID");
		printf("      %s     |", c1);
	}
	free(c1);
	
}