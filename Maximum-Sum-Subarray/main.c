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
// Clock time = http://stackoverflow.com/questions/12743063/using-clock-to-measure-execution-time

// Includes 
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "dynamicArray.h"
#include "Algos.h"
#include "UserInt.h"

// Main Entry Point 
int main (int argc, const char * argv[]) 
{
	// Local declares 
	const char* rawFile;
	char bufFile[512];
	DynArr *rawData; // Dynamic array as defined in dynamicArray.h
	DynArr *rawIdx; // Dynamic array as defined in dynamicArray.h
	DynArr *segData; // Segment of data that is reused and passed to each algo
	FILE *fileptr;
	int iResults = -99; // Global reusable results indicator
	int iGlIdx; // Global reusable indexer
	int iStartIdx; // Starting index 
	int iEndIdx; // Ending index 
	int iStartIdx1 = -99; 
	int iEndIdx1 = -99;
	int iMaxSum = -99; // Return from algos - summation
	int iEpoch = (int)time(NULL); // Seconds since epoch 

	// If two args then run the experimental branch 
	// If three args then run the correctness branch on the
	// input file provided. The results are dumped to "Results.txt"
    if(argc == 2 && strcmp(argv[1], "Experimental") == 0)
	{
		// Create the name of the exp results file 
		snprintf(bufFile, sizeof bufFile, "%s%d%s", "Exp", iEpoch, ".txt");
		
		// Call the experimental function 
		iResults = expData(bufFile);
		
		// Bounce
		return 0;
	}
    else if(argc == 3 && strcmp(argv[1], "Correctness") == 0)
	{
		// Create the name of the correctness results file 
		snprintf(bufFile, sizeof bufFile, "%s%d%s", "Results", iEpoch, ".txt");
		
		// Define the name of the file to be parsed 
		rawFile = argv[2];
		
		// This will hold the actual data from the file.
		rawData = createDynArr(5);
		
		// Create a dyamic array to hold the end positions
		// of each array - these are straight indexes 
		rawIdx = createDynArr(5);
		
		// Get the raw data into arrays 
		iResults = fileToAr(rawFile, rawData, rawIdx);
			
		// Get the subarrays from the large array and then pass 
		// to each of the algos and write to file in this loop
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
			
			/* ---------------------------------------------------------- */
			// Pass to the bad enumeration algo 
			iMaxSum = BadEnum(segData, &iStartIdx1, &iEndIdx1);

			// Open the file again in append mode
			fileptr = fopen(bufFile, "a");
			
			// Handle bad file open 
			if (fileptr == NULL)
			{
				fprintf(stderr, "Cannot open %s.\n", bufFile);
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
			iStartIdx1 = iEndIdx1 = iMaxSum = -99;
			
			// Close the file 
			fclose(fileptr);
			
			/* ---------------------------------------------------------- */
			// Pass to the GOOD enumeration algo 
			iMaxSum = GoodEnum(segData, &iStartIdx1, &iEndIdx1);

			// Open the file again in append mode
			fileptr = fopen(bufFile, "a");
			
			// Handle bad file open 
			if (fileptr == NULL)
			{
				fprintf(stderr, "Cannot open %s.\n", bufFile);
				return 0;
			}
			else
			{
				// Write to the file for the single result set
				fprintf(fileptr, "GoodEnum\n");
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
			iStartIdx1 = iEndIdx1 = iMaxSum = -99;
			
			// Close the file 
			fclose(fileptr);
			
			// Clean up the dynamic allocation
			deleteDynArr(segData);
			
			// Set the start position
			iStartIdx = iEndIdx + 1;
		}
		
		// Delete the dynamic arrays 
		deleteDynArr(rawData);
		deleteDynArr(rawIdx);
		
		// Bounce
		return 0;
	}
	else
	{
		// Default case 
		printf("Incorrect number of args. Try again.\n");
		
		// Bounce
		return 0;
	}
}
