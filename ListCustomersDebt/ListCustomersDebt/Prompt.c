#include "Prompt.h"
#include "List.h"
void prompt(List list, FILE** fp, char** newFile)
{
	char* str = "";
	char* token;
	if (str == NULL)
		printf("  ");
	printInStructions();
	while ((strcmp(str, "quit")) != 0)
	{
		if (!StrNotQuit(&str)) {
			free(str);
			return;
		}
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
				openFile(fp, "a+", newFile);//Enter as a parameter the name of the file that we wrote in main or that we received from the user
				removeSpacesFromStr(token);
				Set(&list, token, *fp);
				closeFile(*fp);
			}
		}
		else if (strcmp(token, "print") == 0) {
			//system("cls");

			
			printList(list);
		}
		else
			printf("enter the query correctly");
		free(str);
	}
	
	puts("\ngood bay :-)\n\n\n(exit by request)");
}
int StrNotQuit(char** str)
{
	puts("\n-->\n");
	readFileAndStdinWithMemoryAllocation(stdin, str);//Accepts input and allocates dynamic space
	if (quit(*str))
		return 0;
	return 1;
}
int quit(char* str)
{
	if (str != NULL && strcmp(str, "quit") == 0)
	{
		puts("\ngood bay :-)\n\n\n(exit by request)");
		return 1;
	}
	return 0;
}
void Set(PList list, char* str, FILE* fp)

