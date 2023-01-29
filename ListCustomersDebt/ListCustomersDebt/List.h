#pragma once
#include "Validation.h"
#include "File.h"

/*
general
Creating a new list and initializing the list

@return List
*/
List createNewList();
/*
General
Creates a linked list from the fp file

@param FILE* , List
*/
void readFileAndCreateList(FILE* fp, PList list);
/*
General
Releases the dynamic allocation to the list of struct

@param PList
*/
void freeList(PList list);
/*
General
Releases the dynamic allocation to the struct

@param Client*
*/
void freeClient(Client* ptr);
/*
general
The function assign allocates memory of struct size and resets
it alland checks that the allocation is correct

@return Client*
*/
Client* initializationClient();
/*
general
The function creates a customer and puts him in
a list that is sorted while entering


@param PList , char*
*/
void createsASortedList(PList list, char* str);
/*
general
The function Inserts the customer's letter into a list 
that is sorted while entering

@param PList ,  Client*
*/
void addToSortedList(PList list, Client* temp);
/*
general
The function creates a structure that will contain the new customer

@param PList , char* , PClient* 
*/
void createClient(PList list, char* str, PClient* client);
/*
general
If the customer exists, sum up the debt and update the date

@param  PList, Client** , Client** , Client** 
@return int
*/
int sumSameId(PList list, Client** temp, Client** ptr, Client** prev);
/*
general
Prints the customer received as a parameter with its number in the list

@param Client* , int 
*/
void printClient(Client* client, int i);
/*
general
Prints the customer with error that received as a parameter with its number in the list

@param Client* , int
*/
void printClientErr(Client* client, int  i);
/*
general
Prints the  all List customers 

@param List
*/
void printList(List list);
/*
general
Prints the title of the valid client

@param char*
*/
void printTitles(char* str);
/*
general
Prints the title of the client with errors

@param int*
*/void printTitlesErr(int* wasATitel);
/*
general
Prints the errors that the clients have

@param Client*
*/
void errorToPrint(Client* temp);
/*
general
check if the client exist

@param Client* temp, PList list, char* token
*/
void sameId(Client* temp, PList list, char* token);
Error initializationError();
void checkDate(Client* temp, Client* ptr);