#include "HeaderProject.h"

List createNewList()
{
	List list = { NULL };//Initializes the list
	return list;
}
List readFileAndCreateList(FILE* fp, char* str, List list, char* day, char* month, char*  year, char* debt)
{
	while (str)
	{
		str = readFile(fp);//Reads from the file and allocates memory according to the length of the lines
		if (str)
			addToSortrdList(&list, str, &day, &month, &year, &debt);//Creates a node and puts it in a sorted list
	}
	return list;
	free(str);//Frees the memory allocation of str
}
char* readFile(FILE* fp)
{
	char* str = NULL;
	char* input = NULL;
	char tempbuf[CHUNK];//An array of size 10 to receive the row in parts
	size_t inputlen = 0, templen = 0;
	if (fgets(tempbuf, CHUNK, fp))//If there is content in the file, reads up to the end of the line or up to 10 characters
	{
		do {
			templen = strlen(tempbuf);//Gets the number of characters received from the file

			if (!(str = realloc(input, inputlen + templen + 1)))//Allocates it space according to the number of characters received in the current and previous reading
			{
				printf("space allocation failed!");
				return NULL;
			}
			input = str;//input points to the allocated space
			strcpy(input + inputlen, tempbuf);//Copies the characters in the array

			inputlen += templen;//and increments the character counter
		} while (templen == CHUNK - 1 && tempbuf[CHUNK - 2] != '\n' && fgets(tempbuf, CHUNK, fp));
		if(input[strlen(input) - 1] == '\n')
		    input[strlen(input)-1 ] = '\0';//Adds \0 to the end of the string
	}
	else
		input = NULL;
	return input;
}
void freeList(PList list)
{
	Client* temp;
	Client* ptr = list->head;
	while (ptr)
	{
		temp = ptr->next;
		freeClient(ptr);
		ptr = temp;
	}
}
void freeClient(Client* ptr)
{
	free(ptr->firstName);
	free(ptr->lastName);
	free(ptr->id);
	free(ptr->phone);
}

FILE* openFile(FILE* fp, char* mode, char** newFile)
{
	fp = NULL;
	if (*newFile == NULL)
		*newFile = "";
	if (!(fp = fopen(*newFile, mode)))// Opens a file for reading and writing 
	{
		while (!(fp))//if not correct gets a new file name if correct continues on
		{
			printf("the file did not open!\n\n>>>>please enter the file name again->\n\n");
			*newFile = readStdin();//The function receives a string from the user and allocates memory according to the length of the lines
			fp = fopen(*newFile, mode);
			putchar('\n');
		}
	}
	return fp;
}
void closeFile(FILE* fp)
{
	if ((fclose(fp)) != 0)
		printf("ERROR in fclose()");
}
char* toLower(char* str)
{
	int i = 0;
	for (i = 0; str[i] != '\0'; i++)//Goes through the characters in the stringand converts to lowercase
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
	}
	return str;
}




Client* resetClient()
{
	Client* client;
	if (!(client = (Client*)calloc(1, sizeof(Client))))//gets Allocates memory of struct size and resets it all and checks that the allocation is correct
	{
		printf("memory allocation failed!");
		return 0;
	}
	return client;
}

char* readStdin()
{
	char* str = NULL;
	char* input = NULL;
	char tempbuf[CHUNK];
	size_t inputlen = 0, templen = 0;
	do {
		fgets(tempbuf, CHUNK, stdin);

		templen = strlen(tempbuf);
		if (!(str = realloc(input, inputlen + templen + 1)))
		{
			printf("space allocation failed!");
			return NULL;
		}
		input = str;
		strcpy(input + inputlen, tempbuf);

		inputlen += templen;
	} while (templen == CHUNK - 1 && tempbuf[CHUNK - 2] != '\n');
	input[strlen(input) - 1] = '\0';

	return input;
}

void frompt(List list, FILE* fp, char* newFile)
{
	char* str = "";
	char* token;
	if (str == NULL)
		printf("  ");
	printInstructions();
	while ((strcmp(str, "quit")) != 0)
	{
		if (!StrNotQuit(&str))
			return;
		while (str == NULL || str[0] == '\0')
		{
			printf("enter the query correctly");
			if (!StrNotQuit(&str))
				return;
		}
		toLower(str);//Converts the string to a lowercase letters
		token = strtok(str, " ");
		if ((strcmp(token, "select")) == 0)
		{
			if (checkNull(token = strtok(NULL, ""), "values after select"))
				ishere(list, token);
		}
		else if (strcmp(token, "set") == 0)
		{
			if (checkNull(token = strtok(NULL, ""), "values after set"))
			{
				fp = openFile(&fp, "a+", &newFile);
				removeSpacesFromStr(token);
				Set(&list, token, fp);
				closeFile(fp);
			}
		}
		else if (strcmp(token, "print") == 0)
			printList(list);
		else
			printf("enter the query correctly");
	}
	puts("\ngood bay :-)\n\n\n(exit by request)");
}
int StrNotQuit(char** str)
{
	puts("\n-->\n");
	*str = readStdin();//Accepts input and allocates dynamic space
	if (quit(&str))
		return 0;
	return 1;
}
int quit(char** str)
{
	if (str != NULL && strcmp(str, "quit") == 0)
	{
		puts("\ngood bay :-)\n\n\n(exit by request)");
		return 1;
	}
	return 0;
}
int checkNull(char* str, char* nameStr)
{
	if (str == NULL)
	{
		printf("\n\nenter the %s correctly", nameStr);
		return 0;
	}
	return 1;
}
void Set(PList list, char* str, FILE* fp)

