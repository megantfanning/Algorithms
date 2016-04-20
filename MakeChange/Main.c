// ------------------------------------------------------------------------- 
// Project Name: 	CS325 - Project 2
// File 			Name: Main.c
// Desc: 			Entry point for project.
// Authors:			Ian Dalrymple, Megan Fanning, Toni York
// Date: 			04/25/2016
// -------------------------------------------------------------------------

// Includes 
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamicArray.h"
#include "UserInt.h"
#include "Algos.h"

// References 
// valgrind --tool=memcheck --leak-check=yes Change InputTest.txt

/*
The execution of the program(s) should be as follows:
 User runs the programs on the command-line, specifying a file ([input filename].txt) in which the first line containsthe array V, formatted as [1, 5, 10, 25], denominations in increasing order.
 
The next line contains one integer value for which we must make change.
Program output should be written to a file named [input filename]change.txt where [input filename].txt is the input filename, and should be formatted with the name of the algorithm used, the change result and the minimum number of coins m, per line.
*/
// Main Entry Point 
int main (int argc, const char * argv[]) 
{
	// Local declares 
	const char* inFile; // Input file name 
	char outFile[512];  // Output file name 
	char tempStr[512];  // Temp string 
	DynArr *rawData;    // Container for all the arrays stacked on one another
	DynArr *rawIdx;     // Container for the locations of the ] which delimit each array
	DynArr *rawChange;  // Container for the change to be given
	int iResults = -99; // Shared results integer 
	
	// Check for correct command line input from user
    if(argc == 1)
	{	
		// Tell the user what is happening
        printf("Include the file name as an argument to the command line. \n");	
		
		// Return fail to os 
		return -99;
	}
	// Second arg is file name and third is optional and when present will 
	// print the running times to screen
    else if(argc == 2 || argc == 3)
	{
		// Get the input file name 
		inFile = argv[1];
		
		// Get the base input file name less .txt and term with null
		strncpy(tempStr, inFile, strlen(inFile) - 4);
		tempStr[strlen(inFile) - 4] = '\0';
	
		// Construct the output file name 
		snprintf(outFile, sizeof outFile, "%s%s", tempStr, "Change.txt");
				
		// Tell the user what is happening
        printf("Running analysis... results will be saved to %s\n", outFile);
	
		// Constuct arrays for holding results of input file parse
		rawData = createDynArr(5);
		rawIdx = createDynArr(5);
		rawChange = createDynArr(5);
		
		// Get the raw data into arrays with rawData containing all the rows 
		// from the file and rawIdx containing the delimiting positions and the 
		// raw change into rawChange
		iResults = fileToAr(inFile, rawData, rawIdx, rawChange);
		
		// Check results from fileToAr before proceeeding 
		if(iResults < 0)
		{
			// Tell the user what happened and elegantly escape
			printf("Failure in fileToAr method. Contact admin.\n");
			
			// Delete the dynamic arrays 
			deleteDynArr(rawData);
			deleteDynArr(rawIdx);
			deleteDynArr(rawChange);
			
			// Return fail to the OS
			return -99;
		}
		
		// Reset iResults 
		iResults = -99;
		
		// Call the correctness routine 
		iResults = correctData(rawData, rawIdx, rawChange, outFile, argc);
		
		// Check the results of correctData call
		if(iResults < 0)
		{
			// Tell the user what happened
			printf("Failure in correctData method. Contact admin.");
		}
		
		// Delete the dynamic arrays 
		deleteDynArr(rawData);
		deleteDynArr(rawIdx);
		deleteDynArr(rawChange);
	
		// Exit with success to OS 
		return 0;
	}
	else
	{
		// Default case 
		printf("Incorrect number of args. Try again.\n");
		
		// Return fail to the OS
		return -99;
	}
}


