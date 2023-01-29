#pragma once
#include "GeneralData.h"


/*
General
the function opens a new file for reading
and writing - and checks the correctness of the opening

@param FILE** , char* , char** 
*/
void openFile(FILE** fp, char* mode, char** newFile);
/*
General
Reads from a file or from stdin and allocates memory as required

@param FILE* char**
*/
void readFileAndStdinWithMemoryAllocation(FILE* fp, char** str1);

/*
General
the function closes the opened file
and checks the correctness of the closure

@param FILE*
*/
void closeFile(FILE* fp);
/*
General
the function Prints the new received client to the file

@param FILE* , Client* , float 
*/
void printToFile(FILE* fp, Client* temp, float tempDebt);
