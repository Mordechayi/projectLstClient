#include "Validation.h"
int checkNull(char* str, char* nameStr)
{
	if (str == NULL)
	{
		printf("\n\nenter the %s correctly", nameStr);
		return 0;
	}
	return 1;
}
int sameIdAndDifName(Client* temp) {
	uint16_t mask = 1;
	if (temp->error & (mask << diffName))
	{
		printf("\nError: the id exists with a different name\n");
		return 1;
	}
	return 0;
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
void checkNullStr(char* token, int* flag)
{
	if (token == NULL || strcmp(token, "(null)") == 0)//Checks if str is NULL or one of the fields(the string) is empty or entered into the file(null) by the user(just to make sure)
		*flag = 1;
}
void checkFirstName(Client* temp, char* token)
{
	int flag = 0;
	checkNullStr(token, &flag);//Checks if token is NULL
	if (flag == 1 || !(inEnglish(token)))//if one character is in english we print dat in the errors
	{
		SetBitError((&((*temp).error)), errFirstName);
		SetBitError((&((*temp).error)), errGeneral);

	}
	temp->firstName = _strdup(token);//Inserts it into the field with space allocation
}
void checkLastName(Client* temp, char* token)
{
	int flag = 0;
	checkNullStr(token, &flag); //Checks if token is NULL
	if (flag == 1 || !(inEnglish(token)))//if one character is in english we print dat in the errors
	{
		SetBitError((&((*temp).error)), errLastName);;//where is the error
		SetBitError((&((*temp).error)), errGeneral);//General error
	}
	temp->lastName = _strdup(token);//Inserts it into the field with space allocation
}
void checkId(Client* temp, char* token)
{
	int len = 0, flag = 0;// , flag1 = 0;
	checkNullStr(token, &flag);//Checks if token is NULL
	//len = strlen(token);
	if ((flag == 1) || !(inDigit(token)) || ((len = strlen(token)) > 9) || (len < 9))
	{
		SetBitError((&((*temp).error)), errId);
		SetBitError((&((*temp).error)), errGeneral);
	}
	temp->id = _strdup(token);//Inserts it into the field with space allocation
}
void checkPhone(Client* temp, char* token)
{
	int len = 0, flag = 0;
	checkNullStr(token, &flag);//Checks if token is NULL
	if (flag == 1 || !(inDigit(token)) || (len > 10) || ((len = strlen(token)) < 10) || token[0] != '0')
	{
		SetBitError((&((*temp).error)), errPhone);
		SetBitError((&((*temp).error)), errGeneral);
	}
	temp->phone = _strdup(token);//Inserts it into the field with space allocation
}
void checkDebt(Client* temp, char* token)
{
	int flag = 0;
	checkNullStr(token, &flag);//Checks if token is NULL
	if (flag == 1 || !inDigOrPoint(token))
	{
		SetBitError((&((*temp).error)), errDebt);
		SetBitError((&((*temp).error)), errGeneral);;
		temp->errorStr.debtErrStr = _strdup(token);
	}
	else
		temp->debt = atof(token);
}
void checkDay(Client* temp, char* token)
{
	int flag = 0;
	checkNullStr(token, &flag);//Checks if token is NULL
	if (flag == 1 || !(inDigit(token)) || strlen(token) > 2 || (atoi(token)) > 31 || (atoi(token)) < 0)//check if the month is more dane 12
	{
		SetBitError((&((*temp).error)), errDate);
		SetBitError((&((*temp).error)), errDay);
		SetBitError((&((*temp).error)), errGeneral);
		temp->errorStr.dayErrStr = _strdup(token);
	}
	else
		temp->date.day = atoi(token);//Converts from string to int
}
void checkMonth(Client* temp, char* token)
{
	int flag = 0;
	checkNullStr(token, &flag);//Checks if token is NULL
	if (flag == 1 || !(inDigit(token)) || strlen(token) > 2 || atoi(token) > 12)//check if the month is more dane 12
	{
		SetBitError((&((*temp).error)), errDate);
		SetBitError((&((*temp).error)), errMonth);
		SetBitError((&((*temp).error)), errGeneral);
		temp->errorStr.monthErrStr = _strdup(token);
	}
	else
		temp->date.month = atoi(token);//Converts from string to int
}
void checkYear(Client* temp, char* token)
{
	int flag = 0;
	checkNullStr(token, &flag);//Checks if token is NULL
	if (flag == 1 || !(inDigit(token)) || (strlen(token) > 4 && token[4] != '\n'))
	{
		SetBitError((&((*temp).error)), errDate);
		SetBitError((&((*temp).error)), errYear);
		SetBitError((&((*temp).error)), errGeneral);
		temp->errorStr.YearErrStr = _strdup(token);
	}
	else
		temp->date.year = atoi(token);//Converts from string to int

}

void checkIdClient(PList list, Client* temp)
{
	if (list->head == NULL || temp->id == NULL)
		return;
	uint16_t mask = 1;
	Client* prev = list->head;//points to the beginning of the list
	Client* ptr = list->head;//points to the beginning of the list
	while (ptr && !(temp->error & (mask << diffName)))//Goes through the whole list
	{
		if (sumSameId(list, &temp, &ptr, &prev) != 0)
			return;
		//if (!(prev->next))//Checks if there is only one cell in the list - exits the loop
		//	return;
		if (ptr != prev && prev->next)// If there are several nodes and we are in the first cell - only ptr is promoted
			prev = prev->next;

		ptr = ptr->next;//Otherwise both are promoted
	}
	//return 1;
}
int strcomper(char* token, char* str)
{
	if (strcmp(token, str) != 0)
	{
		printf("\n\nenter the Key word of %s correctly!\n", str);
		return 1;
	}
	return 0;
}