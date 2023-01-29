#include "GeneralData.h"

char* toLower(char* str)
{
	int i = 0;
	for (i = 0; str[i] != '\0' && str[i] != '\n'; i++)//Goes through the characters in the string and converts to lowercase
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
	}
	return str;
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
//void stringDup(char* str1, char* str2)
//{
//	char* str;
//	size_t n = strlen(str2);
//	if (!(str = (char*)realloc(str1, sizeof(char) * n)))
//	{
//		printf("memory allocation failed");
//		exit(0);
//	}
//	str1 = str;
//	strcat(str1, str2);
//
//
//}
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
//int strLexiLarge(char* str1, char* str2)
//{
//	int i;
//	for (i = 0; (str1[i] || str2[i]); i++)
//	{
//		if (((!(str2[i])) && (str1[i])) || str1[i] > str2[i])
//			return 1;
//		if (((!(str1[i])) && (str2[i])) || str1[i] < str2[i])
//			return -1;
//	}
//	return 0;
//}
void SetBitError(uint16_t* number, int bit)
{
	uint16_t unity = 1;
	(*number) |= (unity << bit);
}
int GetBitError(uint16_t number, int bit)
{
	unsigned int unity = 1, res;
	res = number & (unity << bit);
	return res != 0; //(number>>bit)&1
}

int inDigitDate(char* str)
{
	int i;
	if (str == NULL || strcmp(str, "(null)") == 0)//Checks if str is NULL
		return;
	for (i = 0; str[i]; i++)
	{
		if ((!(isdigit(str[i])) && str[i] != '/'))//Checks that the one she didn't tell isn't either 
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
		if (!(isdigit(str[i])) && str[i] != '\n')//Checks if the character are digits
			return 0;
	}
	return 1;
}
int inDigOrPoint(char* str)
{
	int i, wasAPoint = 0, wasAMins = 0, wasAPlus = 0;
	if (str == NULL || strcmp(str, "(null)") == 0)//Checks if str is NULL
		return;
	for (i = 0; str[i]; i++)
	{

		if (!(isdigit(str[i])))//Checks if the character  are digits
		{
			if (str[i] == '-' && (i != 0) || (str[0] == '-' && !isdigit(str[1])))           return 0;
			if (str[i] == '+' && (i != 0) || (str[0] == '+' && !isdigit(str[1])))           return 0;
			if ((str[i] == '.' && wasAPoint == 1) || (str[i] == '.' && (i == 0 || str[i + 1] == '\0')))    	return 0;
			else if (str[i] == '.')       wasAPoint = 1;
			else if (str[i] != '-' && str[i] != '+') return 0;
		}
	}
	return 1;
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
// set first name = aaaaaaa, last name = nnnnnnnnnn, id = 3333333333, phone = 22222222, date = 11 / 11 / 1111, debt = -1111
//set first name=david,last name=leiderman,id=200000101,phone=0555555522,date=2/12/2222,debt=-1000
// set   first name  =  aaaaaaa   ,    last name   =   nnnnnnnnnn   ,   id=  343333333  ,  phone  =  2222222212  ,  date   =   11/11/1111  ,   debt  =  -1111
