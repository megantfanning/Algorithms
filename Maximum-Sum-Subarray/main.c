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
	int iResults = -99; // Global reusable results indicator
	int iEpoch = (int)time(NULL); // Seconds since epoch 

	// DynArr *tester;
	// // [10, -11, -1, -9, 33, -45, 23, 24, -1, -7, -8, 19] 
	// tester = createDynArr(9);
	// addDynArr(tester, 10);
	// addDynArr(tester, -11);
	// addDynArr(tester, -1);	
	// addDynArr(tester, -9);
	// addDynArr(tester, 33);
	// addDynArr(tester, -45);	
	// addDynArr(tester, 23);
	// addDynArr(tester, 24);
	// addDynArr(tester, -1);
	// addDynArr(tester, -7);
	// addDynArr(tester, -8);
	// addDynArr(tester, 19);
	
	// struct Tuple ianTuple = lTime(tester);
	// printf("%d %d %d ", ianTuple.low, ianTuple.high, ianTuple.sum);
	// return 6;
	
	// If two args then run the experimental branch 
	// If three args then run the correctness branch on the
	// input file provided. The results are dumped to "Results.txt"
    if(argc == 2 && strcmp(argv[1], "Experimental") == 0)
	{
		// Create the name of the exp results file 
		snprintf(bufFile, sizeof bufFile, "%s%d%s", "Exp", iEpoch, ".txt");
		
		// Call the experimental function 
		iResults = expData(bufFile);
		
		// Check results from expData call 
		if(iResults < 0)
		{
			// Tell the user what happened 
			printf("Failure inside expData method. Contact admin.");
		}
		
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
		
		// Get the raw data into arrays with rawData 
		// containing all the rows from the file and rawIdx
		// containing the delimiting positions
		iResults = fileToAr(rawFile, rawData, rawIdx);
		
		// Check results from fileToAr before proceeeding 
		if(iResults < 0)
		{
			// Tell the user what happened and elegantly escape
			printf("Failure in fileToAr method. Contact admin.");
			
			// Delete the dynamic arrays 
			deleteDynArr(rawData);
			deleteDynArr(rawIdx);
			
			// Bounce
			return 0;
		}
		
		// Reset iResults 
		iResults = -99;
		
		// Call the correctness routine 
		iResults = correctData(rawData, rawIdx, bufFile);

		// Check the results of correctData call
		if(iResults < 0)
		{
			// Tell the user what happened
			printf("Failure in correctData method. Contact admin.");
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
