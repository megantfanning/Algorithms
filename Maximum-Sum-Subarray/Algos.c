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
#include <math.h>
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

// The recursive MSS-DAC algorithm checks for the base case, 
// then makes two recursive calls on subproblems, then one 
// call to the helper subroutine MASS-DAC-CROSS, and finally 
// it does a series of comparisons to return the maximum. 
struct Tuple MSS_DAC (DynArr *A, int low, int high)
{
	// Local declares
    struct Tuple lTuple,rTuple,cTuple;
		
    if(high == low)
	{
        int temp = getDynArr(A, low); // A[low];
        struct Tuple equal = {low, high, temp};
        return equal;
    }
	else
	{
        //find midpoint
        int mid = floor((low + high) / 2);

        //call MSS_DAC to return a tuple from the right, left and center ranges
        lTuple = MSS_DAC(A,low,mid);
        rTuple = MSS_DAC(A, mid+1, high);
        cTuple = MSS_DAC_CROSS(A,low,mid,high);

        //find the greatest tuple and return that
        if(lTuple.sum >= rTuple.sum && lTuple.sum >= cTuple.sum)
		{
            return lTuple;
        }
		else if(rTuple.sum >= lTuple.sum && rTuple.sum >= cTuple.sum)
		{
            return rTuple;
        }
		else
		{
            return cTuple;
        }
    }
}

//The MSS-DAC-CROSS helper subroutine finds the both left and right 
// sides of the maximum crossing subarray 
struct Tuple MSS_DAC_CROSS(DynArr *A, int low, int mid, int high)
{
    // Local declares
	int left_sum = INT_MIN;
	int max_left = INT_MIN;
	int right_sum = INT_MIN;
	int max_right = INT_MIN;
	int sum = 0;
	
	// Find max of left 
    for (int i = mid; i >= low; i--)
	{
        sum = sum + getDynArr(A, i); // A[i];
        
        if(sum > left_sum)
		{
            left_sum = sum;
			max_left = i;
        }
    }
	
	// Re-initialize the resuable sum
	sum = 0;
	
	// Find the max for the right
    for (int j = mid + 1; j <= high; j++)
	{
        sum = sum + getDynArr(A, j); // A[j];
		
        if (sum > right_sum)
		{
            right_sum = sum;
            max_right = j;
        }
    }
	
	// Return the max of the right, left and spanner
    struct Tuple maxTuple = {max_left, max_right, left_sum + right_sum};
    return maxTuple;
}

//Linear Time Algorithm
//iterate over the array checking the sum of the subarray as you go
struct Tuple lTime(DynArr *v)
{
	// Local declares 
    int low,high,ending_here_low;
    int n = sizeDynArr(v); //A.length
    int max_sum = INT_MIN;//-∞
    int ending_here_sum = INT_MIN;//-∞
    	
    for (int j = 0; j < n; j++){
        int ending_here_high = j;
        //check sum and reset ending_here_sum to the the current iteration 
        //of the array, 
        if (ending_here_sum > 0){
            ending_here_sum = ending_here_sum + getDynArr(v, j); //A[j]; 
        }else{
            ending_here_low = j;
            ending_here_sum = getDynArr(v, j); // A[j];
        }
        //if the new ending_sum is greater than max sum reset high and low
        if (ending_here_sum > max_sum){
            max_sum = ending_here_sum;
            low = ending_here_low;
            high = ending_here_high;
        }
    }
    struct Tuple maxTuple={low,high,max_sum};
    return maxTuple;
}

