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
int correctData(DynArr *rawData, DynArr *rawIdx, DynArr *rawChange, const char *bufFile)
{

	// Local declares 
	DynArr *segData; // Segment of data that is reused and passed to each algo
	DynArr *resultAr; // Dynamic array pointer returned from algorithms 
	FILE *fileptr;
	int iStartIdx; // Starting index 
	int iGlIdx; // Global reusable indexer
	int iEndIdx; // Ending index
	int iStartIdx1 = -99; 
	int iEndIdx1 = -99;
	
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
		
		/* ---------------------------------------------------------- */
		// Pass to the changeslow algorithm
		resultAr = changeslow(segData, getDynArr(rawChange, iGlIdx));
		
		printf("\n\n");
		for(int m = 0; m < sizeDynArr(resultAr); m++)
			printf("%d ", getDynArr(resultAr, m));
		return 44;

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
			// // Write the name of the algo 
			// fprintf(fileptr, "BadEnum\n");
			
			// // Write the results to the file handling the 
			// // case of only one data point in the input set
			// if(iStartIdx1 == 0 && iEndIdx1 == 0)
			// {
				// fprintf(fileptr, "[%d] ", getDynArr(segData, 0));
			// }
			// else 
			// {
				// for(i = 0; i < (iEndIdx1 - iStartIdx1) + 1; i++)
				// {
					// if(i == 0)
					// {
						// fprintf(fileptr, "[%d, ", getDynArr(segData, (iStartIdx1 + i)));
					// }
					// else if(i == (iEndIdx1 - iStartIdx1))
					// {
						// fprintf(fileptr, "%d]", getDynArr(segData, (iStartIdx1 + i)));
					// }
					// else
					// {
						// fprintf(fileptr, "%d, ", getDynArr(segData, (iStartIdx1 + i)));
					// }
				// }
			// }
			
			// // Add a new line and the sum
			// fprintf(fileptr, "\nSum: %d\n\n", iMaxSum);
		}
		
		// Reset the internal indexes 
		iStartIdx1 = iEndIdx1 = -99;
		
		// Close the file 
		fclose(fileptr);
		
		// /* ---------------------------------------------------------- */
		// // Pass to the GOOD enumeration algo 
        // //TODO remove/fix
		// iMaxSum = GoodEnum(segData, &iStartIdx1, &iEndIdx1);

		// // Open the file again in append mode
		// fileptr = fopen(bufFile, "a");
		
		// // Handle bad file open 
		// if (fileptr == NULL)
		// {
			// fprintf(stderr, "Cannot open %s.\n", bufFile);
			// return -99;
		// }
		// else
		// {
			// // Write the name of the algo
			// fprintf(fileptr, "GoodEnum\n");
			
			// // Write the results to the file handling the 
			// // case of only one data point in the input set
			// if(iStartIdx1 == 0 && iEndIdx1 == 0)
			// {
				// fprintf(fileptr, "[%d] ", getDynArr(segData, 0));
			// }
			// else 
			// {
				// for(i = 0; i < (iEndIdx1 - iStartIdx1) + 1; i++)
				// {
					// if(i == 0)
					// {
						// fprintf(fileptr, "[%d, ", getDynArr(segData, (iStartIdx1 + i)));
					// }
					// else if(i == (iEndIdx1 - iStartIdx1))
					// {
						// fprintf(fileptr, "%d]", getDynArr(segData, (iStartIdx1 + i)));
					// }
					// else
					// {
						// fprintf(fileptr, "%d, ", getDynArr(segData, (iStartIdx1 + i)));
					// }
				// }
			// }
			
			// // Add a new line and the sum
			// fprintf(fileptr, "\nSum: %d\n\n", iMaxSum);
		// }
		
		// // Reset the internal indexes 
		// iStartIdx1 = iEndIdx1 = iMaxSum = -99;
		
		// // Reset the tuple 
		// tResults.low = tResults.high = tResults.sum = -99;
		
		// // Close the file 
		// fclose(fileptr);
			
		// /* ---------------------------------------------------------- */
		// // Pass to the divide and conquer algorithm
        // //TODO remove/fix
		// tResults = MSS_DAC(segData, 0, sizeDynArr(segData) - 1);

		// // Open the file again in append mode
		// fileptr = fopen(bufFile, "a");
		
		// // Handle bad file open 
		// if (fileptr == NULL)
		// {
			// fprintf(stderr, "Cannot open %s.\n", bufFile);
			// return -99;
		// }
		// else
		// {
			// // Write the name of the algo
			// fprintf(fileptr, "DVC\n");
			
			// // Write the results to the file handling the 
			// // case of only one data point in the input set
			// if(tResults.low == 0 && tResults.high == 0)
			// {
				// fprintf(fileptr, "[%d] ", getDynArr(segData, 0));
			// }
			// else 
			// {
				// for(i = 0; i < (tResults.high - tResults.low) + 1; i++)
				// {
					// if(i == 0)
					// {
						// fprintf(fileptr, "[%d, ", getDynArr(segData, (tResults.low + i)));
					// }
					// else if(i == (tResults.high - tResults.low))
					// {
						// fprintf(fileptr, "%d]", getDynArr(segData, (tResults.low + i)));
					// }
					// else
					// {
						// fprintf(fileptr, "%d, ", getDynArr(segData, (tResults.low + i)));
					// }
				// }
			// }
			
			// // Add a new line and the sum
			// fprintf(fileptr, "\nSum: %d\n\n", tResults.sum);
		// }
		
		// // Reset the internal indexes 
		// iStartIdx1 = iEndIdx1 = iMaxSum = -99;
		
		// // Reset the tuple 
		// tResults.low = tResults.high = tResults.sum = -99;
		
		// // Close the file 
		// fclose(fileptr);		

		// /* ---------------------------------------------------------- */
		// // Pass to the linear time recurive algo 
		// tResults = lTime(segData);

		// // Open the file again in append mode
		// fileptr = fopen(bufFile, "a");
		
		// // Handle bad file open 
		// if (fileptr == NULL)
		// {
			// fprintf(stderr, "Cannot open %s.\n", bufFile);
			// return -99;
		// }
		// else
		// {
			// // Write the name of the algo
			// fprintf(fileptr, "LinearTime\n");
			
			// // Write the results to the file handling the 
			// // case of only one data point in the input set
			// if(tResults.low == 0 && tResults.high == 0)
			// {
				// fprintf(fileptr, "[%d] ", getDynArr(segData, 0));
			// }
			// else 
			// {
				// for(i = 0; i < (tResults.high - tResults.low) + 1; i++)
				// {
					// if(i == 0)
					// {
						// fprintf(fileptr, "[%d, ", getDynArr(segData, (tResults.low + i)));
					// }
					// else if(i == (tResults.high - tResults.low))
					// {
						// fprintf(fileptr, "%d]", getDynArr(segData, (tResults.low + i)));
					// }
					// else
					// {
						// fprintf(fileptr, "%d, ", getDynArr(segData, (tResults.low + i)));
					// }
				// }
			// }
			
			// // Add a new line and the sum
			// fprintf(fileptr, "\nSum: %d\n\n", tResults.sum);
		// }
		
		// Reset the internal indexes 
		iStartIdx1 = iEndIdx1 = -99;
			
		// Close the file 
		fclose(fileptr);		

		// Clean up the dynamic allocation
		deleteDynArr(segData);
		
		// Set the start position
		iStartIdx = iEndIdx + 1;
	}
	
	// Bounce from the routine 
	return 1;
}