{
	Client* temp = resetClient();
	char* strNew = (char*)malloc(sizeof(strlen(str) + 1));
	int len, a, * flag = &a;
	char* date, * day, * month, * year, * debt;
	char* token;
	//fputc('\n', fp);
	len = ftell(fp);


	if (!checkNull(token = strtok(str, "="), "firstname") || (strcomper(token, "firstname")) != 0 ||
		(!checkNull((token = strtok(NULL, ",")), "firstname")))
		return;
	token = checkFirstName(temp, token, flag);
	printErrorSet("first name", flag);
	temp->firstName = _strdup(token);


	if (!checkNull(token = strtok(NULL, "="), "lastname") || (strcomper(token, "lastname")) != 0 ||
		(!checkNull(token = strtok(NULL, ","), "lastname")))
	{
		free(temp);
		return;
	}
	token = checklastName(temp, token, flag);
	printErrorSet("lastname", flag);
	temp->lastName = _strdup(token);


	if (!checkNull(token = strtok(NULL, "="), "id") || (strcomper(token, "id")) != 0 ||
		(!checkNull(token = strtok(NULL, ","), "id")))
	{
		free(temp);
		return;
	}
	token = checkId(temp, token, flag);
	printErrorSet("id", flag);

	temp->id = _strdup(token);

	if (!checkNull(token = strtok(NULL, "="), "phone") || (strcomper(token, "phone")) != 0 ||
		(!checkNull(token = strtok(NULL, ","), "phone")))
	{
		free(temp);
		return;
	}
	token = checkPhone(temp, token, flag);
	printErrorSet("phone", flag);
	temp->phone = _strdup(token);

	if (!checkNull(token = strtok(NULL, "="), "date") || (strcomper(token, "date") != 0) ||
		(!checkNull(token = strtok(NULL, "/"), "day")))
	{
		free(temp);
		return;
	}
	token = checkDay(temp, token, flag);
	printErrorSet("day", flag);
	temp->date.day = atoi(token);
	day = _strdup(token);

	if (!checkNull(token = strtok(NULL, "/"), "month"))
	{
		free(temp);
		return;
	}
	token = checkMonth(temp, token, flag);
	printErrorSet("month", flag);
	month = _strdup(token);
	temp->date.month = atoi(token);

	if (!checkNull(token = strtok(NULL, ","), "year"))
	{
		free(temp);
		return;
	}
	token = checkYear(temp, token, flag);
	printErrorSet("year", flag);
	year = _strdup(token);
	temp->date.year = atoi(token);


	if (!checkNull(token = strtok(NULL, "="), "debt") || strcomper(token, "debt") != 0 ||
		(!checkNull(token = strtok(NULL, ","), "debe")))
	{
		free(temp);
		return;
	}
	token = checkDebt(temp, token, flag);
	printErrorSet("debe", flag);
	debt = _strdup(token);
	temp->debt = atof(token);
	temp->next = NULL;
	sameIdAndDifName(temp, list, token);
	if (temp->err || *flag == 1)
	{
		free(temp);
		return;
	}
	printToFile(fp, temp, day, month, year, debt);
	printf("\n\Customer details have been entered successfully!!!\n\nThe customer details after calculation are:\n");
	printf("first name = %s , last name = %s , id = %s , phone = %s , date = %d/%d/%d ,debt = %.2f", temp->firstName, temp->lastName, temp->id,
		temp->phone, temp->date.day, temp->date.month, temp->date.year, temp->debt);
	sortrdList(list, temp);
}
void printToFile(FILE* fp, Client* temp, char* day, char* month, char* year, char* debt)
{
	if (!(fprintf(fp, "\n%s,%s,%s,%s,%s,%s/%s/%s", temp->firstName, temp->lastName, temp->id, temp->phone, debt, day, month, year)))
		puts("error in the fprintf -to print to the file");
}

