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

// struct tuple{
    // int low;
    // int high;
    // int sum;
// }

// //The MSS-DAC-CROSS helper subroutine finds the both left and right sides of the maximum crossing subarray 
// //TODO fix return
// int MSS_DAC (int A[],int low,int high){
    // if(high == low){
        // return (low, high, A[low]);//TODO
    // }else{
        // int mid = floor((low + high) / 2);
        // int llow,rlow,rhigh,rsum,clow,chigh,csum,lhigh,lsum;//TODO define
        // //tuple (llow, lhigh, lsum) = MSS_DAC(A, low, mid); 
        // //tuple (rlow, rhigh, rsum) = MSS_DAC(A, mid + 1, high);
        // //tuple (clow, chigh, csum) = MSS_DAC_CROSS(A, low, mid, high);
        // if(lsum >= rsum && lsum >= csum){
            // return (llow, lhigh, lsum);
        // }else if(rsum >= lsum && rsum >= csum){
            // return (rlow, rhigh, rsum);
        // }else{
            // return (clow, chigh, csum);//TODO
        // }
    // }
// }

// //The recursive MSS-DAC algorithm checks for the base case, then makes two recursive calls on subproblems,
// // then one call to the helper subroutine MASS-DAC-CROSS, and finally it does a series of comparisons to return the maximum. 

// int MSS_DAC_CROSS(int A[],int low,int mid,int high){
    // //left-sum = -∞
    // int sum = 0;
    // int left,right,max;//TODO define
    // for (int i = mid;i< low; i--){
        // sum = sum + A[i];
        
        // if(sum > left-sum){
            // sum=left-sum;
            // i= max-left;
        // }
    // }
    // //right-sum = -∞
    // sum = 0;

    // for (int j = mid + 1; j < high; j++){
        // sum = sum + A[j];
        // if (sum > right-sum){
            // sum=right-sum;
            // j=max-right;
        // }
    // }
    // return (max-left, max-right, left-sum + right-sum);//TODO
// }

