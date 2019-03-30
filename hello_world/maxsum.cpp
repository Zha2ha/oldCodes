#include <iostream>
using namespace std;
int MaxSum(int a[], int n);
int main()
{
    int a[] = {-20, 11, -4, 13, -1, 7, -2};//最大字段和为26
    int sum = MaxSum(a, 7);
    cout << sum << endl;
    system("pause");
    return 0;
}
int MaxSum(int a[], int n)
{
    int max = 0;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            sum = a[i];
            a[i] += a[j];
            if (a[i] > sum)
            {
                sum = a[i];
            }
        }
        if (sum > max)
        {
            max = sum;
        }
    }
    return max;
}