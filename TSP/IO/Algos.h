/* ------------------------------------------------------------------------- */
// Project Name: 	CS325 - Project 1
// File 			Name: Algos.h
// Desc: 			Algorithms for finding the shortest round trip for salesman.
// Authors:			Ian Dalrymple, Megan Fanning, Toni York
// Date: 			05/28/2016
/* ------------------------------------------------------------------------- */
#include<math.h>
#include "StructDef.h"

#ifndef ALGOS_INCLUDED
#define ALGOS_INCLUDED 1

// Algorithm to get the shortest round trip for the 
// input array passed in. The algorithm should populate 
// the output array that is passed in with the first row 
// being the total distance and then the subseuent rows 
// being the cities in the order they are to be visited.
// The size parameter is the number of cities.
int resultTSP(struct structCity *input, int *output, int size);

#endif
