#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
#define N 31
#define M 31
int U[N][M];
int W[N][M];
int Max[N][M];
int C[N][M];
int n, m, k, ans, res, cnt;
bool visited[N][M];
struct Node
{
	int i, j;
};
queue<Node> Q;

void init()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) { 
			scanf("%d", &U[i][j]);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) { 
			scanf("%d", &W[i][j]);
		}
	}
	// for (int i = 1; i <= 2; i++) {
	// 	for (int j = 1; j <= 2; j++) { 
	// 		scanf("%d", &C[i][j]);
	// 	}
	// }
	res = ans = 1000000;
	cnt = 0;
}

int chengben(int i, int j) {
	int c = C[i][j];
	c += (i+j);
	if (c < 0) {
		c = -c;
	}
	c ^= U[i][j];
	return c * W[i][j];
}

int chengben2(int c1, int c2) {
	c1 += c2;
	if (c1 < 0) {
		return -c1;
	}
	return c1;
}

void calc_each()
{
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			ans += chengben(i, j);
		}
	}
}

void calc_neighbors()
{
	for (int i = 1; i  <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (i + 1 <= n) {
				ans += chengben2(C[i][j], C[i+1][j]);
			}
			if (j + 1 <= n) {
				ans += chengben2(C[i][j], C[i][j+1]);
			}
		}
	}
}

void dfs(int i, int j, int c) {
	if ( i == n && j == m) {
		ans = 0;
		cnt++;
		calc_each();
		calc_neighbors();
		if (ans < res) {
			res = ans;
		}
		// for (int ii = 1; ii <= n; ii++) {
		// 	for (int jj = 1; jj <= m; jj++ ) {
		// 		printf("%4d", C[ii][jj]);
		// 	}
		// 	printf("\n");
		// }
		// printf("%d\n\n", ans);
	}
	//printf("%d %d\n", i, j);
	for (int ii = 1; ii <= n; ii++) {
		for (int jj = 1; jj <= m; jj++) {
			if (!visited[ii][jj]) {
				for (int k1 = -k; k1 <= k; k1++) {
					visited[ii][jj] = true;
					//ans = min(ans, chengben(k1,i,j));
					C[ii][jj] = k1;
					dfs(ii, jj, k1);
					visited[ii][jj] = false;
				}
			}
		}
	}
}

void calc()
{
	for (int k1 = -k; k1 <= k; k1++) {
		//printf("dfs\n");
		memset(visited, 0, sizeof(visited));
		visited[1][1] = true;
		//ans = min(ans, chengben(k1,1,1));
		C[1][1] = k1;		
		dfs(1, 1, k1);
		//visited[1][1] = false;
		//memset(visited, 0, sizeof(visited));
	}
}

void output()
{
	//printf("%d\ncnt:%d\n", res, cnt);
	printf("%d\n", res);
}

int main()
{
	init();
	calc();
	output();
	return 0;
}