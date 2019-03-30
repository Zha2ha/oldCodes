#include<iostream>
using namespace std;
#define N 1000
int main()
{
	int prime[N + 1], k, n, cnt = 0;
	for (k = 2; k <= N; k++)
	{
		prime[k] = 1;
	}
	k = 2;
	while (k <= N)
	{
		n = 2;
		while (n*k <= N)
		{
			prime[n*k] = 0;
			n++;
		}
		k++;
		while (k <= N && prime[k] == 0)
		{
			k++;
		}
	}
	k = 2;
	while (k <= N)
	{
		if (prime[k] == 1)
		{
			cout << k << " ";
			cnt++;
		}
		k++;
	}
	cout << endl;
	cout << "there ara " << cnt << "number" << endl;

	return 0;
}
