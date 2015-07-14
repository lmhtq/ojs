#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define N 1000001
int a[N];
int n, k, res;

void init()
{
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) 
		scanf("%d", a + i);
}

void calc()
{
	sort(a, a + n);
}

void output()
{
	if (k < 0 || k > n) {
		printf("-1\n");
	} else {
		printf("%d\n", a[k-1]);
	}
}

int main()
{
	init();
	calc();
	output();
	return 0;
}