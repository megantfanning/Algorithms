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
	int *outputList1 = NULL; // Results array 
	int *outputList2 = NULL; // Results array 
	int rowSize = -99; // Number of cities 
	int emptyCounter = 0; // Rows that are empty

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
	
	// Check if row size is correct
	if(rowSize < 0)
	{
		printf("Row size could not be determined.\n");
		return -99;
	}

	// Spin up the input array that will house the raw data from
	// the file directly 
	inputList = malloc(rowSize * sizeof(*inputList));
	
	// Init the inputlist 
	for(int i = 0; i < rowSize; i++)
	{
		inputList[i].iId = -99;
	}

	// Spin up the output array that will house the results. 
	// This array can be used to output to file as required. 
	// The array contains one extra row for the total distance
	// travelled which is the first row.
	outputList1 = malloc((rowSize + 1) * sizeof(*outputList1));
    outputList2 = malloc((rowSize + 1) * sizeof(*outputList2));

	// Get the raw data into the input array 
	int inputResults = fileToAr(rawFile, inputList, rowSize);
	
	// Check if the data got from file to array 
	if(inputResults < 0)
	{
		printf("File not read into input array.\n");
		return -99;
	}
	
	// Check the total number of data in the input array and 
	// adjust the row count accordingly
	for(int i = rowSize - 1; i >= 0; i--)
	{
		if(inputList[i].iId != i)
		{
			emptyCounter++;
		}
		else
		{
			break;
		}
	}
	
	// Adjust the row size 
	rowSize = rowSize - emptyCounter;
	
	// Start the clock 
	timer = clock();
	
    //generate two sets of results and compare
    resultTSP(inputList, outputList1, rowSize,0);

	// Run algo multiple times and choose best run
    int start=10;
    int better=1;
    
    if(rowSize<1000){
        for(int i=1;i<50;i++){
            if(better==1){
                resultTSP(inputList, outputList2, rowSize,start);
            }else{
                resultTSP(inputList, outputList1, rowSize,start);
            }
            start+=1;
        
            if(outputList1[0]>outputList2[0]){
                better=2;
            }else{
                better=1;
            }
        }
    }    
	
	// Get the running time 
	timer = clock() - timer;

	// Push the output array to output file
    if(better==1)
	{
	    if((outputFile(outFile, outputList1, rowSize + 1)) < 0){
            printf("Error writing output file");
            free(inputList);
		    free(outputList1);
		    free(outputList2);
            return 1; 
        }
    }
	else
	{
        if((outputFile(outFile, outputList2, rowSize + 1)) < 0){
            printf("Error writing output file");
		    free(inputList);
		    free(outputList1);
		    free(outputList2);
            return 1;
        }
    }
	
	// Print the running time and bounce
	printf("Whole program ran in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
	
	// Free up memory 
	free(inputList);
	free(outputList1);
	free(outputList2);

	// Return to OS
	return 0;
}
