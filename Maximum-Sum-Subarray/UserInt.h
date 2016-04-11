/* 	UserInt.h : User interface and other IO. */
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
int fileToAr(const char *filename, DynArr *raw, DynArr *idx); 

#endif
