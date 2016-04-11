/* ------------------------------------------------------------------------- */
// Project Name: 	CS325 - Project 1
// File 			Name: UserInt.c
// Desc: 			User interface and other IO functions.
// Authors:			Ian Dalrymple, Megan Fanning, Toni York
// Date: 			04/10/2016
/* ------------------------------------------------------------------------- */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "UserInt.h"
#include "dynamicArray.h"

// Get the current word / number from a file stream
char* getWord(FILE *file, int *iFlag)
{
	// Local declares
	int length = 0;
	int maxLength = 16;
	char character;
	
	// Init the flag in case the client is sloppy 
	*iFlag = 0;
	
	// Initial allocation
	char* word = malloc(sizeof(char) * maxLength);
	assert(word != NULL);

	while((character = fgetc(file)) != EOF)
	{
		// Create larger array if overgrown
		if((length + 1) > maxLength)
		{
			maxLength *= 2;
			word = (char*)realloc(word, maxLength);
		}
		
		// Grab only the chars we want and break otherwise
		// Set flag if the character is ] which indicates a 
		// new array is about to start.
		if((character >= '0' && character <= '9') || 
		   character == '-') 
		{
			word[length] = character;
			length++;
		}
		else if(length > 0)
		{
			if(character == ']')
				*iFlag = 1;
			break;
		}
	}
	
	// Clean up local memory
	if(length == 0)
	{
		free(word);
		return NULL;
	}
	
	// Assign explicit null termination
	word[length] = '\0';
	
	// Return the word 
	return word;
}

// Take a file name and two dynamic arrays and repeatedly 
// call the getWord function creating a data array of 
// all the raw values from the file and a supplemental 
// array containing all the locations of "]" chars which 
// represent the end of each array. Return 1 for good and -99 
// for bad.
int fileToAr(const char *filename, DynArr *rawData, DynArr *rawIdx)
{
	// Local declares 
	char *curWord;
	FILE *fileptr;
	int iCurInt; // Connvert file char * to int
	int iEndArFlag = 0; // Flag for end of array 1 = end 0 = not end
	
	// Tell the user whats happening 
    printf("\nOpening file: %s.\n", filename);
	
	// Open the file
	fileptr = fopen(filename, "r");
	
	// Handle bad file open 
	if (fileptr == NULL)
	{
  		fprintf(stderr, "Cannot open %s.\n", filename);
		return -99;
	}
	else
	{
		// Get the current word
		curWord = getWord(fileptr, &iEndArFlag);
		
		// Start reading in the file - the output of this loop is 
		// the array with the raw data and the array of 
		// end positions that is to be used to parse out the smaller 
		// array from within 
		while(curWord != NULL)
		{	
			// Convert to integer
			iCurInt = atoi(curWord);
			
			// Add to the dynamic array
			addDynArr(rawData, iCurInt);
			
			// Check to see if at the end and add accordingly
			if(iEndArFlag == 1)
				addDynArr(rawIdx, sizeDynArr(rawData) - 1);
			
			// Free up the memory 
			free(curWord);
				
			// Reset the flag 
			iEndArFlag = 0;
			
			// Get the current word
			curWord = getWord(fileptr, &iEndArFlag);
		}
	}

	// Close the file
	fclose(fileptr);
	fileptr = NULL;
	
	// Bounce 
	return 1;
}


















