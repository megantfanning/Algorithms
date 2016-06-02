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


int NearestNeightbor(struct structCity *cityList,struct structCity *visitedCities, int size){
    int counter=0;
    int totalDistance=0;

    //start on an arbitrary vertex as current vertex.
    visitedCities[counter]=cityList[0];
    counter++;
    struct structCity currentCity=cityList[0];//first vertex

    //if all the vertices in domain are visited, then terminate.
    while(counter<size){
        //find out the shortest edge connecting current vertex 
        //and an unvisited vertex V (the closest neighbor.
        //set current vertex to V.
        struct structCity V;
        int minimumDistance=-999;
        int distance=-999;

        for(int i=0; i<size;i++){
            //get the distance between city & neighbor
            distance=getDistance(currentCity, cityList[i]);
            if(distance<minimumDistance){
                //check if cityList[i] has been visited
                for(int j=0;j<counter;j++){
                    if(cityList[i].iId == visitedCities[j].iId){
                        //city have been visited.
                        return -1;//TODO this error needs to be handled.
                    }
                }
                minimumDistance=distance;
                V=cityList[i];
            }
        } 
        //mark V as visited, incriment counter
        visitedCities[counter]=V;
        totalDistance=minimumDistance;
        counter++;
        currentCity=V;
    }
    
    return totalDistance;
}

// Algorithm to get the shortest round trip for the 
// input array passed in. The algorithm should populate 
// the output array that is passed in with the first row 
// being the total distance and then the subsequent rows 
// being the cities in the order they are to be visited, The 
// size parameter is the number of cities.
int resultTSP(struct structCity *input, int *output, int size)
{
    //create an array for visited cities
    struct structCity visitedCities[size];
    //TODO zero out visitedCities
    int totalDistance=NearestNeightbor(input,visitedCities,size);

    printf("totalDistance %d",totalDistance);

	// Dummy populate the result array 
	for(int i = 0; i < size + 1; i++)
	{
        printf("%d, ",visitedCities[i].iId);
        
		/*if(i == 0)
		{
			output[0] = 78932;
		}
		else 
		{
			output[i] = input[i - 1].iY;
		}*/
	}
	
	return 0;
}
