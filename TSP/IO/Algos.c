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
int getDistance(struct structCity A, struct structCity B)
{
    //get distance between two cities
    int x=A.iX-B.iX;//subtract x coordinates
    int y=A.iY-B.iY;//subtract y coordinates
    double dist=pow(y,2)+pow(x,2);// raise both to the power of two and add
    double distance=sqrt(dist);//sqrt of the sum of x^2+y^2
    int myDistance=nearbyint(distance);//round to nearest int
    return myDistance;
}

// Get the distance from an origin city to the nearest city. Return the min distance.
int NearestNeighbor(struct structCity *cityList, 
		struct structCity *visitedCities, int size, int start){
    
	// Local declares 
	int iCurDist = -999; // Holder for the current distance 
	int iShortDist = -999; // Holder for the min distance 
	int iFlag = -999; // Flag for same city or in the visited list
	int iCurCityId = -999; // Holder for the index of the current closest city
	int i = 0; // Shared indexer

	// Loop over the city list and find the shortest distance 
	for(i = 0; i < size; i++)
	{
		// Init the flag 
		iFlag = -999;
		
		// Check if the ith element is the start element 
		if(i == start)
		{
			iFlag = 1;
		}
		
		// Only execute if the flag has not been set 
		if(iFlag != 1)
		{
			// Check if ith element is in visitedCities
			for(int j = 1; j < visitedCities[0].iId; j++)
			{
				if(cityList[i].iId == visitedCities[j].iId)
				{
					iFlag = 1;
					break;
				}
			}
		}
		
		// Only execute if flag has not been set meaning 
		// we have the same vertex for start and end or the 
		// vertex is already in the finished pile 
		if(iFlag != 1)
		{
			// Now get the distance for the ith city 
			iCurDist = getDistance(cityList[start], cityList[i]);

			// Init the distances for first time through
			if(iShortDist < 0)
			{
				iShortDist = iCurDist;
				iCurCityId = i;
			}
			
			// Check if current distance is less than min distance 
			if((iShortDist > 0 && iCurDist > 0) & (iCurDist < iShortDist))
			{
				iShortDist = iCurDist;
				iCurCityId = i;
			}
		}
	}
	
	// Put the closest city into visited
	visitedCities[visitedCities[0].iId + 1] = cityList[iCurCityId];
	
	// Increment the size of visitedCities
	visitedCities[0].iId = visitedCities[0].iId + 1;
	
	// Return the min distance
	return iShortDist;
}

// Algorithm to get the shortest round trip for the 
// input array passed in. The algorithm should populate 
// the output array that is passed in with the first row 
// being the total distance and then the subsequent rows 
// being the cities in the order they are to be visited, The 
// size parameter is the number of cities.
int resultTSP(struct structCity *input, int *output, int size, int StartNode)
{
	// Local declares
	struct structCity visitedCities[size + 1]; // Put the size in the first index
	int TotalDist = -999; // Total distance traveled
	int i = -999; // Global indexer
	
	// Set the size of visitedCities 
	visitedCities[0].iId = 1;
	visitedCities[0].iX = -999;
	visitedCities[0].iY = -999;
	
	// Add the initial city to the first index of visited cities 
	visitedCities[1] = input[StartNode];
	
	// Get the nearest neighbor for the first time through
	TotalDist = NearestNeighbor(input, visitedCities, size, StartNode);
	
	// Now loop through the rest of the input list 
	while(visitedCities[0].iId < size)
	{
		TotalDist = TotalDist + NearestNeighbor(input, visitedCities, size, 
					visitedCities[visitedCities[0].iId].iId);
	}

	// Move the visited cities to the output
	for(i = 1; i < size + 1; i++)
	{
		output[i] = visitedCities[i].iId;
	}
    // add the distance from the last city to the first city;
    int distToFinishLoop=getDistance(visitedCities[0],visitedCities[size]); 	
    TotalDist+=distToFinishLoop;
	// Move the total distance traveled to index 0 in the output list
	output[0] = TotalDist;
	
	// Bounce 
	return 0;
}

//compare the distance between the first and last distance
//1 need to run again 0 okay run time
int tourComparsion(int *output,int length){
    int startDistance=0;
    int endDistance=0;
    //sum the first 5 distances
    for(int i=0;i<5;i++){
        startDistance=output[i];
    }
    //sum the last 5 distances
    for(int j=length;j<length-5;j--){       //StartNode=5;//use 5 so we have a significantly different start
        //resultTSP(input,output, size,StartNode);

        endDistance=output[length];
    }
    //compare
    //if last 5 is significantly greater then call resultTSP again
    if(endDistance>(1.2*startDistance)){
        return 1;
    }
    return 0;
}
