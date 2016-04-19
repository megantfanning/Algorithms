/* ------------------------------------------------------------------------- *
// Project Name: 	CS325 - Project 2
// File 			Name: Main.c
// Desc: 			Entry point for project.
// Authors:			Ian Dalrymple, Megan Fanning, Toni York
// Date: 			04/25/2016
/* -------------------------------------------------------------------------*/

// Includes 
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "dynamicArray.h"
//#include "UserInt.h"
//#include "Algos.h"

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
	const char* inFile;
	
	// Check for correct command line input from user
    if(argc == 1)
	{	
		// Tell the user what is happening
        printf("Include the file name as an argument to the command line. \n");	
		
		// Return fail to os 
		return -99;
	}
    else if(argc == 2)
	{
		// Get the input file name 
		inFile = argv[1];
		printf("%s ", inFile);
		return 0;
	}


    // //define these variables using file input
    // int A;
    // int V[4]={3,2,1,1,1};

    // //call agorithms
    // //Brute force/Divide and Conquer
    // int Change[]= changeslow(V[],A){}
    // //Greedy
    // int Change[]= changegreedy(V[],A){}
    // //Dynamic
    // int Change[]= changedp(V[],A){}
}


