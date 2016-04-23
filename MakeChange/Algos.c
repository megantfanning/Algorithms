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

// Method taken from:
// http://www.cis.upenn.edu/~matuszek/cit594-2014/Lectures/30-dynamic-programming.ppt
DynArr * changeslow(DynArr *V, int A)
{
	// Local declares 
	DynArr *finalSol; // Final
	DynArr *tempSol1; // First subproblem
	DynArr *tempSol2; // Second subproblem
	int i, j; // Indexers
	int iDenomCount  = sizeDynArr(V);
	int iNewCount;
	int iMinCount = 9392;
	
	// Init the dynamic solution arrays
	finalSol = createDynArr(iDenomCount);
	tempSol1 = createDynArr(iDenomCount);
	tempSol2 = createDynArr(iDenomCount);
	for(i = 0; i < iDenomCount; i++)
	{
		addDynArr(finalSol, 0);
		addDynArr(tempSol1, 0);
		addDynArr(tempSol2, 0);
		
	}
	
	// Loop to check for the base case
	for(i = 0; i < iDenomCount; i++)
	{
		// Check if a coin matches the value being checked for
		if(getDynArr(V, i) == A)
		{
			putDynArr(finalSol, i, 1);
			return finalSol;
		}
	}

	// Loop through all values up to n 
	for(i = 1; i < A; i++)
	{
		// Get the sub solutions 
		tempSol1 = changeslow(V, i);
		tempSol2 = changeslow(V, A - i);
		
		// Sum the total coins used for both sub solutions 
		iNewCount = 0;
		for(j = 0; j < iDenomCount; j++)
		{
			// Place the total coins in temp variable
			iNewCount = iNewCount + getDynArr(tempSol1, j) + getDynArr(tempSol2, j);
		}
		
		// Compare the new coin count to the previous best 
		if(iNewCount < iMinCount)
		{
			// Set the new best 
			iMinCount = iNewCount;
			
			// Index wise sum the sub solutions to get the full solution
			for(j = 0; j < iDenomCount; j++)
			{
				putDynArr(finalSol, j, getDynArr(tempSol1, j) + getDynArr(tempSol2, j));
			}
		}
	}
	
	// Return the best case solution
	return finalSol;
}

// Greedy - choose the max coin size that is less than
//			the current change required. Make this selection
//			repeatedly using a loop structure.
DynArr * changegreedy(DynArr *V, int A)
{
	// Locals 
	DynArr *MyCoins;
	int i = 0;
	int iRemaining = -99;
	
	// Initialize iRemaining
	iRemaining = A;
	
	// Initialize return array
	MyCoins = createDynArr(sizeDynArr(V));
	for(i = 0; i < sizeDynArr(V); i++)
		addDynArr(MyCoins, 0);
	
	// Loop through the V array and decrement iRemaining 
	for(i = sizeDynArr(V) - 1; i >= 0; i--)
	{
		// Check if remaining is greater than coin value 
		if(iRemaining >= getDynArr(V, i))
		{
			// Increment the count in return array 
			putDynArr(MyCoins, i, getDynArr(MyCoins, i) + (iRemaining / getDynArr(V, i)));
			
			// Dec the remaining 
			iRemaining = iRemaining - ((iRemaining / getDynArr(V, i)) * getDynArr(V, i));
		}
		
		// Check for early exit 
		if(iRemaining == 0)
			break;
	}
	
	return MyCoins;
}

//Dynamic
DynArr *changedp(DynArr *V, int A)
{
		// Locals 
	DynArr *MyCoins;
	DynArr *SubProbs;
	int i = 0;
	int j = 0;
	int currentCoin=0;
	int iCount = -99;

	// Initialize return array
	MyCoins = createDynArr(sizeDynArr(V));
	for(i = 0; i < sizeDynArr(V); i++)
		addDynArr(MyCoins, 0);
	
	// Initialize the subproblem array 
	SubProbs = createDynArr(A + 1);
	for(i = 0; i < A + 1; i++)
		addDynArr(SubProbs, 0);
	
	// Loop to fill in the table 
	for(i = 0; i < A + 1; i++)
	{
		iCount = i;
		for(j = 0; j < sizeDynArr(V); j++)
		{
			if(getDynArr(V, j) <= i)
			{
				if(getDynArr(SubProbs, i - getDynArr(V, j)) + 1 < iCount)
				{
					iCount = getDynArr(SubProbs, i - getDynArr(V, j)) + 1;
					
					// Increment the denomination counter
					putDynArr(MyCoins, j, getDynArr(MyCoins, j) + 1);
					//track current best coins
					currentCoin=MyCoins;
				}
			}
		}
		
		putDynArr(SubProbs, i, iCount);
	}
	
	// for(i = 0; i < sizeDynArr(V); i++)
		// printf("%d ", getDynArr(MyCoins, i));
	
	// Clean up 
	deleteDynArr(SubProbs);
    MyCoins=currentCoin;//gets the best coin and returns it.	
	// Send the results back
	return MyCoins;
}
