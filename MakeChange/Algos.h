/* ------------------------------------------------------------------------- */
// Project Name: 	CS325 - Project 2
// File 			Name: Algos.h
// Desc: 			Algorithms functions for making change.
// Authors:			Ian Dalrymple, Megan Fanning, Toni York
// Date: 			04/25/2016
/* ------------------------------------------------------------------------- */
#include<math.h>
#include "dynamicArray.h"

#ifndef ALGOS_INCLUDED
#define ALGOS_INCLUDED 1
#define INT_MIN (-2147483647 - 1)

// Programs accept
//	An array V where V[i] is the value of the coin of the ith denomination.
//	A value A which is the amount of change we are asked to make
// 	return an array the same length as the array V but with counts of 
// 	each index in the respective locations.

//Brute force/Divide and Conquer
DynArr * changeslow(DynArr *V,int A);

//Greedy
//int * changegreedy(int V[],int A); 

//Dynamic
//int * changedp(int V[],int A);

#endif
