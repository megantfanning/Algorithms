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

//get the distance between two cities
int getDistance(struct structCity A, struct structCity B){
    //get distance between two cities
    int x=A.iX-B.iX;//subtract x coordinates
    int y=A.iY-B.iY;//subtract y coordinates
    double dist=pow(y,2)+pow(x,2);// raise both to the power of two and add
    double distance=sqrt(dist);//sqrt of the sum of x^2+y^2
    //note: use rint or nearby int for rounding
    int myDistance=nearbyint(distance);//round to nearest int
    return myDistance;
}

//Create a list of all neighboring Cities and then find the closest neighbor
struct structCity findNeighbors(struct structCity currentCity, int max){
    //TODO
    //make a list of all adjcent cities
    struct structCity cityList[max];

    int numberOfNeighbors=0;
    //create a array to store distances
    int distances[numberOfNeighbors];
 
    for(int i=0; i<max;i++){
        //get the distance between city and neighbor then store to an array
        distances[i]=getDistance(currentCity, cityList[i]);
    }
    //compare ints in array to find smallest one? 
    //TODO make comparison more effective. 
    struct structCity nearestNeighbor;
    return nearestNeighbor;
}

int NearestNeightbor(struct structCity *input, int *output, int size){
    int counter=0;
    //create an array for visited cities
    struct structCity visitedCities[size];
    //bzero(visitedCities);TODO

    //start on an arbitrary vertex as current vertex.
    visitedCities[counter]=input[0];
    counter++;
    
    //if all the vertices in domain are visited, then terminate.
    while(counter<size){
        //TODO 10 is a dummy value
        int maxNeighbors=10;//maximum number of neighbors used to initialze list size
        //find out the shortest edge connecting current vertex 
        //and an unvisited vertex V.set current vertex to V.
        struct structCity V=findNeighbors(input[0],maxNeighbors);    
        //mark V as visited.
        visitedCities[counter]=V;
        counter++;
    }
    return 0;
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
