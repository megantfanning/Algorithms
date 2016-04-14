/* ------------------------------------------------------------------------- */
// Project Name: 	CS325 - Project 1
// File 			Name: Algos.h
// Desc: 			Algorithms functions for finding maximum sum subarray.
// Authors:			Ian Dalrymple, Megan Fanning, Toni York
// Date: 			04/10/2016
/* ------------------------------------------------------------------------- */
#include<math.h>
#include "dynamicArray.h"

#ifndef ALGOS_INCLUDED
#define ALGOS_INCLUDED 1

//define tuple struct
struct Tuple{
    int low;
    int high;
    int sum;
};

// Enumeration algorithms which receive the 
// start and finish ref parameters and pass 
// back the sum. 
int BadEnum(DynArr *v, int * start, int *end);
int GoodEnum(DynArr *v, int *start, int *end);
struct Tuple MSS_DAC (int A[],int low,int high);
struct Tuple MSS_DAC_CROSS(int A[],int low,int mid,int high);
int lTime(DynArr *v, int *start, int *end);


#endif
