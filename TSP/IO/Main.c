/* ------------------------------------------------------------------------- */
// Project Name: 	CS325 - Project 4
// File 			Name: main.c
// Desc: 			Entry point for project. Contains user interface 
//					and file parsing. Also invokes the main algorithmic 
//					solver function for TSP.
//
// Authors:			Ian Dalrymple, Megan Fanning, Toni York
// Date: 			05/27/2016
/* ------------------------------------------------------------------------- */

// References
// Valgrind = http://www.cprogramming.com/debugging/valgrind.html 
// valgrind --tool=memcheck program_name
// Compile = http://www.cyberciti.biz/faq/compiling-c-program-and-creating-executable-file/
// File IO = http://www.programiz.com/c-programming/c-file-examples
// Clock time = http://stackoverflow.com/questions/12743063/using-clock-to-measure-execution-time

// Includes 
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Algos.h"
#include "UserInt.h"
#include "StructDef.h"

// Main Entry Point 
int main (int argc, const char * argv[]) 
{
	// Local declares 
	clock_t timer;
	const char* rawFile; // Input file name handler
	char outFile[512];  // Output file name 
	struct structCity *inputList = NULL; // List of input data 
	int *outputList = NULL; // Results array 
	int iResults = -99; // Global reusable results indicator
	int rowSize = -99; // Number of cities 

	// The argument from the command line is the file to be 
	// parsed and contains the city id followed by the coords (x, y)
    if(argc == 2)
	{
		// Assign the input file name
		rawFile = argv[1];
	
		// Construct the output file name 
		snprintf(outFile, sizeof outFile, "%s%s", rawFile, ".tour");
	}
	else
	{
		// Wrong number of arguments
		printf("Incorrect number of args. Try again.\n");
		return 99;
	}
	
	// Get the number of rows in the file
	rowSize = fRowCount(rawFile);

	// Spin up the input array that will house the raw data from
	// the file directly 
	inputList = malloc(rowSize * sizeof(*inputList));

	// Spin up the output array that will house the results. 
	// This array can be used to output to file as required. 
	// The array contains one extra row for the total distance
	// travelled which is the first row.
	outputList = malloc((rowSize + 1) * sizeof(*outputList));
	
	// Get the raw data into the input array 
	iResults = fileToAr(rawFile, inputList, rowSize);
	
	// Reset the global integer return
	iResults = -99;
	
	// Start the clock 
	timer = clock();
	
	// Call the algorithmic solver function start with 0
	iResults = resultTSP(inputList, outputList, rowSize,0);
    //TODO check here for comparison	
    //tourComparsion(int *output,int length){

	// Reset the results integer
	iResults = -99;
	
	// Push the output array to output file
	iResults = outputFile(outFile, outputList, rowSize + 1);
	
	// Conditional iResults 
	if(iResults == 0)
	{
		iResults = 9;
	}
	
	// Get the running time 
	timer = clock() - timer;
	
	// Print the running time and bounce
	printf("Whole program ran in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
	
	// Free up memory 
	free(inputList);
	free(outputList);

	// Return to OS
	return 0;
}