int strcomper(char* token, char* str)
{
	if (strcmp(token, str) != 0)
	{
		printf("\n\nyou need write the Key word of %s correctly!\n", str);
		return 1;
	}
	return 0;
}
void printErrorSet(char* str, int* flag)
{
	if (*flag == 1)
		printf("\n\nyou need write the %s correctly!\n", str);
}

void sameIdAndDifName(Client* temp, PList list, char* token)
{
	if (list == NULL || token == NULL)
		return 0;
	Client* prev = list->head;
	Client* ptr = list->head;

	while (ptr)
	{
		if (sumSameId(list, &temp, &ptr, &prev) == -1)
			return;
		if (temp->error.diffName)
		{
			printf("\nERROR!!! the same id but a diffrentt name\n");
			return;
		}
		if (ptr != prev)
			prev = prev->next;
		ptr = ptr->next;


	}

}
char* removeSpacesFromStr(char* str)// Funtion removing spaces from string
{
	{

		int nonSpaceCount = 0;// non_space_count to keep the frequency of non space characters
		int i;
		for (i = 0; str[i] != '\0'; i++)//Traverse a string and if it is non space character then, place it at index non_space_count
		{
			if (str[i] != ' ')
			{
				str[nonSpaceCount] = str[i];
				nonSpaceCount++;//non_space_count incremented
			}
		}
		str[nonSpaceCount] = '\0';//Finally placing final character at the string end
		return str;
	}
}
void stringDup(char* str1, char* str2)
{
	char* str;
	size_t n = strlen(str2);
	if (!(str = (char*)realloc(str1, sizeof(char) * n)))
	{
		printf("memory allocation failed");
		exit(0);
	}
	str1 = str;
	strcat(str1, str2);


}
int callBackFunc(int (*funSelect)(char*, Client *,int*), char* token, Client* ptr, int* PFlag)
{	
	return funSelect(token, ptr, PFlag);
}
int selectFirstName(char* token, Client* ptr, int* PFlag)
{
	if (*PFlag == 0 && (token == NULL||!inEnglish(token)))
	{
		printf("\nplease enter a valid name");
		return -2;
	}
	*PFlag = 1;
	return (strcmp(ptr->firstName,token));
}
int selectLastName(char* token, Client* ptr, int* PFlag)
{
	if (*PFlag == 0 && (token == NULL || !inEnglish(token)))
	{
		printf("\nplease enter a valid name");
		return -2;
	}
	*PFlag = 1;
	return (strcmp(((Client*)ptr)->lastName, token));
}
int selectId(char* token, Client* ptr,int* PFlag)
{
	if (*PFlag == 0 && (token == NULL || !inDigit(token) || strlen(token)>9 || strlen(token)<9))
	{
		printf("\nplease enter a valid id");
		*PFlag = 1;
		return -2;
	}
	return (strcmp(((Client*)ptr)->id, token));
}
int selectPhone(char* token, Client* ptr, int* PFlag)
{
	if (*PFlag == 0 && (token == NULL || !inDigit(token) || strlen(token) > 10 || strlen(token) < 10))
	{
		printf("\nplease enter a valid phone");
		return -2;
	}
	*PFlag = 1;
	return (strcmp(((Client*)ptr)->phone, token));
}
int selectDate(char* token, Client* ptr, int* PFlag)
{
	char* tok="";
	int day, month;
	if (token == NULL)
	{
		printf("\nplease enter a valid day");
		return -2;
	}
	if (*PFlag == 0)
		tok = _strdup(token);
	else
	{
		*(token + 2) = '/';
		*(token + 5) = '/';
	}
        *PFlag = 1;

		token = strtok(token, "/");
		if(token == NULL||!inDigit(token) ||strlen(token)>2)
		{
			printf("\nplease enter a valid day");
			return -2;
		}
	     day = atoi(token);//Saves the day with a new variable

		if (token == NULL)
		{
			printf("\nplease enter a valid month");
			return -2;
		}
		token = strtok(NULL, "/");
		if (token == NULL || !inDigit(token) || strlen(token) > 2)
		{
			printf("\nplease enter a valid month");
			return -2;
		}
		month = atoi(token);//Saves the month in a new variable
		token = strtok(NULL, "");//Saves the year
	
	if (token == NULL || !inDigit(token) || day > 31 || day < 1 || month >12 || month < 1 || atoi(token) < 1||strlen(token) > 4)
	{
		printf("\nplease enter a valid date");
		return -2;
	}

	if (ptr->date.day == day && ptr->date.month == month && ptr->date.year == atoi(token) && (!(ptr->err)))
		return 0;
	if ((ptr->date.year > atoi(token) || ((ptr->date.year == atoi(token) && ptr->date.month > month)) ||
		((ptr->date.year == atoi(token) && ptr->date.month == month && ptr->date.day > day))) && (!(ptr->err)))
		return 1;
	if ((ptr->date.year < atoi(token) || ((ptr->date.year == atoi(token) && ptr->date.month < month)) ||
		((ptr->date.year == atoi(token) && ptr->date.month == month && ptr->date.day < day))) && (!(ptr->err)))
		return -1;
	return -2;

}
int selectDebt(char* token, Client* ptr, int* PFlag)
{
	if (*PFlag == 0 && (token == NULL || !inDigOrPoint(token) ||  token[0] == '\0'))
	{
		printf("\nplease enter a valid debt");
		return -2;
	}
	*PFlag = 1;
	if (ptr->debt == atof(token))
		return 0;
	if (ptr->debt > atof(token))
		return 1;
	if (ptr->debt < atof(token))
		return -1;
	return 2;
}
void ishere(List list, char* str)
{
	Client* ptr = list.head;
	int a = 0, c = 1, * PFlag = &a, flag1 = 0, flagPrint = 0;
	char  oper, * poper, * token, oper2;
	char s[5] = "=><!";
	int (*ptr_arr[])(char*, Client*) = { selectFirstName,selectLastName,selectId,selectPhone,selectDate,selectDebt };
	int (*fun)(char*,Client*);
	if (!pointOper(str, s, &poper))
		return;
	oper = *poper;
	str = skippingProfits(str, oper);
	token = strtok(str, s);
	if (strcmp("first name", token) == 0)         fun = ptr_arr[0];
	else if (strcmp("last name", token) == 0)     fun = ptr_arr[1];
	else if (strcmp("id", token) == 0)            fun = ptr_arr[2];
	else if (flag1 = strcmp("phone", token) == 0) fun = ptr_arr[3];
	else if (flag1 = strcmp("date", token) == 0)  fun = ptr_arr[4];
	else if (flag1 = strcmp("debt", token) == 0)  fun = ptr_arr[5];
	else
	{
		printf("\nyou need write a valid Key word");
		return;
	}
	token = strtok(NULL, "");
	if (token == NULL)
	{
		printf("\nyou need write a valid value");
		return;
	}
	if (oper == '!')
	{
		oper2 = token[0];
		token++;
	}
	
	switch (oper)
	{
	case '!':
		if (invalidOperator(oper2, token))
			break;
		while (ptr)
		{
			if (!(ptr->err))
			{
				if ((flag1 = callBackFunc(fun, token, ptr, PFlag)) == -2)     { flagPrint = -1;   break;  }
				if (flag1 != 0)  {  printSelctClient(ptr, c++);  flagPrint = 1; }
			}
			ptr = ptr->next;
		}
		break;
	case '=':
		while (ptr)
		{
			if (!(ptr->err))
			{
				if ((flag1 = callBackFunc(fun, token, ptr, PFlag)) == -2)   { flagPrint = -1; break; }
				if (flag1 == 0)   { printSelctClient(ptr, c++);  flagPrint = 1;  }
			}
			ptr = ptr->next;
		}
		break;
	case '>':
		while (ptr)
		{
			if (!(ptr->err))
			{
				if ((flag1 = callBackFunc(fun, token, ptr, PFlag)) == -2)
				{
					flagPrint = -1;
					break;
				}
				if ((!(ptr->err)) && flag1 == 1)
				{
					printSelctClient(ptr, c++);
					flagPrint = 1;
				}
			}
			ptr = ptr->next;
		}
		break;
	case '<':
		while (ptr)
		{
			if (!(ptr->err))
			{
				if ((flag1 = callBackFunc(fun, token, ptr, PFlag)) == -2)
				{
					flagPrint = -1;
					break;
				}
					
				if (!(ptr->err) && flag1 == -1)
				{
					printSelctClient(ptr, c++);
					flagPrint = 1;
				}
			}
			ptr = ptr->next;
		}
		break;
	default:
		printf("\nThe operator is not valid");
		break;
	}
	if (flagPrint == 0)
		printf("\nno results were found for the last search");
	
}
int pointOper(char* str, char* s, char** poper)
{
	if (!((*poper) = strpbrk(str, s)))//oper accepts the operator into
	{
		printf("\nERROR!!!\n *invalid operator*\n");
		return 0;
	}
	return 1;
}
int invalidOperator(char oper2, char* token)
{
	if (oper2 != '=')
	{
		printf("ERROR!!!\n*invalid operator*\n");
		return 1;
	}
	return 0;
}
char* skippingProfits(char* str, char oper)
{
	char* str2 = (char*)malloc(sizeof(str));
	if (str[0] == ' ')
		str = skippingProfitsHeadStr(str);
	str2 = strchr(str, oper);
	str2 = skippingProfitsTailStr(--str2);
	str2 = strchr(str, oper);
	if (oper == '!')
		str2++;
	str2 = skippingProfitsHeadStr(++str2);
	str2 = strchr(str, '\0');
	str2 = skippingProfitsTailStr(str2);
	strcat(str, str2);
	return str;
}
char* skippingProfitsTailStr(char* str)
{
	int i = 0, j = 1;
	if (str[0] == ' ')
	{
		while (str[0] == ' ')
		{
			str--;
			i++;
		}
		i++;
		while (str[i])
		{
			str[j] = str[i];
			i++;
			j++;
		}
		str[j] = '\0';
		str++;
	}
	return str;
}
char* skippingProfitsHeadStr(char* str)
{
	int i = 0, j = 0;

	while (str[i] == ' ')
		i++;
	for (j = 0; str[i]; i++, j++)
	{
		str[j] = str[i];
	}
	str[j] = '\0';

	return str;
}
int strLexiLarge(char* str1, char* str2)
{
	int i;
	for (i = 0; (str1[i] || str2[i]); i++)
	{
		if (((!(str2[i])) && (str1[i])) || str1[i] > str2[i])
			return 1;
		if (((!(str1[i])) && (str2[i])) || str1[i] < str2[i])
			return -1;
	}
	return 0;
}

