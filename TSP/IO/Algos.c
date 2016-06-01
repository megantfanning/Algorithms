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



int getDistance(struct structCity A, struct structCity B){
    //get distance between two cities
    int x=A[x]-B[x];//subtract x coordinates
    int y=A[x]-B[y];//subtract y coordinates
    int dist=pow(y,2)+pow(x,2);// raise both to the power of two and add
    int distance=sqrt(dist);//sqrt of the sum of x^2+y^2
    distance=nearestint(distance);//round to nearest int
    return Distance;
}


int NearestNeightbor(struct structCity *input, int *output, int size){

    //start on an arbitrary vertex as current vertex.
    //2. find out the shortest edge connecting current vertex and an unvisited vertex V.
    //set current vertex to V.
    //mark V as visited.
    //if all the vertices in domain are visited, then terminate.
    //else Go to step 2.
}

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
