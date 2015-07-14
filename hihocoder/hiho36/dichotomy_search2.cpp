#include <cstdio>

using namespace std;

#define N 1000001
int a[N], la[N], ra[N], n, k, res;

void init()
{
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++)
		scanf("%d", a + i);
	res = -1;
}

void calc()
{
	int cnt = 1;
	bool exits = false;
	for (int i = 0; i < n; i++) {
		if (a[i] < k) {
			cnt++;
		} 
		if (a[i] == k) {
			exits = true;
		}
	}
	if (exits) {
		res = cnt;
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