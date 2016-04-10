/* ------------------------------------------------------------------------- */
// Project Name: 	CS325 - Project 1
// File 			Name: main.c
// Desc: 			Entry point for project. Contains user interface 
//					and file parsing. Also invokes the maximum sub array 
//					algorithms.
// Authors:			Ian Dalrymple, Megan Fanning, Antonina (Toni) York
// Date: 			04/10/2016
/* ------------------------------------------------------------------------- */

// delete me, this is just testing git from my tablet - TY

// References
// Valgrind = http://www.cprogramming.com/debugging/valgrind.html 
// Compile = http://www.cyberciti.biz/faq/compiling-c-program-and-creating-executable-file/

// Includes 
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dynamicArray.h"

// Header declare 
char* getWord(FILE *file, int *iFlag);

// Main Entry Point 
int main (int argc, const char * argv[]) {
	
	// Local declares 
	const char* filename;
	int iCounter = 0; // Debug only 
	clock_t timer; 
	FILE *fileptr;
	char *curWord;
	int iEndArFlag = 0; // Flag for end of array 1 = end 0 = not end
	int iCurInt; // Connvert file char * to int
	DynArr *b; // Dynamic array as defined in dynamicArray.h
	
	// Create a dynamic aray with 100 elements
	b = createDynArr(5);
		
	// Get the file name to be processed from command line
	// or else just use a default 
    if(argc == 2)
        filename = argv[1];
    else
        filename = "MSS_TestProblems.txt"; 

	// Tell the user whats happening 
    printf("Opening file: %s.\n\n", filename);
	
	// Start the clock 
	timer = clock();

	// Open the file
	fileptr = fopen(filename, "r");
	
	// Handle bad file open 
	if (fileptr == NULL)
	{
  		fprintf(stderr, "Cannot open %s.\n", filename);
		return 0;
	}
	else
	{
		// Get the current word
		curWord = getWord(fileptr, &iEndArFlag);

		// Start reading in the file
		while(curWord != NULL)
		{	
			// Debug counter 
			iCounter = iCounter + 1;
			
			// Convert to integer
			iCurInt = atoi(curWord);
			
			// Add to the dynamic array
			addDynArr(b, iCurInt);
			
			// Debug printer statement 
			printf("Current word: %s     %d     %d     %d\n", curWord, iCounter, iEndArFlag, iCurInt);
			
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

	// Print out the dynamic array - debug only 
	int i = 0;
	for(i = 0; i < sizeDynArr(b); i++)
	{
		printf("%d\n", getDynArr(b, i));
	}
	
	// Get the running time 
	timer = clock() - timer;
	
	// Print the running time and bounce
	printf("\nWhole program ran in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
	return 0;
}

 /* getWord function takes a FILE pointer and returns a string which was
 the next word in the in the file. Words are defined (by this function) to be
 characters or numbers seperated by periods, spaces, or newlines.
 When there are no more words in the input file this function will return NULL.
 This function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it. */
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
