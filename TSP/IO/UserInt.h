// Project Name: 	CS325 - Project 1
// File 			Name: UserInt.h
// Desc: 			User interface and other IO functions.
// Authors:			Ian Dalrymple, Megan Fanning, Toni York
// Date: 			05/28/2016
/* ------------------------------------------------------------------------- */
#include<math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "StructDef.h"

#ifndef USERINT_INCLUDED
#define USERINT_INCLUDED 1

// Get the number of rows in input file 
// The number of rows is the number 
// of cities
int fRowCount(const char *filename);

// Get the next number / char from a stream 
char* getWord(FILE *file, int *iFlag);

// Get word wrapper containing a loop to 
// repeatedly call getWord and build arrays - one for 
// the city id, one for the x and one for the y 
int fileToAr(const char *filename, struct structCity *input, int size); 

// Receive array and string for filename and send the array to 
// a newly created file. The first row is the total distance and the 
// subsequent rows are the cities in visitation order.
int outputFile(const char *filename, int *output, int size);

#endif
