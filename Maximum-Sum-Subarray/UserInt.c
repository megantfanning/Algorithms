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
#include <time.h>
#include "UserInt.h"
#include "dynamicArray.h"
#include "Algos.h"

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

// Create the experimental runtime results for all 
// algorithms. Each algorithm will be tested with 
// 10 samples sizes and 10 runs per sample size and the 
// average calculated from the ten.
int expData(const char *filename)
{
	// Local declares
	clock_t cStart, cEnd;
	double dDuration;
	double dTotalTime = 0;
	DynArr *randN; // Array of random integers based on the sample sizes required
	FILE *fileptr;
	int sampleSizes[4][10] = 	{
									{200, 300, 400, 500, 600, 700,  800, 900, 1000, 1100}, // Bad enum
									{100, 200, 300, 400, 500, 600,  700, 800, 900, 1000},  // Good enum
									{100, 200, 300, 400, 500, 600,  700, 800, 900, 1000},  // DVC
									{100, 200, 300, 400, 500, 600,  700, 800, 900, 1000}   // Linear
								};
	// int badEnumSamples[10] = {200, 300, 400, 500, 600, 700,  800, 900, 1000, 1100};
	//int badEnumSamples[10] = {20, 300, 40, 50, 60, 70,  80, 90, 100, 110}; - Valgrind tester
	//int goodEnumSamples[10] = {100, 200, 300, 400, 500, 600,  700, 800, 900, 1000};
	//int dVCSamples[10] = {100, 200, 300, 400, 500, 600,  700, 800, 900, 1000};
	//int linearSamples[10] = {100, 200, 300, 400, 500, 600,  700, 800, 900, 1000};
	int iIdx = -99; // Shared indexer 
	int jIdx = -99; // Shared indexer
	int kIdx = -99; // Shared indexer
	int hIdx = -99; // Shared indexer
	int iResults = -99; // Shared results 
	int iStart = -99; // Start passed as ref to algos 
	int iEnd = -99; // End passed as ref to algos 
	
	// Plant the random number generator seed 
	srand(time(NULL));
	
	// Open the file in write mode
	fileptr = fopen(filename, "w");
	
	// Handle bad file open 
	if (fileptr == NULL)
	{
		fprintf(stderr, "Cannot open %s.\n", filename);
		return 0;
	}
	else
	{
		// Outer loop for each of the algos 
		for(hIdx = 0; hIdx < 4; hIdx++)
		{
			// Write the algo name once 
			switch(hIdx)
			{
				case 0:
					fprintf(fileptr, "BadEnum\n");
					break;
				case 1:
					fprintf(fileptr, "GoodEnum\n");
					break;
				case 2:
					fprintf(fileptr, "DVC\n");
					break;
				case 3:				
					fprintf(fileptr, "GoodEnum\n");
					break;
			}
			
			// Loop to get each of the sample sizes 
			for(iIdx = 0; iIdx < 10; iIdx++)
			{
				// Get ten samples of the sample size 
				for(jIdx = 0; jIdx < 10; jIdx++)
				{
					// Create an array the size of the sample size from master table
					randN = createDynArr(sampleSizes[hIdx][iIdx]);
					
					// Assign random numbers to the array
					for(kIdx = 0; kIdx < sampleSizes[hIdx][iIdx]; kIdx++)
					{
						addDynArr(randN, rand() % 1000);
					}
					
					// Get the current time 
					cStart = clock();
					
					// Pass through the algorithm 
					iResults = BadEnum(randN, &iStart, &iEnd);
					
					// Get the time delta 
					cEnd = clock();
					dDuration = (double)(cEnd - cStart) / CLOCKS_PER_SEC;
					dTotalTime = dTotalTime + dDuration;
					
					// Write the times to file 
					fprintf(fileptr, "%f ", dDuration);
					
					//  Blow out the array
					deleteDynArr(randN);
				}
				
				// Write the average to file
				fprintf(fileptr, "%f\n\n", dTotalTime / 10);
				
				// Clean out the total and durations 
				dDuration = dTotalTime = 0;
			}
		}
	}
	
	// Close the file 
	fclose(fileptr);
	
	// Bounce
	return -99;
}
