{
	Client* temp = initializationClient();//pointer to a client
	float tempDebt;//It will hold the value of temp entered, even if a calculation is done on it
	int flag = 0;//flag to chech if the file is empty - then we wonwt go down a line before writing
	char* token = NULL;
	/* an array of pointers to functions, to check tht correctness of the input */
	void (*PoinersToFuncCheck[8])(Client*, char*) = { checkFirstName,checkLastName,checkId,checkPhone,checkDay,checkMonth,checkYear,checkDebt };
	char* strClient[8] = { "firstname","lastname","id","phone","day","month","year","debt" };//an array  of strings with the keywords that need enter
	for (int i = 0; i < 8; i++)
	{
		if (i == 0) {
			if (!checkNull(token = strtok(str, "="), strClient[i]))     return;
			strcomper(token, strClient[i]);
			if (!checkNull((token = strtok(NULL, ",")), strClient[i]))    return;
		}
		else if (i < 4 || i == 7) {
			if (!checkNull(token = strtok(NULL, "="), strClient[i]))
			{
				free(temp);//////////////////////////
				return;
			}
			strcomper(token, strClient[i]);
		}
		if ((i > 0 && i < 4) || i > 5) {
			if (!checkNull(token = strtok(NULL, ","), strClient[i]))
			{
				free(temp);
				return;
			}
		}
		else if (i > 0 && i < 6) {
			if ((i == 4 && (!checkNull(token = strtok(NULL, "="), "date"))))
			{
				free(temp);
				return;
			}
			if (i == 4)     strcomper(token, "date");
			token = strtok(NULL, "/");
		}
		PoinersToFuncCheck[i](temp, token);
	}
	printErrorInSet(temp);

	temp->next = NULL;
	tempDebt = temp->debt;
	if (list->head)  flag = 1;
	sameId(temp, list, token);
	if (GetBitError(temp->error, errGeneral))
	{
		free(temp);
		return;
	}
	if (flag == 1) fprintf(fp, "\n");
	printToFile(fp, temp, tempDebt);
	printf("\n\Customer details have been entered successfully!!!\n\nThe customer details after calculation are:\n");
	printf("first name = %s , last name = %s , id = %s , phone = %s , date = %d/%d/%d ,debt = %.2f", temp->firstName, temp->lastName, temp->id,
		temp->phone, temp->date.day, temp->date.month, temp->date.year, temp->debt);
	addToSortedList(list, temp);
}
void printErrorInSet(Client* temp) {
	int flag = 0;
	uint16_t mask = 1;
	char* strClient[8] = { "firstname","lastname","id","phone","debt","day","month","year" };
	for (int i = errFirstName, j = 0; i <= errYear; i++, j++) {
		if (i == 4 || i == 7)
			i++;
		if (temp->error & (mask << i))
			printErrorSet(strClient[j], &flag);
	}
	if (flag)
		printf("correctly!");
}
void printErrorSet(char* str, int* flag)
{
	if (!(*flag))
		printf("\nyou need write the %s ", str);
	else {
		printf(", %s ", str);
		*flag = 1;

	}
}
int callBackFunc(int (*funSelect)(char*, Client*, int*), char* token, Client* ptr, int* PFlag)
{
	return funSelect(token, ptr, PFlag);
}
int selectFirstName(char* token, Client* ptr, int* PFlag)
{
	if (*PFlag == 0 && (token == NULL || !inEnglish(token)))
	{
		printf("\nplease enter a valid name");
		return -2;
	}
	*PFlag = 1;
	return (strcmp(ptr->firstName, token));
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
int selectId(char* token, Client* ptr, int* PFlag)
{
	if (*PFlag == 0 && (token == NULL || !inDigit(token) || strlen(token) > 9 || strlen(token) < 9))
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
	char* tok = "";
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
	if (token == NULL || !inDigit(token) || strlen(token) > 2)
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

	if (token == NULL || !inDigit(token) || day > 31 || day < 1 || month >12 || month < 1 || atoi(token) < 1 || strlen(token) > 4)
	{
		printf("\nplease enter a valid date");
		return -2;
	}

	if (ptr->date.day == day && ptr->date.month == month && ptr->date.year == atoi(token) && (!GetBitError(ptr->error, errGeneral)))
		return 0;
	if ((ptr->date.year > atoi(token) || ((ptr->date.year == atoi(token) && ptr->date.month > month)) ||
		((ptr->date.year == atoi(token) && ptr->date.month == month && ptr->date.day > day))) && (!GetBitError(ptr->error, errGeneral)))
		return 1;
	if ((ptr->date.year < atoi(token) || ((ptr->date.year == atoi(token) && ptr->date.month < month)) ||
		((ptr->date.year == atoi(token) && ptr->date.month == month && ptr->date.day < day))) && (!GetBitError(ptr->error, errGeneral)))
		return -1;
	return -2;

}
int selectDebt(char* token, Client* ptr, int* PFlag)
{
	if (*PFlag == 0 && (token == NULL || !inDigOrPoint(token) || token[0] == '\0'))
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
	int (*fun)(char*, Client*);
	if (!pointOper(str, s, &poper))
		return;
	oper = *poper;
	str = skippingProfits(str, oper);
	token = strtok(str, s);
	if (!token) return;//  להוציא הודעת שגיאה לצרף לפונ' קיימת
	if (strcmp("first name", token) == 0)         fun = ptr_arr[0];//בדיקה אם יש אפשרות ללולאה
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
			if (!GetBitError(ptr->error, errGeneral))
			{
				if ((flag1 = callBackFunc(fun, token, ptr, PFlag)) == -2) { flagPrint = -1;   break; }
				if (flag1 != 0) { printSelectClient(ptr, c++);  flagPrint = 1; }
			}
			ptr = ptr->next;
		}
		break;
	case '=':
		while (ptr)
		{
			if (!GetBitError(ptr->error, errGeneral))
			{
				if ((flag1 = callBackFunc(fun, token, ptr, PFlag)) == -2) { flagPrint = -1; break; }
				if (flag1 == 0) { printSelectClient(ptr, c++);  flagPrint = 1; }
			}
			ptr = ptr->next;
		}
		break;
	case '>':
		while (ptr)
		{
			if (!GetBitError(ptr->error, errGeneral))
			{
				if ((flag1 = callBackFunc(fun, token, ptr, PFlag)) == -2)
				{
					flagPrint = -1;
					break;
				}
				if ((!!GetBitError(ptr->error, errGeneral)) && flag1 == 1)
				{
					printSelectClient(ptr, c++);
					flagPrint = 1;
				}
			}
			ptr = ptr->next;
		}
		break;
	case '<':
		while (ptr)
		{
			if (!GetBitError(ptr->error, errGeneral))
			{
				if ((flag1 = callBackFunc(fun, token, ptr, PFlag)) == -2)
				{
					flagPrint = -1;
					break;
				}
				if (!GetBitError(ptr->error, errGeneral) && flag1 == -1)
				{
					printSelectClient(ptr, c++);
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
char* skippingProfits(char* str, char oper)
{
	char* str2 = (char*)malloc(sizeof(str)+1);
	char* tempStr2 = str2;
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
	free(tempStr2);
	return str;
}

void printSelectClient(Client* ptr, int i)
{
	if (i == 1)
		printTitles("Your search results");
	printClient(ptr, i);
}
void printInStructions()//user instructions
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
