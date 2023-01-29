#pragma once
#include "GeneralData.h"
//#include "List.h"
/*
general
if the strint is NULL print error message 
with the name of the field whose value is NULL

@param char* str, char* nameStr
return int 
*/
int checkNull(char* str, char* nameStr);
/*
general
Check if the existing client has a different name than what we got from the file

@param Client* temp, PList list, char* token
*/
int sameIdAndDifName(Client* temp);
/*
general
Checking whether the client entered by the user already exists

@param char* , char* , char**
@return int
*/
int pointOper(char* str, char* s, char** poper);
/*
general
Checks that an '=' operator has been inserted
between the keyword and the value

@param char oper2, char* token
@return int
*/
int invalidOperator(char oper2, char* token);
/*
general
if the strint is NULL changes the flag value to  1

@param char* token, int* flag
*/
void checkNullStr(char* token, int* flag);
/*
general
Checks that the first name its valid

@param Client* , char* , int*
*/
void checkFirstName(Client* temp, char* token);
/*
general
Checks that the last name its valid

@param Client* , char* , int*
*/
void checkLastName(Client* temp, char* token);
/*
general
Checks that the id its valid

@param Client* , char* , int*
*/
void checkId(Client* temp, char* token);
/*
general
Checks that the phone its valid

@param Client* , char* , int*
*/
void checkPhone(Client* temp, char* token);
/*
general
Checks that the day its valid

@param Client* , char* , int*
*/
void checkDay(Client* temp, char* token);
/*
general
Checks that the mmonth its valid

@param Client* , char* , int*
*/
void checkMonth(Client* temp, char* token);
/*
general
Checks that the year its corecte

@param Client* , char* , int*
*/
void checkYear(Client* temp, char* token);
/*
general
Checks that the first name its valid

@param Client* , char* , int*
*/
void checkDebt(Client* temp, char* token);
/*
general
Checking whether the client that the user set, already exists 

@param PList,Client*
*/
void checkIdClient(PList list, Client* temp);
/*
general 
if the two strints are not the same prints an error with the 
specifying the incorrect keyword

@param char oper2, char* token
@return int
*/
int strcomper(char* token, char* str);