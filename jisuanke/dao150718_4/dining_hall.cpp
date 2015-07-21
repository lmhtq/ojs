#include <cstdio>
#include <cstring>

using namespace std;
#define MAX 128
#define MOD 1000000007
#define MI 32
int k, dim, num, T;

struct Mat
{
	long d[MAX][MAX];
	Mat operator * (const Mat &a) const {
		Mat ret;
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				int sum = 0;
				for (int k = 0; k < dim; k++) {
					long tmp = d[i][k] * a.d[k][j];
					//long tmp = d[j][k] * a.d[k][j];//Error
					tmp %= MOD;
					sum += tmp;
					sum %= MOD;
				}
				ret.d[i][j] = sum;
			}
		}
		return ret;
	}
	void put() {
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				printf("%5ld", d[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
} mats[MI], res;

long pow2(int d, int num) 
{
	int s = 1;
	while (num > 0) {
		s *= d;
		num--;
	}
	return s;
}

void init()
{	
	k = 4;
	dim = pow2(2, 4);
	memset(mats, 0, sizeof(Mat) * MI);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; ++j) {
			if (i == j) res.d[i][j] = 1;
			else res.d[i][j] = 0;
		}
	}
	//res.put();
}

void dfs(int x, int y, int col)
{
	//printf("%ld %ld %ld\n", x, y , col);
	//if (col == dim) {Error
	//if (col == num) {Error
	if (col == k) {
		mats[0].d[y][x] = 1;
		return;
	}
	dfs(x << 1, (y << 1) + 1, col + 1);//key position
	dfs((x << 1) + 1, y << 1, col + 1);//key position
	if (col + 2 <= k) {
		dfs((x << 2) + 3, (y << 2) + 3, col + 2 );
	}
}

void construct()
{
	dfs(0,0,0);
	//mats[0].put();
	for (int i = 1; i < MI; i++) {
		mats[i] = mats[i-1] * mats[i-1];
	}
}

void calc()
{
	int i = 0;
	while (num > 0) {
		if (num % 2 == 1) {
			res = res * mats[i];
			//res.put();
		}
		i++;
		num /= 2;
	}
}

return output()
{
	return res.d[dim-1][dim-1] % MOD;
	//printf("%ld\n", res.d[dim-1][dim-1] % MOD);
}

int main()
{
	init();
	construct();
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &num);
		calc();
		output();
	}
	
	return 0;
}