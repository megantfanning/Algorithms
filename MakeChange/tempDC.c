//Brute force/Divide and Conquer
//To make change for A cents:
//If there is a K-cent coin, then that one coin is the minimum
//Otherwise, for each value i < K,
//Find the minimum number of coins needed to make i cents
//Find the minimum number of coins needed to make K - i cents
//Choose the i that minimizes this sum
DynArr * changeslow(DynArr *V, int A)
{
	// Locals 
	DynArr *MyCoins; // Return array of coin counts
	DynArr *countsAr; // Array of counts for each i
	DynArr *lower; // Return from lower half 
	DynArr *upper; // Return from upper half
	DynArr *compiledAr[A]; // Array of pointers to each of the i solutions
	int i = 0;
	int j = 0;
	int iMin = 0; 
	
	// Initialize the dynamic arrays that are 
	// the size of V
	MyCoins = createDynArr(sizeDynArr(V));
	lower = createDynArr(sizeDynArr(V));
	upper = createDynArr(sizeDynArr(V));
	for(i = 0; i < sizeDynArr(V); i++)
	{
		addDynArr(MyCoins, 0);
		addDynArr(lower, 0);
		addDynArr(upper, 0);
	}
	
	// Initialize the array that is used to hold all the i counts
	// Adding 1 to be able to loop from 1 in the main recursion loop
	countsAr = createDynArr(A + 1);
	for(i = 0; i < A + 1; i++)
	{
		addDynArr(countsAr, 0);
	}
	
	// Base case check if the A value has a coin 
	// exactly equal to its value 
	for(i = 0; i < sizeDynArr(V); i++)
	{
		if(getDynArr(V, i) == A)
		{
			putDynArr(MyCoins, i, getDynArr(MyCoins, i) + 1);
			putDynArr(countsAr, i, 1);
			return MyCoins;
		}
	}
	
	// Loop through all i from 1 to A and recurse on 
	// A - i and A 
	for(i = 1; i < A + 1; i++)
	{		
		// Loop to pairwise sum the two
		for(j = 0; j < sizeDynArr(V); j++)
		{
			putDynArr(MyCoins, j, getDynArr(lower, j) + getDynArr(upper, j));
		}
		
		// Loop to get the sum of the coins in MyCoins just created
		for(j = 0; j < sizeDynArr(MyCoins); j++)
		{
			putDynArr(countsAr, i, getDynArr(countsAr, i) + getDynArr(MyCoins, j));
		}

		// Put the combined solution into the array of pointers
		compiledAr[i] = MyCoins;
	}
	
	// Find the minimum in the countsAr array 
	for(i = 0; i < A + 1; i++)
	{
		if(iMin > getDynArr(countsAr, i))
			iMin = i;
	}
	
	// Since we are using the i after the for we need to dec 1
	return compiledAr[i -1];
}
