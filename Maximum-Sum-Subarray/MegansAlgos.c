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
            return lTuple;
        }else if(rTuple.sum >= lTuple.sum && rTuple.sum >= cTuple.sum){
            return rTuple;
        }else{
            return cTuple;
        }
    }
}

//The MSS-DAC-CROSS helper subroutine finds the both left and right sides of the maximum crossing subarray 
struct Tuple MSS_DAC_CROSS(int A[],int low,int mid,int high)
{
    //int definition
    int leftSum,rightSum,maxSum,max_left,max_right,left_sum, right_sum,maxLeft,sum;
    for (int i = mid; i< low; i--){
        int sum = sum + A[i];
        
        if(sum > leftSum){
            sum=leftSum;
            i= maxLeft;//how is max defined?
        }
    }
    rightSum = INT_MIN; //-∞
    sum = 0;

    for (int j = mid + 1; j < high; j++)
	{
        int sum = sum + A[j];
        if (sum > right_sum)
		{
            int right_sum = sum;
            int max_right = j;
        }
    }
    struct Tuple maxTuple = {max_left, max_right, left_sum + right_sum};
    return maxTuple;
}


struct Tuple MSS_LINEAR (int A[]){
    int low,high,ending_here_low;
    int n = sizeof(A)/sizeof(int); //A.length
    int max_sum = INT_MIN;//-∞
    int ending_here_sum = INT_MIN;//-∞
    for (int j = 0; j< n-1;j++){
        int ending_here_high = j;
        if (ending_here_sum > 0){
            ending_here_sum = ending_here_sum + A[j];
        }else{
            ending_here_low = j;
            ending_here_sum = A[j];
        }
        if (ending_here_sum > max_sum){
            max_sum = ending_here_sum;
            low = ending_here_low;
            high = ending_here_high;
        }
    }
    struct Tuple maxTuple={low,high,max_sum};
    return maxTuple;
}
