/* ------------------------------------------------------------------------- *
// Project Name: 	CS325 - Project 2
// File 			Name: Algos.c
// Desc: 			Entry point for project.
// Authors:			Ian Dalrymple, Megan Fanning, Toni York
// Date: 			04/25/2016
*-------------------------------------------------------------------------*/

#include<math.h>
#include <stdio.h>
#include <stdlib.h>
#include "dynamicArray.h"

// Programs accept:
// An array V where V[i] is the value of the coin of the ith denomination.
// A value A which is the amount of change we are asked to make

// Algorithms return:
// The algorithm should return an array C where C[i] is the number of coins of value V[i] to 
// return as change and m the minimum number of coins it took. 

//Brute force/Divide and Conquer
//To make change for A cents:
//If there is a K-cent coin, then that one coin is the minimum
//Otherwise, for each value i < K,
//Find the minimum number of coins needed to make i cents
//Find the minimum number of coins needed to make K - i cents
//Choose the i that minimizes this sum
DynArr * changeslow(DynArr *V, int A)
{
	// Local declares 
	DynArr *C;

	C = createDynArr(sizeDynArr(V));	
	
	for(int i = 0; i < sizeDynArr(V); i++)
		addDynArr(C, i*3);
	
	for(int i = 0; i < 32767; i++)
			for(int j = 0; j < 32000; j++)
			{}
	
	return C;
}


// Greedy
DynArr * changegreedy(DynArr *V, int A)
{
	// Locals 
	DynArr *MyCoins;
    int i = 0;
    int totalChange = 0;
    int minCoins = 0;
	
	// Initialize return array
	MyCoins = createDynArr(sizeDynArr(V));
	for(i = 0; i < sizeDynArr(V); i++)
	{
		addDynArr(MyCoins, 0);
	}

	// Create indexer based on size of V
	i = sizeDynArr(V) - 1;
	
    while(totalChange != A && i >= 0)
	{
        //Use the largest value coin possible.
        if(getDynArr(V, i) > 0)
		{
            //check if the value of the coin to ensure we don't give too much change
            if(getDynArr(V, i) + totalChange < A)
			{
				//increment the number of total coins used
                minCoins++;
				
				// Increment the specific coin in the return array
				putDynArr(MyCoins, i, getDynArr(MyCoins, i) + 1);
			
               // Increment the change counter 
				totalChange = totalChange + getDynArr(V, i);	
            }
			else
			{
                //if the value of i is too great to make change decrease to smaller size coin denomination
                i--;
            }
        }
		else
		{
            i--;
        }
    }
	
	return MyCoins;
}


// Greedy
// DynArr * changegreedy(DynArr *V,int A)
// {
	// // Locals 
    // int i=0;
    // int totalChange=0;
    // //int MyCoins[5]={0,0,0,0,0};//TODO fix
	// DynArr *MyCoins = createDynArr(5);
    // int minCoins=0;
	
    // while(totalChange != A)
	// {
        // //set i to length of the array
        // i=sizeof(V) / sizeof(V[0]);
		
        // //Use the largest value coin possible.
        // if(V[i] > 0)
		// {
            // //check if the value of the coin to ensure we don't give too much change
            // if( i+totalChange < A)
			// {
                // coins= i + coins;
                // V[i] = V[i]-1;
                // minCoins++;//incriment the number of total coins used
                // myCoins[i]=myCoins[i]+i;//incriment my array
                // //Subtract the value from the amount of change to be made.
            // }
			// else
			// {
                // //if the value of i is too great to make change decrease to smaller size coin denomination
                // i--;
            // }
        // }
		// else
		// {
            // i--;
        // }
    // }
// }

// int B[4]{3,0,0,0,}

// //Dynamic
// int * changedp(int V[],int A){}
