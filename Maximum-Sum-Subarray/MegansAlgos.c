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

//The MSS-DAC-CROSS helper subroutine finds the both left and right sides of the maximum crossing subarray 
//TODO fix return
struct Tuple MSS_DAC_CROSS(int A[],int low,int mid,int high)
{

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


