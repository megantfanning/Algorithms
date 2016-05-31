/* ------------------------------------------------------------------------- */
// Project Name: 	CS325 - Project 1
// File 			Name: UserInt.c
// Desc: 			User interface and other IO functions.
// Authors:			Ian Dalrymple, Megan Fanning, Toni York
// Date: 			05/28/2016
/* ------------------------------------------------------------------------- */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "UserInt.h"
#include "Algos.h"

// Get the number of rows from a file
int fRowCount(const char *filename)
{
	// Local declares 
	FILE *fileptr;
	int iRows = 0;
	int chNext = 0;
	
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
		// Loop and count the number of new lines
		while(!feof(fileptr))
		{
			// Get the next char
			chNext = fgetc(fileptr);
			
			// Check for new line and inc the 
			// counter if a new line 
			if(chNext == '\n')
			{
				iRows++;
			}
		}
	}
	
	// Close the file
	fclose(fileptr);
	fileptr = NULL;
	
	// Send back the number of rows
	return iRows;
}

// Get the current word / number from a file stream
char* getWord(FILE *file, int *iFlag)
{
	// Local declares
	int length = 0;
	int maxLength = 16;
	char character;
	
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
		if((character >= '0' && character <= '9')) 
		{
			word[length] = character;
			length++;
		}
		else if(length > 0)
		{
			*iFlag = *iFlag + 1;
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
	//printf("%s", word);
	return word;
}

// Take a file name, array of structs and the number of elements 
// in the array. Open the file and put the contents into the array. 
// return -99 for failed and 0 for success.
int fileToAr(const char *filename, struct structCity *input, int size)
{
	// Local declares 
	char *curWord;
	FILE *fileptr;
	int iCurInt; // Connvert file char * to int
	int iCurIdx = 0; // Current indexing location to array 
	int iEndArFlag = 0; // Flag to dictate the column of the struct 

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
		// Get the current word for the first time
		curWord = getWord(fileptr, &iEndArFlag);

		// Start reading in the file - the output of this loop is 
		// the array with the raw data and the array of 
		// end positions that is to be used to parse out the smaller 
		// array from within 
		while(curWord != NULL)
		{	
			// Convert to integer
			iCurInt = atoi(curWord);
			
			// Add to the array with location based on 
			// the reference flag passed back and forth
			switch(iEndArFlag)
			{
				case 1:
					input[iCurIdx].iId = iCurInt;
					// printf("ID = %d iEndArFlag = %d iCurIdx = %d", input[iCurIdx].iId, iEndArFlag, iCurIdx);
					break;
				case 2:
					input[iCurIdx].iX = iCurInt;
					// printf("ID = %d iEndArFlag = %d iCurIdx = %d ", input[iCurIdx].iX, iEndArFlag, iCurIdx);
					break;
				case 3:
					input[iCurIdx].iY = iCurInt;
					// printf("ID = %d iEndArFlag = %d iCurIdx = %d\n", input[iCurIdx].iY, iEndArFlag, iCurIdx);
					break;
			}
				
			// Free up the memory
			free(curWord);
				
			// Reset the flag and inc the row indexer
			if(iEndArFlag == 3)
			{
				// Reset the flag
				iEndArFlag = 0;
				
				// Increment the indexer 
				iCurIdx = iCurIdx + 1;
			}
			
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

// Receive array and string for filename and send the array to 
// a newly created file. The first row is the total distance and the 
// subsequent rows are the cities in visitation order.
int outputFile(const char *filename, int *output, int size)
{
	// Local declares 
	FILE *fileptr;

	// Open the file
	fileptr = fopen(filename, "w");
	
	// Handle bad file open 
	if (fileptr == NULL)
	{
  		fprintf(stderr, "Cannot open %s.\n", filename);
		return -99;
	}
	else
	{
		// Loop and write the array the file
		for(int i = 0; i < size; i++)
		{
			fprintf(fileptr, "%d\n", output[i]);
		}
	}
	
	// Close the file
	fclose(fileptr);
	fileptr = NULL;
	
	// Send back the number of rows
	return 0;
}
















