/* ------------------------------------------------------------------------- */
// Project Name: 	CS325 - Project 1
// File 			Name: Algos.c
// Desc: 			Algorithms functions for finding maximum sum subarray.
// Authors:			Ian Dalrymple, Megan Fanning, Toni York
// Date: 			04/10/2016
/* ------------------------------------------------------------------------- */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "Algos.h"

// Creates the internal array to the struct DynArray
int BadEnum(DynArr *v, int *start, int *end)
{
	// Local declares 
	int iMaxSum = getDynArr(v, 0);
	int iCurSum = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	
	// Check for one element and return if 
	// only one long 
	if(sizeDynArr(v) == 1)
	{
		*start = 0;
		*end = 0;
		return getDynArr(v, 0);
	}
	
	// Loop through the array - outer loop is start index 
	for(i = 0; i < sizeDynArr(v); i++)
	{
		// Init the current sum
		iCurSum = getDynArr(v, i);
		
		// Loop the ending point 
		for(j = i + 1; j <sizeDynArr(v); j++)
		{
			// Init the current sum
			iCurSum = getDynArr(v, i);
			
			// Loop through to get sum from i to j
			for(k = i + 1; k <= j; k++)
			{
				iCurSum = iCurSum + getDynArr(v, k);
			}
			
			// Check to see if the current sum is greater than the 
			// maximum sum and if yes replace and grab the indices
			if(iCurSum > iMaxSum)
			{
				iMaxSum = iCurSum;
				*start = i;
				*end = j;
			}
		}
	}
	
	return iMaxSum;
}

// Enumeration but keeping track of the previous sums 
int GoodEnum(DynArr *v, int *start, int *end)
{
	// Local declares 
	int iMaxSum = getDynArr(v, 0);
	int iCurSum = 0;
	int i = 0;
	int j = 0;

	// Check for one element and return if 
	// only one long 
	if(sizeDynArr(v) == 1)
	{
		*start = 0;
		*end = 0;
		return getDynArr(v, 0);
	}
	
	// Loop through the array - outer loop is start index 
	for(i = 0; i < sizeDynArr(v); i++)
	{
		// Init the current sum
		iCurSum = getDynArr(v, i);
		
		// Loop the ending point 
		for(j = i + 1; j < sizeDynArr(v); j++)
		{
			// Init the current sum
			iCurSum = iCurSum + getDynArr(v, j);
			
			// Check to see if the current sum is greater than the 
			// maximum sum and if yes replace and grab the indices
			if(iCurSum > iMaxSum)
			{
				iMaxSum = iCurSum;
				*start = i;
				*end = j;
			}
		}
	}
	
	return iMaxSum;
}


//The MSS-DAC-CROSS helper subroutine finds the both left and right sides of the maximum crossing subarray 
//TODO this function returns multiple things need to return array
int MSS-DAC (A[],int low,int high){
      if high == low
            return (low, high, A[low])
      else
            mid = floor((low + high) / 2)
            (llow, lhigh, lsum) = MSS-DAC(A, low, mid)
            (rlow, rhigh, rsum) = MSS-DAC(A, mid + 1, high)
            (clow, chigh, csum) = MSS-DAC-CROSS(A, low, mid, high)
            if lsum ≥ rsum and lsum ≥ csum
                  return (llow, lhigh, lsum)
            elseif rsum ≥ lsum and rsum ≥ csum
                  return (rlow, rhigh, rsum)
            else return (clow, chigh, csum)
}

//The recursive MSS-DAC algorithm checks for the base case, then makes two recursive calls on subproblems,
// then one call to the helper subroutine MASS-DAC-CROSS, and finally it does a series of comparisons to return the maximum. 

int DivideAndConquer(){

      MSS-DAC-CROSS(A, low, mid, high)
      left-sum = -∞
      sum = 0
      for i = mid downto low
            sum = sum + A[i]
      if sum > left-sum
            left-sum =sum
            max-left = i
      right-sum = -∞
      sum = 0
      for j = mid + 1 to high
            sum = sum + A[j]
            if sum > right-sum
                  right-sum = sum
                  max-right = j
      return (max-left, max-right, left-sum + right-sum)
}


