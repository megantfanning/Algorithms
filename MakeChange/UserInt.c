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
#include <sys/time.h>
#include "UserInt.h"
#include "dynamicArray.h"
#include "Algos.h"

// Struct supporting nano timestamps
struct timeval GetTimeStamp() 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv;
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
int fileToAr(const char *filename, DynArr *rawData, DynArr *rawIdx, DynArr *rawChange)
{
	// Local declares 
	char *curWord;
	FILE *fileptr;
	int iCurInt; // Connvert file char * to int
	int iEndArFlag = 0; // Flag for end of array 1 = end 0 = not end
		
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
			
			// Switch based on flag 0) Regular add to raw 
			// 1) At the end of an array so add to idx
			// 2) Change to add to change 
			switch(iEndArFlag)
			{
				case 0:
					// Add to the dynamic array
					addDynArr(rawData, iCurInt);
					
					// Exit control
					break;
						
				case 1:
					// Add to the dynamic array
					addDynArr(rawData, iCurInt);
				
					// Add to the index array with the position of ]
					addDynArr(rawIdx, sizeDynArr(rawData) - 1);
					
					// Set the flag 
					iEndArFlag = 2;
					
					// Exit control
					break;
					
				case 2:
					// Add to the change array 
					addDynArr(rawChange, iCurInt);
					
					// Reset the flag 
					iEndArFlag = 0;
					
					// Exit control
					break;
			}
			
			// Free up the memory 
			free(curWord);
				
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

// Pass the rawData, rawIdx and rawChange arrays with a file name into function
// that will parse out the child arrays and run through each algorithm 
// and write the results to the file name listed 
int correctData(DynArr *rawData, DynArr *rawIdx, DynArr *rawChange, 
								const char *bufFile, int iTimerFlag)
{
	// Local declares 
	clock_t cStart, cEnd;
	double dDuration = -99;
	DynArr *segData; // Segment of data that is reused and passed to each algo
	DynArr *resultAr; // Dynamic array pointer returned from algorithms 
	FILE *fileptr;
	int iStartIdx; // Starting index 
	int iGlIdx; // Global reusable indexer
	int iEndIdx; // Ending index
	int iSumCoins = -99; // Sum of coins used 
	struct timeval tvStart;
	struct timeval tvEnd;
	unsigned long lDuration = -99;
		
	// Get the subarrays from the large array and then pass 
	// to each of the algos and write to file in this loop
	iStartIdx = 0; 
	for(iGlIdx = 0; iGlIdx < sizeDynArr(rawIdx); iGlIdx++)
	{
		// Get the last index for each array in the master array rawData
		iEndIdx = getDynArr(rawIdx, iGlIdx);
		
		// Create a reusable dynamic array
		segData = createDynArr((iEndIdx - iStartIdx) + 1);

		// Loop to add the elements to the new array 
		int i = 0;
		for(i = 0; i < (iEndIdx - iStartIdx) + 1; i++)
		{
			addDynArr(segData, getDynArr(rawData, iStartIdx + i));
		}
		
		/* changeslow --------------------------------------- */
		// Get the current time 
		// cStart = clock();
		tvStart = GetTimeStamp();
		
		// Pass to the changeslow algorithm
		resultAr = changeslow(segData, getDynArr(rawChange, iGlIdx));
		
		// Get the time delta 
		// cEnd = clock();
		tvEnd = GetTimeStamp();
		
		// dDuration = (double)(cEnd - cStart) / CLOCKS_PER_SEC;
		// dDuration = (double)(cEnd - cStart);
		lDuration = (1000000 * tvEnd.tv_sec + tvEnd.tv_usec) -
			(1000000 * tvStart.tv_sec + tvStart.tv_usec);
	
		// Open the file again in append mode
		fileptr = fopen(bufFile, "a");
		
		// Handle bad file open 
		if (fileptr == NULL)
		{
			fprintf(stderr, "Cannot open %s.\n", bufFile);
			return -99;
		}
		else
		{
			// Write the name of the algo 
			fprintf(fileptr, "Algorithm changeslow:\n");
			
			// Loop out the results from the returned array from algorithm
			iSumCoins = 0;
			for(i = 0; i < sizeDynArr(resultAr); i++)
			{
				if(i == 0)
				{
					fprintf(fileptr, "[%d, ", getDynArr(resultAr, i));
				}
				else if(i == sizeDynArr(resultAr) - 1)
				{
					fprintf(fileptr, "%d]", getDynArr(resultAr, sizeDynArr(resultAr) - 1));
				}
				else
				{
					fprintf(fileptr, "%d, ", getDynArr(resultAr, i));
				}
				
				// Inc the sum counter 
				iSumCoins = iSumCoins + getDynArr(resultAr, i);
			}
			
			// Add a new line and the sum
			fprintf(fileptr, "\n%d\n\n", iSumCoins);
			
			// Print the time if needed
			if(iTimerFlag == 3)
			{
				printf("%s: %d %lu\n", "changeslow", iSumCoins, lDuration);
			}
		}
		
		// Reset the sum counter 
		iSumCoins = -99;
		
		// Clean out the result array 
		for(i = 0; i < sizeDynArr(resultAr); i++)
			putDynArr(resultAr, i, 0);
		
		// Delete the result array 
		deleteDynArr(resultAr);
		
		// Close the file 
		fclose(fileptr);		

		/* GREEDY --------------------------------------- */
		// Get the current time 
		// cStart = clock();
		tvStart = GetTimeStamp();
		
		// Pass to the changeslow algorithm
		resultAr = changegreedy(segData, getDynArr(rawChange, iGlIdx));
		
		// Get the time delta 
		// cEnd = clock();
		tvEnd = GetTimeStamp();
		
		// dDuration = (double)(cEnd - cStart) / CLOCKS_PER_SEC;
		// dDuration = (double)(cEnd - cStart);
		lDuration = (1000000 * tvEnd.tv_sec + tvEnd.tv_usec) -
					(1000000 * tvStart.tv_sec + tvStart.tv_usec);
	
		// Open the file again in append mode
		fileptr = fopen(bufFile, "a");
		
		// Handle bad file open 
		if (fileptr == NULL)
		{
			fprintf(stderr, "Cannot open %s.\n", bufFile);
			return -99;
		}
		else
		{
			// Write the name of the algo 
			fprintf(fileptr, "Algorithm changegreedy:\n");
			
			// Loop out the results from the returned array from algorithm
			iSumCoins = 0;
			for(i = 0; i < sizeDynArr(resultAr); i++)
			{
				if(i == 0)
				{
					fprintf(fileptr, "[%d, ", getDynArr(resultAr, i));
				}
				else if(i == sizeDynArr(resultAr) - 1)
				{
					fprintf(fileptr, "%d]", getDynArr(resultAr, sizeDynArr(resultAr) - 1));
				}
				else
				{
					fprintf(fileptr, "%d, ", getDynArr(resultAr, i));
				}
				
				// Inc the sum counter 
				iSumCoins = iSumCoins + getDynArr(resultAr, i);
			}
			
			// Add a new line and the sum
			fprintf(fileptr, "\n%d\n\n", iSumCoins);
			
			// Print the time if needed
			if(iTimerFlag == 3)
			{
				printf("%s: %d %lu\n", "changegreedy", iSumCoins, lDuration);
			}
		}
		
		// Reset the sum counter 
		iSumCoins = -99;
		
		// Clean out the result array 
		for(i = 0; i < sizeDynArr(resultAr); i++)
			putDynArr(resultAr, i, 0);
		
		// Delete the result array 
		deleteDynArr(resultAr);
		
		// Close the file 
		fclose(fileptr);		
		
		/* DYNAMIC PROGRAMMING --------------------------------------- */
		// Get the current time 
		// cStart = clock();
		tvStart = GetTimeStamp();
		
		// Pass to the changeslow algorithm
		resultAr = changedp(segData, getDynArr(rawChange, iGlIdx));
		
		// Get the time delta 
		// cEnd = clock();
		tvEnd = GetTimeStamp();
		
		// dDuration = (double)(cEnd - cStart) / CLOCKS_PER_SEC;
		// dDuration = (double)(cEnd - cStart);
		lDuration = (1000000 * tvEnd.tv_sec + tvEnd.tv_usec) -
				(1000000 * tvStart.tv_sec + tvStart.tv_usec);
	
		// Open the file again in append mode
		fileptr = fopen(bufFile, "a");
		
		// Handle bad file open 
		if (fileptr == NULL)
		{
			fprintf(stderr, "Cannot open %s.\n", bufFile);
			return -99;
		}
		else
		{
			// Write the name of the algo 
			fprintf(fileptr, "Algorithm changedp:\n");
			
			// Loop out the results from the returned array from algorithm
			iSumCoins = 0;
			for(i = 0; i < sizeDynArr(resultAr); i++)
			{
				if(i == 0)
				{
					fprintf(fileptr, "[%d, ", getDynArr(resultAr, i));
				}
				else if(i == sizeDynArr(resultAr) - 1)
				{
					fprintf(fileptr, "%d]", getDynArr(resultAr, sizeDynArr(resultAr) - 1));
				}
				else
				{
					fprintf(fileptr, "%d, ", getDynArr(resultAr, i));
				}
				
				// Inc the sum counter 
				iSumCoins = iSumCoins + getDynArr(resultAr, i);
			}
			
			// Add a new line and the sum
			fprintf(fileptr, "\n%d\n\n", iSumCoins);
			
			// Print the time if needed
			if(iTimerFlag == 3)
			{
				printf("%s: %d %lu\n", "changedp", iSumCoins, lDuration);
			}
		}
		
		// Reset the sum counter 
		iSumCoins = -99;
		
		// Clean out the result array 
		for(i = 0; i < sizeDynArr(resultAr); i++)
			putDynArr(resultAr, i, 0);
		
		// Close the file 
		fclose(fileptr);				

		// Clean up the dynamic allocation
		deleteDynArr(segData);
		deleteDynArr(resultAr);
		
		// Set the start position
		iStartIdx = iEndIdx + 1;
	}
	
	// Bounce from the routine 
	return 1;
}

















