/* ------------------------------------------------------------------------- */
// Project Name: 	CS325 - Project 1
// File 			Name: main.c
// Desc: 			Entry point for project. Contains user interface 
//					and file parsing. Also invokes the maximum sub array 
//					algorithms.
// Authors:			Ian Dalrymple, Megan Fanning, Toni York
// Date: 			04/10/2016
/* ------------------------------------------------------------------------- */

// References
// Valgrind = http://www.cprogramming.com/debugging/valgrind.html 
// Compile = http://www.cyberciti.biz/faq/compiling-c-program-and-creating-executable-file/
// File IO = http://www.programiz.com/c-programming/c-file-examples

// Includes 
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dynamicArray.h"
#include "Algos.h"
#include "UserInt.h"

// Main Entry Point 
int main (int argc, const char * argv[]) {
	
	// Local declares 
	char *curWord;
	clock_t timer; 
	const char* filename;
	const char* resultsFile = "Results.txt";
	DynArr *rawData; // Dynamic array as defined in dynamicArray.h
	DynArr *rawIdx; // Dynamic array as defined in dynamicArray.h
	DynArr *segData; // Segment of data that is reused and passed to each algo
	FILE *fileptr;
	int iCounter = 0; // Debug only 
	int iEndArFlag = 0; // Flag for end of array 1 = end 0 = not end
	int iCurInt; // Connvert file char * to int
	int iGlIdx; // Global reusable indexer
	int iStartIdx; // Starting index 
	int iEndIdx; // Ending index 
	int iStartIdx1 = -99; 
	int iEndIdx1 = -99;
	int iMaxSum; // Return from algos - summation

	// Create a dynamic aray with just a few elements 
	// This will hold the actual data from the file.
	rawData = createDynArr(5);
	
	// Create a dyamic array to hold the end positions
	// of each array - these are straight indexes 
	rawIdx = createDynArr(5);
		
	// Get the file name to be processed from command line
	// or else just use a default 
    if(argc == 2)
        filename = argv[1];
    else
        filename = "MSS_TestProblems.txt"; 

	// Tell the user whats happening 
    printf("\nOpening file: %s.\n", filename);
	
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

		// Start reading in the file - the output of this loop is 
		// the array with the raw data and the array of 
		// end positions that is to be used to parse out the smaller 
		// array from within 
		while(curWord != NULL)
		{	
			// Debug counter 
			iCounter = iCounter + 1;
			
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
	
	// Pass to each of the algorithms under study 
	iStartIdx = 0; 
	for(iGlIdx = 0; iGlIdx < sizeDynArr(rawIdx); iGlIdx++)
	{
		// Get the last index 
		iEndIdx = getDynArr(rawIdx, iGlIdx);
		
		// Create a reusable dynamic array
		segData = createDynArr((iEndIdx - iStartIdx) + 1);

		// Loop to add the elements to the new array 
		int i = 0;
		for(i = 0; i < (iEndIdx - iStartIdx) + 1; i++)
		{
			addDynArr(segData, getDynArr(rawData, iStartIdx + i));
		}
		
		// Pass to the algos
		iMaxSum = BadEnum(segData, &iStartIdx1, &iEndIdx1);

		// Open the file again in append mode
		fileptr = fopen(resultsFile, "a");
		
		// Handle bad file open 
		if (fileptr == NULL)
		{
			fprintf(stderr, "Cannot open %s.\n", resultsFile);
			return 0;
		}
		else
		{
			// Write to the file for the single result set
			fprintf(fileptr, "BadEnum\n");
			for(i = 0; i < (iEndIdx1 - iStartIdx1) + 1; i++)
			{
				if(i == 0)
				{
					fprintf(fileptr, "[%d, ", getDynArr(segData, (iStartIdx1 + i)));
				}
				else if(i == (iEndIdx1 - iStartIdx1))
				{
					fprintf(fileptr, "%d]", getDynArr(segData, (iStartIdx1 + i)));
				}
				else
				{
					fprintf(fileptr, "%d, ", getDynArr(segData, (iStartIdx1 + i)));
				}
			}
			
			// Add a new line and the sum
			fprintf(fileptr, "\nSum: %d\n\n", iMaxSum);
		}
		
		// Reset the internal indexes 
		iStartIdx1 = iEndIdx1 = -99;
		
		// Close the file 
		fclose(fileptr);
		
		// Clean up the dynamic allocation
		deleteDynArr(segData);
		
		// Set the start position
		iStartIdx = iEndIdx + 1;
	}
	
	// Get the running time 
	timer = clock() - timer;
	
	// Delete the dynamic arrays 
	deleteDynArr(rawData);
	deleteDynArr(rawIdx);
	
	// Print the running time and bounce
	printf("\n\nWhole program ran in %f seconds\n\n", (float)timer / (float)CLOCKS_PER_SEC);
	return 0;
}
