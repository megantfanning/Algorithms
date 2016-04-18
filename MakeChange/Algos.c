/* ------------------------------------------------------------------------- *
// Project Name: 	CS325 - Project 2
// File 			Name: Algos.c
// Desc: 			Entry point for project.
// Authors:			Ian Dalrymple, Megan Fanning, Toni York
// Date: 			04/18/2016
*-------------------------------------------------------------------------*/

// Programs accept
//An array V where V[i] is the value of the coin of the ith denomination.
// A value A which is the amount of change we are asked to make
//return an array of length 4 (pennies, nickels, dimes and quarters.

//Brute force/Divide and Conquer
int * changeslow(int V[],int A){
//To make change for A cents:
//If there is a K-cent coin, then that one coin is the minimum
//Otherwise, for each value i < K,
//Find the minimum number of coins needed to make i cents
//Find the minimum number of coins needed to make K - i cents
//Choose the i that minimizes this sum

}

//Greedy
int * changegreedy(int V[],int A){
    int i=0;
    int coins=0;
    while(coins != A){
        //set i to length of the array
        i=sizeof(V) / sizeof(V[0]);
        //Use the largest value coin possible.
        if(V[i] > 0){
            //check if the value of the coin to ensure we don't give too much change
            if( i+coins < A){
                coins= i + coins;
                V[i] = V[i]-1;
                //Subtract the value from the amount of change to be made.
            }else{
                //if the value of i is too great to make change decrease to smaller size coin denomination
                i--;
            }
        }else{
            i--;
        }
    }

}

//Dynamic
int * changedp(int V[],int A){}
