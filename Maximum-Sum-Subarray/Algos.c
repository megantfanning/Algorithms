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
struct Tuple MSS_DAC (int A[],int low,int high){
    struct Tuple lTuple,rTuple,cTuple;

    if(high == low){
        int temp=A[low];
        struct Tuple equal={low, high,temp};
        return equal;
    }else{
        int mid = floor((low + high) / 2);
        lTuple =MSS_DAC(A,low,mid);
        rTuple =MSS_DAC(A, mid+1, high);
        cTuple =MSS_DAC_CROSS(A,low,mid,high);

        if(lTuple.sum >= rTuple.sum && lTuple.sum >= cTuple.sum){
            //struct Tuple lTuple={llow,lhigh,lsum};
            return lTuple;
        }else if(rTuple.sum >= lTuple.sum && rTuple.sum >= cTuple.sum){
            //struct Tuple rightResults={rlow, rhigh, rsum};
            return rTuple;
        }else{
            //struct Tuple cTuple={clow, chigh, csum};
            return cTuple;
        }
    }
}

//The recursive MSS-DAC algorithm checks for the base case, then makes two recursive calls on subproblems,
// then one call to the helper subroutine MASS-DAC-CROSS, and finally it does a series of comparisons to return the maximum. 

struct Tuple MSS_DAC_CROSS(int A[],int low,int mid,int high){
    //left-sum = -∞
    int sum = 0;
    int leftSum,rightSum,maxSum;//TODO define
    for (int i = mid; i< low; i--){
        int sum = sum + A[i];
        
        if(sum > leftSum){
            sum=leftSum;
            i= maxLeft;//how is max defined?
        }
    }
    //right-sum = -∞
    //sum = 0;

    for (int j = mid + 1; j < high; j++){
        sum = sum + A[j];
        if (sum > rightSum){
            sum=rightSum;
            j=maxRight;
        }
    }
    struct Tuple maxTuple={maxLeft, maxRight, leftSum + rightSum};
    return maxTuple;
}


struct Tuple MSS_LINEAR (int A[]){
    int endingHereHigh,endingHereSum,endingHereLow;
    int n = sizeof(A)/sizeof(int);//A.length
    
    //max-sum = -∞
    //ending-here-sum = -∞
    for (int j = 0; j <= n-1; j++){
        endingHereHigh = j;
        if (endingHereSum > 0){
            endingHereSum = endingHereSum + A[j];
        }else{
            int endingHereLow = j;
            endingHereSum = A[j];
        }
        if (endingHereSum > maxSum){
            int maxSum = endingHereSum;
            int low = endingHereLow;
            int high = endingHereHigh;
        }
    }
    struct Tuple maxTuple={low, high, max-sum};
    return maxTuple;
}
