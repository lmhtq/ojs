#include <cstdio>
#include <cstring>

using namespace std;

#define N 100000001
#define MOD 12357
#define L 8
#define MI 32
long n;

struct Mat
{
	long d[L][L];
	Mat operator * (const Mat &a) const {
		Mat mat;
		for (int i = 0; i < L; i++) {
			for (int j = 0; j < L; j++) {
				long sum = 0;
				for (int k = 0; k < L; k++) {
					long tmp = d[i][k]*a.d[k][j];
					tmp %= MOD;
					sum += tmp;
					sum %= MOD;
				}
				mat.d[i][j] = sum;
			}
		}
		return mat;
	}
	void put() {
		for (int i = 0; i < L; ++i)
		{
			for (int j = 0; j < L; ++j)
			{
				printf("%6ld", d[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
} mats[MI];

Mat M;

void init()
{
	long a[L][L] = {
		{0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 1, 0, 0, 1},
		{0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 1, 0}
	};
	memcpy(mats[0].d[0], a[0], sizeof(long)*L*L);
	for (int i = 1; i < MI; i++) {
		mats[i] = mats[i-1]*mats[i-1];
	}
	scanf("%ld", &n);
}

void calc()
{
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			if (i == j) M.d[i][j] = 1;
			else M.d[i][j] = 0;
		}
	}
	int i = 0;
	while (n > 0) {
		if (n % 2 == 1) {
			M = M * mats[i];
		}
		n /= 2;
		i++;
	}
}

void output()
{
	printf("%ld\n", M.d[L-1][L-1]);
	// mats[0].put();
	// mats[1].put();
	// mats[2].put();
}

int main()
{
	init();
	calc();
	output();
	return 0;
}