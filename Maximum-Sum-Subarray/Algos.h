/* 	Algos.h : Algorithms. */
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
int dVC(DynArr *v, int *start, int *end);
int lTime(DynArr *v, int *start, int *end);
struct Tuple MSS_DAC (int A[],int low,int high);
int MSS_DAC_CROSS(int A[],int low,int mid,int high);


#endif
