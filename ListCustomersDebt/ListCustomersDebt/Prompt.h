#pragma once
#include "List.h"

/*
general
responsible for queries and entering data from the user

@param List list, FILE** fp, char** newFile
*/
void prompt(List list, FILE** fp, char** newFile);
/*
general
Receives a new string from the user and allocates memory to it
if quit has been entered sends to a function that exits the program

@param char** str
@return int
*/
int StrNotQuit(char** str);
/*
general
Customer insertion by the user

@param PList list, char* str, FILE* fp
*/
void Set(PList list, char* str, FILE* fp);
/*
general
prints the errors in the client entered by the user

@param Client* temp
*/
void printErrorInSet(Client* temp);
/*
general
indicates the errors in the client entered by the user

@param char* str, int* flag
*/
void printErrorSet(char* str, int* flag);
int callBackFunc(int (*funSelect)(char*, Client*, int*), char* token, Client* ptr, int* PFlag);
int selectFirstName(char* token, Client* ptr, int* PFlag);
int selectLastName(char* token, Client* ptr, int* PFlag);
int selectId(char* token, Client* ptr, int* PFlag);
int selectPhone(char* token, Client* ptr, int* PFlag);
int selectDate(char* token, Client* ptr, int* PFlag);
int selectDebt(char* token, Client* ptr, int* PFlag);
void ishere(List list, char* str);
char* skippingProfits(char* str, char oper);
void printInStructions();
void printSelectClient(Client* ptr, int i);