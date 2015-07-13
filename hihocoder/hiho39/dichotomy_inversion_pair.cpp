#include <cstdio>
#include <cstring>

using namespace std;

#define N 100001

int a[N], n, tmp[N];
long res;

void init()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) 
		scanf("%d", a + i);
	res = 0;
}

void merge(int left, int right)
{
	if (left == right) {
		return;
	}
	int mid = (left + right) / 2;
	merge(left, mid);
	merge(mid+1, right);
	int *b = a;

	int ind = 0;
	long cnt = 0;
	long sum = 0;
	int i = left;
	int j = mid + 1;
	while (i <= mid && j <= right) {
		if (a[i] <= b[j]) {
			tmp[ind++] = a[i++];
			sum += cnt;
		} else {
			tmp[ind++] = b[j++];
			cnt++; 
		}
	}
	while (i <= mid) {
		tmp[ind++] = a[i++];
		sum += cnt;
	}
	while (j <= right) {
		tmp[ind++] = b[j++];
		cnt++; 
	}
	res += sum;
	//printf("%d %d aaaa\n", (right - left + 1), ind);
	memcpy(a + left, tmp, sizeof(int) * (right - left + 1) );
}

void output()
{
	printf("%ld\n", res);
}

int main()
{
	init();
	merge(0, n-1);
	output();
	return 0;
}