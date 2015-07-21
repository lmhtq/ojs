#include <iostream>  
#include <cstdio>  
#include <cstdlib>  
#include <cstring>  
#include <string>  
#include <queue>  
#include <algorithm>  
#include <map>  
#include <iomanip>  
using namespace std;

#define N 100002
#define M 100002
#define Err 1000
int n, m;
int imgs[N];
int tmp[2*N];
int p[2*N];
int query[M][2];

void init()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", imgs + i);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d%d", query[i], query[i] + 1);
	}
}

void calc(int len)
{
	int id = 0, maxlen = 0;
	for (int i = 2; i < 2 * len + 1; i++) {
		if(p[id] + id > i) {
			p[i] = min(p[2*id-i], p[id]+id-i);  
		} else {
			p[i]=1;
		}  
		while(tmp[i-p[i]] == tmp[i+p[i]]) {
			++p[i];
		}  
		if(id + p[id] < i + p[i]) {
			id=i; 
		}
		if(maxlen < p[i]) {
			maxlen = p[i];
		}
	}
	//printf("maxlen:%d\n", maxlen-1);
}

void set(int l, int r)
{
	memset(tmp, 0, sizeof(tmp));
	int i, j;
	for (i = 0, j = l; j <= r; i++, j++ ) {
		tmp[i] = imgs[j-1];
	}
	int nn = i;
	for (i = nn; i >= 0; i--) {
		tmp[i+i+2] = tmp[i];
		tmp[i+i+1] = Err;
	}
	tmp[0] = Err*2;
	memset(p, 0, sizeof(p));
	
}

void output()
{
	// for (int i = 0; i <= 2*n+1; i++) {
	// 	printf("%6d", tmp[i]);
	// }
	// printf("\n");
	// for (int i = 0; i < 2*n+1; i++) {
	// 	printf("%6d", p[i]);
	// }
	//printf("\n");
	for (int i = 0; i < m; i++) {
		int ans = 0;
		set(query[i][0], query[i][1]);
		int nn = query[i][1] - query[i][0] + 1;
		calc(nn);
		// for (int ii = 0; ii <= 2*nn+1; ii++) {
		// 	printf("%6d", tmp[ii]);
		// }
		// printf("\n");
		// for (int ii = 0; ii < 2*nn+1; ii++) {
		// 	printf("%6d", p[ii]);
		// }
		// printf("\n");
		for (int j = 1; j <= nn; j++) {
			int cen = 2*j+0;
			// ans += tmp[cen];
			// printf("a%d %4d\n",cen, ans );
			int rad = p[cen] / 2;
			for (int d = 0; d <=  rad; d+=2) {
				if (tmp[cen-d] == tmp[cen+d] && tmp[cen-d] != Err) {
					if (d == 0) {
						ans += tmp[cen-d]*(rad-d);
					} else {
						ans += tmp[cen-d]*2*(rad-d/2);
					}
					//printf("a%d %4d\n", d, ans);
				}
			}
		}
		for (int j = 0; j <= nn; j++) {
			int cen = 2*j-1;
			//printf("b%4d\n",cen );
			int rad = p[cen] / 2;
			for (int d = 1; d <=  rad; d+=2) {
				if (tmp[cen-d] == tmp[cen+d] && tmp[cen-d] != Err) {
					ans += tmp[cen-d]*2*(rad-d/2);
				}
			}
		}
		printf("%d\n", ans);
	}
}

int main()
{
	init();
	//calc();
	output();
	return 0;
}