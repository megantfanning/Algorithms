/* ------------------------------------------------------------------------- */
// Project Name: 	CS325 - Project 1
// File 			Name: Algos.c
// Desc: 			Algorithms for finding the shortest round trip for salesman.
// Authors:			Ian Dalrymple, Megan Fanning, Toni York
// Date: 			05/28/2016
/* ------------------------------------------------------------------------- */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "Algos.h"

// Algorithm to get the shortest round trip for the 
// input array passed in. The algorithm should populate 
// the output array that is passed in with the first row 
// being the total distance and then the subseuent rows 
// being the cities in the order they are to be visited, The 
// size parameter is the number of cities.
int resultTSP(struct structCity *input, int *output, int size)
{
	// Dummy populate the result array 
	for(int i = 0; i < size + 1; i++)
	{
		if(i == 0)
		{
			output[0] = 78932;
		}
		else 
		{
			output[i] = input[i - 1].iY;
		}
	}
	
	return 0;
}
