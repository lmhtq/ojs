#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1002
#define M 1002
int n, m, a[N], b[N], d[N], x[M], y[M], t[M];

void init()
{
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(d, 0, sizeof(d));
	memset(x, 0, sizeof(x));
	memset(y, 0, sizeof(y));
	memset(t, 0, sizeof(t));
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)  
		scanf("%d%d", a + i, b + i);
	for (int i = 0; i < m; i++) 
		scanf("%d%d%d", x + i, y + i, t + i);
	for (int i = 0; i < n; i++) {
		d[i] = b[i] - a[i];
		if (d[i] < 0) {
			d[i] = -d[i];
		}
	}
}

void calc()
{
	for (int i = 0; i < m; i++) {
		int cnt = 0, tmp, tt;
		for (int j = 0; j < n; j++) {
			tmp = t[i] % (2*d[j]);
			if (a[j] < b[j]) {
				if (tmp > d[j]) {
					tt = b[j] - (tmp - d[j]);
				} else {
					tt = a[j] + tmp;
				}
			} else if (a[j] > b[j]) {
				if (tmp > d[j]) {
					tt = b[j] + (tmp - d[j]);
				} else {
					tt = a[j] - tmp;
				}
			} else {
				tt = a[j];
			}
			//printf("%d %d\n",j, tt );
			if (tt <= max(x[i], y[i]) && tt >= min(x[i], y[i]) ) {
				cnt++;
			}
		}
		printf("%d\n", cnt);
	}
}

int main()
{
	init();
	calc();
	return 0;
}