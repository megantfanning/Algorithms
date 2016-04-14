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
struct Tuple MSS_DAC (int A[],int low,int high)
{
	printf("%d",A[3]);
	
    // int llow,rlow,rhigh,rsum,clow,chigh,csum,lhigh,lsum;//TODO define
	int mid; 
	struct Tuple lTuple, rTuple, cTuple;
			
	// Only one element present so return as high and low
    if(high == low)
	{
        int temp = A[low];
        struct Tuple equal = {low, high, temp};
        return equal;
    }
	// Find the midpoint and then recurse on the left, right and 
	// straddling chunks 
	else
	{
        mid = floor((low + high) / 2);
        lTuple = MSS_DAC(A, low, mid);
        rTuple = MSS_DAC(A, mid + 1, high);
        cTuple = MSS_DAC_CROSS(A, low, mid, high);

        if(lTuple.sum >= rTuple.sum && lTuple.sum >= cTuple.sum)
		{
            // struct Tuple lTuple = {llow, lhigh, lsum};
            return lTuple;
        }
		else if(rTuple.sum >= lTuple.sum && rTuple.sum >= cTuple.sum)
		{
            // struct Tuple rTuple = {rlow, rhigh, rsum};
            return rTuple;
        }
		else
		{
            // struct Tuple cTuple = {clow, chigh, csum};
            return cTuple;
        }
    }
}

//The MSS-DAC-CROSS helper subroutine finds the both left and right sides of the maximum crossing subarray 
//TODO fix return
struct Tuple MSS_DAC_CROSS(int A[],int low,int mid,int high)
{
    int sum = 0;
	int left_sum = -9999;
	int max_right = -999;
	int max_left = -999;

    for (int i = mid; i < low; i--)
	{
        sum = sum + A[i];
        
        if(sum > left_sum)
		{
            left_sum = sum;
			max_left = i;
        }
    }

    sum = 0;
	int right_sum = -9999;

    for (int j = mid + 1; j < high; j++)
	{
        sum = sum + A[j];
        if (sum > right_sum)
		{
            right_sum = sum;
            max_right = j;
        }
    }
    struct Tuple maxTuple = {max_left, max_right, left_sum + right_sum};
    return maxTuple;
}