void addToSortrdList(PList list, char* str, char* day, char* month, char* year, char* debt)
{
	Client* temp = createClient(list, str,&day, &month, &year, &debt);// Creates a new struct and returns a new pointer
	checkIdClient(list, temp);//Checking if there is already a debt in his name - and the debt scheme
	sortrdList(list, temp);
}

void sortrdList(PList list, Client* temp)
{
	Client* prev = list->head;
	if (temp == NULL)
	{
		return;
	}
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
Client* createClient(PList list, char* str, char* day, char* month, char* year, char* debt)
{

	char* token;//saves the string that will be divided into sections
	int a = 0, * flag = &a;
	Client* temp = resetClient();//new Client restart
	temp->error = startError();//Initializes the error
	if (temp == NULL)
	{
		printf("allocation failed!");
		exit(0);
	}
	if (str != NULL)
		toLower(str);//Accepts a string and converts uppercase to lowercase
	token = strtok(str, ",");//Gets the string up to the first comma
	token = checkFirstName(temp, token, flag);
	temp->firstName = _strdup(token);//Inserts it into the field with space allocation

	token = strtok(NULL, ",");
	token = checklastName(temp, token, flag);
	temp->lastName = _strdup(token);//Inserts it into the field with space allocation
	token = strtok(NULL, ",");
	token = checkId(temp, token, flag);
	temp->id = _strdup(token);//Inserts it into the field with space allocation

	token = strtok(NULL, ",");
	token = checkPhone(temp, token, flag);
	temp->phone = _strdup(token);//Inserts it into the field with space allocation

	token = strtok(NULL, ",");
	token = checkDebt(temp, token, flag);
	debt = (char*)malloc(sizeof(token));
	temp->debt = atof(token);//Converts from string to float
	_gcvt(temp->debt, 10,debt) ;
	if (strcmp(token, debt) != 0)  debt = _strdup(token);
	printf("\n%s", debt);

	token = strtok(NULL, "/");//Stops at a slash to pick up a date
	token = checkDay(temp, token, flag);
	if (strlen(token) <= 2)        temp->date.day = atoi(token);//Converts from string to int
	else                       day = _strdup(token);
	printf("\n%s", day);
	token = strtok(NULL, "/");
	token = checkMonth(temp, token, flag);
	if (strlen(token) <= 2)        temp->date.month = atoi(token);		//Converts from string to int
	else {   month = _strdup(token);
		printf("\n%s", month);
	}
	token = strtok(NULL, "");
	token = checkYear(temp, token, flag);
	if (strlen(token) <= 4)        temp->date.year = atoi(token);//Converts from string to int
	else                       year = _strdup(token);
	printf("\n%s", year);
	temp->next = NULL;// Unless otherwise specified the next is NULL  


	return temp;
}
char* checkNullStr(char* token, char* nameStr, int* flag)
{
	if (token == NULL || strcmp(token, "(null)") == 0)//Checks if str is NULL or one of the fields(the string) is empty or entered into the file(null) by the user(just to make sure)
	{
		token = _strdup(nameStr);//Inserts the received string as a memory-allocated parameter
		*flag = 1;
	}
	return token;
}
char* checkFirstName(Client* temp, char* token, int* flag)
{
	int flag1 = 0;
	*flag = 0;
	token = checkNullStr(token, "(null)", flag);//Checks if token is NULL
	if (!(inEnglish(token)))//if one character is in english we print dat in the errors
	{
		token = _strdup(token);//Token gets the error
		flag1 = 1;
	}
	if (*flag == 1 || flag1 == 1)
	{
		temp->error.errFirstName = 1;
		temp->err = 1;
		*flag = 1;
	}
	return token;
}
char* checklastName(Client* temp, char* token, int* flag)
{
	int flag1 = 0;
	*flag = 0;
	token = checkNullStr(token, "(null)", flag); //Checks if token is NULL
	if (!(inEnglish(token)))//if one character is in english we print dat in the errors
	{
		token = _strdup(token);//Token gets the error
		flag1 = 1;
		*flag = 1;
	}
	if (*flag == 1 || flag1 == 1)
	{
		temp->error.errlastName = 1;//where is the error
		temp->err = 1;//General error
	}
	return token;
}
char* checkId(Client* temp, char* token, int* flag)
{
	int len = 0, flag1 = 0;
	*flag = 0;
	token = checkNullStr(token, "99999999", flag);//Checks if token is NULL
	if (!(inDigit(token))) // if one character is in digit we print dat in the errors
	{
		token = _strdup("99999999");//Token gets the error
		flag1 = 1;

	}
	len = strlen(token);
	if (len > 9)
		token = _strdup("+9");//Checks that the length is 9 characters
	else if (len < 9)
		token = _strdup("-9");//Checks that the length is 9 characters
	if (*flag == 1 || flag1 == 1 || (len > 9) || (len < 9))
	{
		temp->error.errId = 1;
		temp->err = 1;
		*flag = 1;
	}
	return token;
}
char* checkPhone(Client* temp, char* token, int* flag)
{
	int len = 0, flag1 = 0;
	*flag = 0;
	token = checkNullStr(token, "99999999", flag);//Checks if token is NULL
	if (!(inDigit(token)))// if one character is in digit we print dat in the errors
	{
		token = _strdup("99999999");//Token gets the error
		flag1 = 1;
	}
	len = strlen(token);
	if (len > 10)
		token = _strdup("+10"); //Checks that the length is 9 characters
	else if (len < 10)
		token = _strdup("-10");//Checks that the length is 9 characters
	else if (token[0] != '0')//Checks that the first digit is 0
		token = _strdup("*0");
	if (*flag == 1 || flag1 == 1 || (len > 10) || (len < 10) || token[0] != '0')
	{
		temp->error.errPhone = 1;
		temp->err = 1;
		*flag = 1;
	}
	return token;
}
char* checkDebt(Client* temp, char* token, int* flag)
{
	int flag1 = 0;
	*flag = 0;
	token = checkNullStr(token, "0", flag);//Checks if token is NULL
	if (!inDigOrPoint(token))// if one character (from the last location) is in digit we print dat in the errors
	{
		
		flag1 = 1;
	}
	if (flag1 == 1)//check if the debt in the locatine 0 is '-'
	{
		temp->error.errDebt = 1;
		temp->err = 1;
		*flag = 1;
	}
	return token;
}
char* checkDay(Client* temp, char* token, int* flag)
{
	int flag1 = 0, atint;
	*flag = 0;
	token = checkNullStr(token, "0", flag);//Checks if token is NULL
	if (!(inDigit(token))||strlen(token)>2)//if one character is in digit we print dat in the errors
	{
		//token = _strdup("0");//Token gets the error
		flag1 = 1;
	}
	    atint = atoi(token);
	if (*flag == 1 || flag1 == 1 || atint > 31)//check if the month is more dane 12
	{
		temp->error.errDate = 1;
		temp->err = 1;
		*flag = 1;
	}
	return token;
}
char* checkMonth(Client* temp, char* token, int* flag)
{
	int flag1 = 0;
	*flag = 0;
	token = checkNullStr(token, "0", flag);//Checks if token is NULL
	if (!(inDigit(token)) || strlen(token) > 2)//if one character is in digit we print dat in the errors
	{
		//token = _strdup("0");//Token gets the error
		flag1 = 1;
	}
	if (*flag == 1 || flag1 == 1 || atoi(token) > 12)//check if the month is more dane 12
	{
		temp->error.errDate = 1;
		temp->err = 1;
		*flag = 1;
	}
	return token;
}
char* checkYear(Client* temp, char* token, int* flag)
{
	int flag1 = 0;
	*flag = 0;
	token = checkNullStr(token, "0", flag);//Checks if token is NULL
	if (!(inDigit(token)) || strlen(token) > 4)//if one character is in digit we print dat in the errors
	{
		//token = _strdup("0");//Token gets the error
		flag1 = 1;
	}
	if (*flag == 1 || flag1 == 1)
	{
		temp->error.errDate = 1;
		temp->err = 1;
		*flag = 1;
	}
	return token;
}
int inDigitDate(char* str)
{
	int i;
	if (str == NULL || strcmp(str, "(null)") == 0)//Checks if str is NULL
		return;
	for (i = 0; str[i]; i++)
	{
		if ((!(isdigit(str[i])) && str[i] != '/'))//Checks that the one she didn't tell isn't either /
			return 0;
	}
	return 1;
}
int inDigit(char* str)
{
	int i;
	if (str == NULL || strcmp(str, "(null)") == 0)//Checks if str is NULL
		return;
	for (i = 0; str[i]; i++)
	{
		if (!(isdigit(str[i])))//Checks if the character  are digits
			return 0;
	}
	return 1;
}
int inDigOrPoint(char* str)
{
	int i, val = 0;
	float x = 0;
	if (str == NULL || strcmp(str, "(null)") == 0)//Checks if str is NULL
		return;
	val = sscanf(str, "%*f %f", &x);//Checks if the character  are digits
	if (val != -1 || (str[0] == '-' && !isdigit(str[1])) || (str[0] == '+' && !isdigit(str[1])))
		return 0;
	return 1;
	/*return val;*/
}

int inEnglish(char* str)
{
	int i;
	for (i = 0; str[i]; i++)
	{
		if (!(isalpha(str[i])))//Checks if the character  is in English
			return 0;
	}
	return 1;
}
void  checkIdClient(PList list, Client* temp)
{
	if (list->head == NULL || temp->id == NULL)
		return;
	Client* prev = list->head;//points to the beginning of the list
	Client* ptr = list->head;//points to the beginning of the list
	while (ptr &&  !temp->error.diffName)//Goes through the whole list
	{
		if (sumSameId(list, &temp, &ptr, &prev) != 0)
			return;
		//if (!(prev->next))//Checks if there is only one cell in the list - exits the loop
		//	return;
		if (ptr != prev&&prev->next)// If there are several nodes and we are in the first cell - only ptr is promoted
			prev = prev->next;
		
		ptr = ptr->next;//Otherwise both are promoted
	}

	//return 1;
}
int sumSameId(PList list, Client** temp, Client** ptr, Client** prev)
{
	if (strcmp((*ptr)->id, (*temp)->id) == 0 && (!((*ptr)->err)))//If the id Their is the same as concluded and returns the new date
	{

		if (((*ptr)->firstName != NULL) && (strcmp((*ptr)->firstName, (*temp)->firstName) == 0) && ((*ptr)->lastName != NULL)
			&& (strcmp((*ptr)->lastName, (*temp)->lastName) == 0) && (!((*temp)->err)))//If the names are the same and there is no error
		{
			(*temp)->debt = ((*ptr)->debt + (*temp)->debt);//Schema and providing the value within the already existing customer
			checkDate((*temp), (*ptr));//Checking the latest date among them
			if ((*ptr) == (*prev))//If the cell worth renewing is the new cell 
			{
				if (list->head->next == NULL)//If the only one on the list
					list->head = (*ptr)->next = NULL;
				else if (list->head == (*ptr))
					list->head = list->head->next;
				else
					//(*prev)->next = (*temp);
					(*prev)->next =(*ptr)->next;//links it to the next one in the list
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
		else if (!((*temp)->error.diffName) && !((*ptr)->error.diffName))//If there are no errors in the node
		{
			if ((*ptr)->firstName == NULL || (*ptr)->lastName == NULL)
				return 1;
			if ((strcmp((*ptr)->firstName, (*temp)->firstName) != 0) || (strcmp((*ptr)->lastName, (*temp)->lastName) != 0))
			{
				(*temp)->error.diffName = 1;
				(*temp)->err = 1;
			}
		}
	}
	return 0;
}
void checkDate(Client* temp, Client* ptr)
{
	if (ptr->date.year < temp->date.year || (((temp->date.year) == (ptr->date.year)) && ((ptr->date.month) < (temp->date.month))) ||
		(((temp->date.year) == (ptr->date.year)) && ((temp->date.month) == (ptr->date.month)) && ((ptr->date.day) < (temp->date.day))))
		return;
	else
		temp->date = ptr->date;



}

Error startError()
{
	Error err = { 0,0,0,0,0,0,0 };//Initializes the list
	return err;
}

void printClient(Client* client, int i)//Printing one customer from the list
{
	printf("    |   |                |                   |            |             |            |          |\n");
	printf("    |%2d.|%-16s|%-19s|%-12s|%-13s| %02d/%02d/%04d |%10.2f|\n", i, client->firstName, client->lastName, client->id, client->phone,
		client->date.day, client->date.month, client->date.year, client->debt);
	printf("    |___|________________|___________________|____________|_____________|____________|__________| \n");
}
void printClientErr(Client* client, int  i)//Printing one customer with errors from the list
{

	printf("    |   |                |                   |            |             |            |          |\n");
	printf("    |%2d.|%-16s|%-19s|%-12s|%-13s| %02d/%02d/%04d |%9.2f |\n", i, client->firstName, client->lastName, client->id, client->phone,
		client->date.day, client->date.month, client->date.year, client->debt);
	printf("    |   |----------------|-------------------|------------|-------------|------------|----------| \n");
}
void printList(List list)//print the list
{
	int i = 1, a = 0, flag1 = 0;;
	int* flag = &a;
	Client* ptr = list.head;//Pointer to the beginning of the list

	while (ptr)
	{
		if (!ptr->err && !flag1)
		{
			printTitles("     LIST OF CLIENTS DEBT");
			flag1 = 1;
		}
		if (!(ptr->err))
		{
			if (ptr->debt > 0)
				ptr->debt = 0;
			printClient(ptr, i++);
		}

		ptr = ptr->next;//Promotion by one node until the end of the list is reached
	}
	ptr = list.head;//Resets the pointer to the beginning of the list
	i = 1;//Resets the list numbers

	while (ptr)
	{
		if (*flag == 0 &&  ptr->err)
			printTitlesErr(flag);

		if (ptr->err)
		{
			printClientErr(ptr, i++);
			errorToPrint(ptr);
			printf("\n    |___|________________|___________________|____________|_____________|____________|__________| \n");
		}
		ptr = ptr->next;//Promotion by one node until the end of the list is reached
	}
}
void printTitles(char* str)
{
	printf("\n                                    %s \n", str);
	printf("    _____________________________________________________________________________________________\n");
	printf("    |   |                |                   |            |             |            |          |\n");
	printf("    | N |   %s   |     %s     |     %s     |    %s    |    %s    |   %s   |\n", "first name", "last name", "id", "phone", "date", "debt");
	printf("    |___|________________|___________________|____________|_____________|____________|__________| \n");
}
void printTitlesErr(int* flag)
{
	*flag = 1;
	printf("\n\n\n\n\n\n                                   LIST OF CLIENTS DEBT - WITH ERRORS \n");
	printf("    _____________________________________________________________________________________________\n");
	printf("    |   |                |                   |            |             |            |          |\n");
	printf("    | N |   %s   |     %s     |     %s     |    %s    |    %s    |   %s   |\n", "first name", "last name", "id", "phone", "date", "debt");
	printf("    |___|________________|___________________|____________|_____________|____________|__________| \n");
}
void errorToPrint(Client* temp)
{
	char* c1 = "     ", * c2 = "     ", * c3 = "     ", * c4 = "     ", * c5 = "     ", * c6 = "     ", * c7 = "               ";
	if (!temp)
		return;

	if (temp->error.errFirstName)
		c1 = "ERROR";
	if (temp->error.errlastName)
		c2 = "ERROR";
	if (temp->error.errId)
		c3 = "ERROR";
	if (temp->error.errPhone)
		c4 = "ERROR";
	if (temp->error.errDebt)
		c5 = "ERROR";
	if (temp->error.errDate)
		c6 = "ERROR";
	if (temp->error.diffName)
		c7 = "*different name";

	printf("    |   |     %s      |       %s       |   %s    |    %s    |    %s   |   %s  |%s", c1, c2, c3, c4, c5, c6, c7);
}

void printSelctClient(Client* ptr, int i)
{
	if (i == 1)
		printTitles("Your search results");
	printClient(ptr, i);
}
void printInstructions()
{
	printf("\n\n\n\nGeneral instructions for use:\n\n\tTo search for an existing customer : \n\n\t\t\t1.write select, \n\t\t\t2.Enter the type of value requested(last name, id, phone, first name, date, debt)\n\t\t\t"
		"3. Write the operator, (=, =!, <, >)\n\t\t\t4. write the operand,\n\t\tFor example : select date < 11 / 11 / 2020\n\n\t"
		"To add a new customer or change an existing customer : \n\n\t\t"
		"The format will look like this - first name = ..., last name = ..., id = ..., phone = ..., date = .. / .. / ...., debt = ...\n\t\t\t"
		"1. write set,\n\t\t\t2. Write the value type\n\t\t\t3. Write operator =\n\t\t\t4. write the appropriate value,\n\t\t\t"
		"5. Separate the fields with the character ','\n\t\t\t6. Repeat actions 2 - 5 for all fields(do not add ',' at the end),\n\t\t"
		"For example : first name = Israel, last name = Israel, id = 123456789, phone = 0123456789, date = 01 / 01 / 2023, debt = -100\n\n\t"
		"To print the list of customers with debt : \n\n\t\tWrite print and press Enter\n\n\n");
}
// set first name = aaaaaaa, last name = nnnnnnnnnn, id = 3333333333, phone = 22222222, date = 11 / 11 / 1111, debt = -1111
//set first name=david,last name=leiderman,id=200000101,phone=0555555522,date=2/12/2222,debt=-1000
// set   first name  =  aaaaaaa   ,    last name   =   nnnnnnnnnn   ,   id=  343333333  ,  phone  =  2222222212  ,  date   =   11/11/1111  ,   debt  =  -1111
