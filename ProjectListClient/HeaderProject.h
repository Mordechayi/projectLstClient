#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>



#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define CHUNK 10



typedef struct Date
{
	unsigned int day : 6;
	unsigned int month : 5;
	unsigned int year : 14;
}Date;

typedef struct Error//where is the error
{
	unsigned int errFirstName : 1;
	unsigned int errlastName : 1;
	unsigned int errId : 1;
	unsigned int errPhone : 1;
	unsigned int errDate : 1;
	unsigned int errDebt : 1;
	unsigned int diffName : 1;
}Error;

typedef struct Client
{

	char* firstName;
	char* lastName;
	char* id;
	char* phone;
	int err; //General error
	float debt;
	Date date;
	Error error;

	struct Client* next;
} Client, * PClient;

typedef struct List
{
	Client* head;

}List, * PList;

//*********************************************************************  file  *************************************************************************

/*
General
the function opens a new file for reading
and writing - and checks the correctness of the opening

@param FILE*
@retrn FILE*
*/
FILE* openFile(FILE* fp, char* mode, char** newFile);

/*
General
the function closes the opened file
and checks the correctness of the closure

@param FILE*
*/
void closeFile(FILE* fp);

/*
General
Creates a linked list from the fp file

@param FILE* , char * , List
@return List
*/
List readFileAndCreateList(FILE* fp, char* str, List list, char* day, char* month, char* year, char* debt);

/*
General


@param FILE*
@return char*
*/
char* readFile(FILE* fp);

//*****************************************************************   list client   *******************************************************************

/*
General
Releases the dynamic allocation to the struct

@param Client*
*/
void freeClient(Client* ptr);

/*
General
Releases the dynamic allocation to a list of struct

@param PList
*/
void freeList(PList list);
/*
general
The function assign allocates memory of struct size and resets
it alland checks that the allocation is correct

@return Client*
*/
Client* resetClient();

/*
general
Creating a new list and initializing the list

@return List
*/
List createNewList();//Creates and initializes a new list

/*
general
Initializes the error struct initializes all fields to 0

@return Error
*/
Error startError();



//**************************************************************  cheke client  *****************************************************************

/*
general
Checking whether the client already exists

@param PList,Client*
*/
void checkIdClient(PList list, Client* temp);

/*
general
Checking the later date among them

@param PList, Client*
*/
void checkDate(Client* prev, Client* temp);


//****************************************************************   frompt   *******************************************************************




void frompt(List list, FILE* fp, char* newFile);//Accepts the data that is entered


//******************************************************************  set  **********************************************************************

int sumSameId(PList list, Client** temp, Client** ptr, Client** prev);
void sameIdAndDifName(Client* temp, PList list, char* token);
char* removeSpacesFromStr(char* str);
void printErrorSet(char* str, int* flag);
//int checkSetStr(char* token, char* str, int i);
//void addToSortrdList(PList list, char* str);//Puts in the list and sorts according to the value of the debt
void sortrdList(PList list, Client* temp);
void addToSortrdList(PList list, char* str);
Client* createClient(PList list, char* str);//יוצר מבנה של לקוח חדש  


//****************************************************************  check set  *****************************************************************


/*
general
Checks that all characters in the received string are in English

@param PList , char* , FILE*
*/
void Set(PList list, char* str, FILE* fp);//יצירת לקוח על ידי המשתמש

/*
general
Checks that the first name its corecte
@param Client* , char* , int*
@return  char*
*/
char* checkFirstName(Client* temp, char* token, int* flag);
/*
general
Checks that the first name its corecte
@param Client* , char* , int*
@return  char*
*/
char* checklastName(Client* temp, char* token, int* flag);
/*
general
Checks that the first name its corecte
@param Client* , char* , int*
@return  char*
*/
char* checkId(Client* temp, char* token, int* flag);
/*
general
Checks that the first name its corecte
@param Client* , char* , int*
@return  char*
*/
char* checkPhone(Client* temp, char* token, int* flag);
/*
general
Checks that the first name its corecte
@param Client* , char* , int*
@return  char*
*/
char* checkMonth(Client* temp, char* token, int* flag);
/*
general
Checks that the first name its corecte
@param Client* , char* , int*
@return  char*
*/
char* checkDay(Client* temp, char* token, int* flag);
/*
general
Checks that the first name its corecte
@param Client* , char* , int*
@return  char*
*/
char* checkDebt(Client* temp, char* token, int* flag);
///*
//general
//Checks that the day name its corecte
//@param Client* , char* , int*
//@return  char*
//*/
//char* checkDay(Client* temp, char* token, int* flag);
/*
general
Checks that the year its corecte
@param Client* , char* , int*
@return  char*
*/
char* checkYear(Client* temp, char* token, int* flag);


//****************************************************************  frompt select  *****************************************************************


char* skippingProfits(char* str, char oper);
char* skippingProfitsHeadStr(char* str);
char* skippingProfitsTailStr(char* str);

/*
general
Checking whether the client entered by the user already exists

@param char* , char* , char**
@return int
*/
int pointOper(char* str, char* s, char** poper);


int invalidOperator(char oper2, char* token);
void ishere(List list, char* srt);// 
void stringDup(char* str1, char* str2);//


//*******************************************************************   print    *******************************************************************


void printClient(Client* client, int i);//מדפיס נתוני לקוח
void printList(List list);//מדפיס את רשימת הלקוחות
void printClientErr(Client* client, int  i);//הדפסת לקוח עם שגיאות בנתונים
void errorToPrint(Client* temp);
void printTitlesErr(int* flag);
void printTitles(char* str);
void printSelctClient(Client* ptr, int i);
void printToFile(FILE* fp, Client* temp, char* day, char* month, char* year, char* debt);
int inDigOrPoint(char* str);
//*******************************************************************  general  ********************************************************************
int StrNotQuit(char* str);
int quit(char* str);
//void openFileToWirth(&fp);
/*
general
Checks that all characters in the received string are in English

@param char*
@return int
*/
int inEnglish(char* str);

/*
general
Checks that all characters in the received string are digits

@param char*
@return int
*/
int inDigit(char* str);

/*
general
Checks that all characters in the received string are digits

@param char*
@return int
*/
int inEnglish(char* str);





char* readStdin();







int strLexiLarge(char* str1, char* str2);

/*general
Goes through the characters in the string and converts to lowercase

@param char*
@return char*
*/
char* toLower(char* str);








int strcomper(char* token, char* str);

/*
general
Checks that all characters in the received string are digits or /

@param char*
@return int
*/
int inDigitDate(char* str);

/*
general
Checks if str is NULL or one of the fields(the string) is empty
or entered into the file(null) by the user(just to make sure)

@param char* ,char*
@return int
*/
Client* createClient(PList list, char* str, char* day, char* month, char* year, char* debt);
//List readFileAndCreateList(FILE* fp, char* str, List list, char* day, char* month, char* year, char* debt);
int callBackFunc(int (*funSelect)(char*, Client*, int*), char* token, Client* ptr, int* PFlag);
int selectFirstName(char* token, Client* ptr, int* PFlag);
int selectLastName(char* token, Client* ptr, int* PFlag);
int selectId(char* token, Client* ptr, int* PFlag);
int selectPhone(char* token, Client* ptr, int* PFlag);
int selectDate(char* token, Client* ptr, int* PFlag);
int selectDebt(char* token, Client* ptr, int* PFlag);
void printInstructions();
//char* read_str(char* str);

//int check_fix(Client* temp, char* token, int i);

//void healthCheck(void* fileString);//פונקציה גנרית לבדיקת תקינות זיכרון








#endif



