/* ------------------------------------------------------------------------- *
// Project Name: 	CS325 - Project 2
// Authors:			Ian Dalrymple, Megan Fanning, Toni York
// Date: 			04/18/2016
/* -------------------------------------------------------------------------*/

Project Description:
The coin change problem requires the algorithm to return the minimum number 
of coins possible for a certain amount given some coin denominations. The 
algorithm must produce a correct result for regardless of amount of change 
needed or the denominations (denominations must contain a 1 cent piece). Three 
methods are employed: changeslow which uses recursion. changegreedy which uses 
the greedy method (suboptimal) and changedp which uses dynamic programming 
techniques.

File Descriptions:
1) Algos.c - actuals functions used to solve the coin change problem. 
2) UserInt.c - manages file IO and main loop for calling and timing the algorithms.
3) DynamicArray.c - dynamic array functions taken directly from CS261.
4) Main.c - entry point which calls on functions in UserInt.c.

Instructions for Building the Project:
1) Place the entire contents of this folder on flip directory.
2) Enter make cleanall to remove old .o files and results files.
3) Enter make to compile the project.

Instructions for Running the Project:
1) Enter Change "filenametobeparsed" where "filenametobeparsed" is 
the name of the file containing the input data. 
2) The results will be written to SUBSTR("filenametobeparsed", length - 4) + "Change" + ".txt".

Notes:
1) changeslow algorithm runs very slow and should not be tested for A
values greater than 20. If A values greater than 20 are input the program 
will simply bypass the algorithm and output all 0's. 
2) The input file must be of the form:
[1, ..... n]
A
where n is the largest coin value and A is the change to be made. 
