#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <stdint.h>
#include <inttypes.h>
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define CHUNK 10
#define CHUNK_IN 25



typedef struct Date
{
	unsigned int day;
	unsigned int month;
	unsigned int year;
}Date;

typedef struct Error//where is the error
{
	char* debtErrStr;
	char* dayErrStr;
	char* monthErrStr;
	char* YearErrStr;

}Error;

typedef struct Client
{

	char* firstName;
	char* lastName;
	char* id;
	char* phone;
	float debt;
	Date date;
	Error errorStr;
	uint16_t error;

	struct Client* next;
} Client, * PClient;

typedef struct List
{
	Client* head;//Pointr to head of the list

}List, * PList;


/*errors optiononality to be kept in bits*/
enum {
	errFirstName, errLastName, errId, errPhone, errDate, errDebt, diffName, errDay, errMonth, errYear, errGeneral
};



/*
general
Goes through the characters in the string and converts to lowercase

@param char*
@return char*
*/
char* toLower(char* str);
/*
general
removes spaces from a string

@param char*
@return char*
*/
char* removeSpacesFromStr(char* str);
///*general
//like the functions _strdup() and strcat() together
//receives 2 strings and adds the second to the first string withe memory allocation
//
//@param char* str1, char* str2
//*/
//void stringDup(char* str1, char* str2);
/*
general
removes spaces from the end of a string

@param char*
@return char*
*/
char* skippingProfitsTailStr(char* str);
/*
general
removes spaces from the head of a string

@param char*
@return char*
*/
char* skippingProfitsHeadStr(char* str);

//int strLexiLarge(char* str1, char* str2)
/*
general
changes the bit according to the received number

@param uint16_t* number, int bit
*/
void SetBitError(uint16_t* number, int bit);
/*
general
gets the bit in the position of the received number (shifted to the left)

@param uint16_t* number, int bit
*/
int GetBitError(uint16_t number, int bit);
/*
general
Checks that all characters in the received string are digits or in '/'

@param char*
@return int
*/
int inDigitDate(char* str);
///*
//general
//Checks that all characters in the received string are digits
//
//@param char*
//@return int
//*/
//int inDigit(char* str);

/*general
Checks that all characters in the received string are digits or point

@param char*
@return int*/
int inDigOrPoint(char* str);
/*general
Checks that all characters in the received string are in english

@param char*
@return int*/
int inEnglish(char* str);

#endif