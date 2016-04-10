// Enumeration for max subarray 
// evaluate every possible solution 
MaxSubArray(a[1, ...... , n])
	for each pair (i,j) with 1 <= i <= j <= n 
		compute a[i] + a[i + 1] ...... a[j]
		keep max sum found so far 
	return max sum found 
	
	
// Better Enumeration 
// don't compute sums from scratch 
MaxSubArray(a[1, .....,n])
	for i = 1, ...... n
		sum = 0 
		for j = i, ...... n 
			sum = sum + a[j]
			keep max found so far 
	return max sum found 
	
// DVC 
1) Find the answer of first half
2) Find the answer of the second half
3) Find the spanning max 
4) Find the max of those three 
? - whats the base case

// Recursion inversion 
-- see 17 30 of the lecture
-- start at the smallest and work up to whole array 