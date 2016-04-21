#include <iostream>
#include <algorithm> 
#define ALGOS_INCLUDED
#define INT_MIN (-2147483647 - 1)
#define INT_MAX 10000000
using namespace std;



int CoinChange(int amount, int d[], int size)
{
    
	if (amount <= 0) return 0;

	int min_coins = (int)INT_MAX;

	for (int i = 0; i < size; i++) 
	{
		if (d[i] <= amount)
		{
			int recur = CoinChange(amount - d[i], d, size) + 1;

			if (min_coins > recur)
			{
				min_coins = recur;
				//cout << d[i] << endl;
			}
		}
			
	}
	return min_coins;
}


int main()
{
	//int d[] = { 1, 5, 3, 10, 25 };
	int d[] = { 1, 5 };
	int amount = 7;
	int size = sizeof(d) / sizeof(d[0]);
	int ans = CoinChange(amount, d, size);
	cout << "Minimal # of coins = " << ans << endl;

	return 0;
}
