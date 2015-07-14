#include <cstdio>
#include <algorithm>

using namespace std;

#define N 1000001
int a[N], n, k, res;

void init()
{
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) 
		scanf("%d", a+i);
}

void calc()
{
	sort(a, a+n);
	int left = 0, right = n-1, mid;
	while (left <= right) {
	//while (left < right) {//key WA
		mid = (left + right) / 2;
		if (a[mid] < k) {
			left = mid + 1;
		} 
		if (a[mid] > k) {
			right = mid - 1;
		}
		if (a[mid] == k) {
			break;
		}
	}
	if (a[mid] == k) {
		res = mid+1;
	} else {
		res = -1;
	}
}

void output()
{
	printf("%d\n", res);
}

int main()
{
	init();
	calc();
	output();
	return 0;
}
