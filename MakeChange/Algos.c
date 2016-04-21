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
	// Locals 
	DynArr *MyCoins; // Return array of coin counts
	DynArr *countsAr; // Array of counts for each i
	DynArr *lower; // Return from lower half 
	DynArr *upper; // Return from upper half
	int i = 0;
	int j = 0;
	int iMin = 0; 
	
	// Initialize the dynamic arrays that are 
	// the size of V
	MyCoins = createDynArr(sizeDynArr(V));
	lower = createDynArr(sizeDynArr(V));
	upper = createDynArr(sizeDynArr(V));
	for(i = 0; i < sizeDynArr(V); i++)
	{
		addDynArr(MyCoins, 0);
		addDynArr(lower, 0);
		addDynArr(upper, 0);
	}
	
	// Initialize the array that is the size of A 
	countsAr = createDynArr(A + 1);
	for(i = 0; i < A + 1; i++)
	{
		addDynArr(countsAr, 0);
	}
	
	// Base case check if the A value has a coin 
	// exactly equal to its value 
	for(i = 0; i < sizeDynArr(V); i++)
	{
		if(getDynArr(V, i) == A)
		{
			putDynArr(MyCoins, i, getDynArr(V, i) + 1);
		}
	}
	
	// Loop through all i from 1 to A and recurse on 
	// A - i and A 
	for(i = 1; i < A + 1; i++)
	{		
		// Loop to pairwise sum the two
		for(j = 0; j < sizeDynArr(V); j++)
		{
			putDynArr(MyCoins, j, getDynArr(lower, j) + getDynArr(upper, j));
		}
		
		// Loop to get the sum of the coins in MyCoins just created
		for(j = 0; j < sizeDynArr(MyCoins); j++)
		{
			putDynArr(countsAr, i, getDynArr(countsAr, i) + getDynArr(MyCoins, j));
		}
	}
	
	// Find the minimum in the countsAr array 
	for(i = 0; i < A + 1; i++)
	{
		if(iMin > getDynArr(countsAr, i))
			iMin = i;
	}
	
	return MyCoins;
}

// Greedy
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
	
	for(i = 0; i < sizeDynArr(V); i++)
		printf("%d ", getDynArr(MyCoins, i));
	
	// Clean up 
	deleteDynArr(SubProbs);
	
	// Send the results back
	return MyCoins;
}
