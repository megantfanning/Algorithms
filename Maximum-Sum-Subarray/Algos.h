/* 	Algos.h : Algorithms. */
#include<math.h>
#include "dynamicArray.h"

#ifndef ALGOS_INCLUDED
#define ALGOS_INCLUDED 1

// Enumeration algorithms which receive the 
// start and finish ref parameters and pass 
// back the sum. 
int BadEnum(DynArr *v, int * start, int *end);
int GoodEnum(DynArr *v, int *start, int *end);
int dVC(DynArr *v, int *start, int *end);
int lTime(DynArr *v, int *start, int *end);

#endif