// // Create the experimental runtime results for all 
// // algorithms. Each algorithm will be tested with 
// // 10 samples sizes and 10 runs per sample size and the 
// // average calculated from the ten.
// int expData(const char *filename)
// {
	// // Local declares
	// clock_t cStart, cEnd;
	// double dDuration;
	// double dTotalTime = 0;
	// DynArr *randN; // Array of random integers based on the sample sizes required
	// FILE *fileptr;
	// int sampleSizes[4][10] = 	{
									// {200, 300, 400, 500, 600, 700,  800, 900, 1000, 1100}, 													// Bad enum
									// {500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000},  											// Good enum
									// {500000, 1000000, 1500000, 2000000, 2500000, 3000000,  3500000, 4000000, 4500000, 5000000},  			// DVC
									// {5000000, 10000000, 15000000, 20000000, 25000000, 30000000,  35000000, 40000000, 45000000, 50000000}  	// Linear
								// };

	// int iIdx = -99; // Shared indexer 
	// int jIdx = -99; // Shared indexer
	// int kIdx = -99; // Shared indexer
	// int hIdx = -99; // Shared indexer
	// int iResults = -99; // Shared results 
	// int iStart = -99; // Start passed as ref to algos 
	// int iEnd = -99; // End passed as ref to algos 
	// struct Tuple tResults; // Tuple to hold the results of recursive calls
	
	// // Plant the random number generator seed 
	// srand(time(NULL));
	
	// // Open the file in write mode
	// fileptr = fopen(filename, "w");
	
	// // Handle bad file open 
	// if (fileptr == NULL)
	// {
		// fprintf(stderr, "Cannot open %s.\n", filename);
		// return -99;
	// }
	// else
	// {
		// // Outer loop for each of the algos 
		// for(hIdx = 0; hIdx < 4; hIdx++)
		// {
			// // Write the algo name once 
			// switch(hIdx)
			// {
				// case 0:
					// fprintf(fileptr, "BadEnum\n");
					// break;
				// case 1:
					// fprintf(fileptr, "GoodEnum\n");
					// break;
				// case 2:
					// fprintf(fileptr, "DVC\n");
					// break;
				// case 3:				
					// fprintf(fileptr, "Linear\n");
					// break;
			// }
			
			// // Loop to get each of the sample sizes 
			// for(iIdx = 0; iIdx < 10; iIdx++)
			// {
				// // Get ten samples of the sample size 
				// for(jIdx = 0; jIdx < 10; jIdx++)
				// {
					// // Create an array the size of the sample size from master table
					// randN = createDynArr(sampleSizes[hIdx][iIdx]);
					
					// // Assign random numbers to the array
					// for(kIdx = 0; kIdx < sampleSizes[hIdx][iIdx]; kIdx++)
					// {
						// addDynArr(randN, (rand() % 1000) - 500);
					// }
					
					// // Get the current time 
					// cStart = clock();
					
					// // Pass through the algorithm based on the value of outer loop
					// iResults = 0;
					// switch(hIdx)
					// {
						// case 0:
							// iResults = BadEnum(randN, &iStart, &iEnd);
							// break;
						// case 1:
							// iResults = GoodEnum(randN, &iStart, &iEnd);
							// break;
						// case 2:
							// tResults = MSS_DAC(randN, 0, sizeDynArr(randN) - 1);
							// break;
						// case 3:				
							// tResults = lTime(randN);
							// break;
					// }
					
					// // Remove warning
					// if(iResults == 0 && tResults.sum == 0){}
								
					// // Get the time delta 
					// cEnd = clock();
					// dDuration = (double)(cEnd - cStart) / CLOCKS_PER_SEC;
					// dTotalTime = dTotalTime + dDuration;
					
					// // Write the times to file 
					// fprintf(fileptr, "%f ", dDuration);
					
					// //  Blow out the array
					// deleteDynArr(randN);
				// }
				
				// // Write the average to file
				// fprintf(fileptr, "%f\n\n", dTotalTime / 10);
				
				// // Clean out the total and durations 
				// dDuration = dTotalTime = 0;
			// }
		// }
	// }
	
	// // Close the file 
	// fclose(fileptr);
	
	// // Bounce
	// return 1;
// }
















