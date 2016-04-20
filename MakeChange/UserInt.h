// Project Name: 	CS325 - Project 1
// File 			Name: UserInt.h
// Desc: 			User interface and other IO functions.
// Authors:			Ian Dalrymple, Megan Fanning, Toni York
// Date: 			04/10/2016
/* ------------------------------------------------------------------------- */
#include<math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "dynamicArray.h"

#ifndef USERINT_INCLUDED
#define USERINT_INCLUDED 1

// Get the next number / char from a stream 
char* getWord(FILE *file, int *iFlag);

// Get word wrapper containing a loop to 
// repeatedly call getWord and build an array
int fileToAr(const char *filename, DynArr *rawData, DynArr *rawIdx, DynArr *rawChange); 

// Pass the rawData and rawIdx arrays with a file name into function
// that will parse out the child arrays and run through each algorithm 
// and write the results to the file name listed
int correctData(DynArr *rawData, DynArr *rawIdx, const char *bufFile);

// Create the experimental runtime results for all 
// algorithms. Each algorithm will be tested with 
// 10 samples sizes and 10 runs per sample size and the 
// average calculated from the ten.
int expData(const char *filename);

#endif
