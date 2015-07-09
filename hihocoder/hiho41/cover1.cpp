#include <cstdio>
#include <cstring>
#define N 60
#define MOD 19999997
long mat[N][4];

void init()
{
	mat[0][0] = 0;
	mat[0][1] = mat[0][2] = mat[0][3] = 1;
	for (long i = 1; i < N; i++) {
		mat[i][0] = ((mat[i-1][0] * mat[i-1][0]) % MOD + (mat[i-1][1] * mat[i-1][2]) % MOD ) % MOD;
		mat[i][1] = ((mat[i-1][0] * mat[i-1][1]) % MOD + (mat[i-1][1] * mat[i-1][3]) % MOD ) % MOD;
		mat[i][2] = ((mat[i-1][2] * mat[i-1][0]) % MOD + (mat[i-1][3] * mat[i-1][2]) % MOD ) % MOD;
		mat[i][3] = ((mat[i-1][2] * mat[i-1][1]) % MOD + (mat[i-1][3] * mat[i-1][3]) % MOD ) % MOD;			
	}
}

// a *= b
void multipy(long  a[], long b[]) {
	long c[4];
	c[0] = ((a[0] * b[0]) % MOD + (a[1] * b[2]) % MOD ) % MOD;
	c[1] = ((a[0] * b[1]) % MOD + (a[1] * b[3]) % MOD ) % MOD;
	c[2] = ((a[2] * b[0]) % MOD + (a[3] * b[2]) % MOD ) % MOD;
	c[3] = ((a[2] * b[1]) % MOD + (a[3] * b[3]) % MOD ) % MOD;			
	memcpy (a, c, sizeof(long) * 4);
}

int main()
{
	init();
	long num, i = 0, j = 0;
	scanf("%ld", &num);
	long tmat[4] = {1,1,1,1};
	num-=1;
	while (num) {
		long re = num % 2;
		if (re == 1) {
			multipy(tmat, mat[i]);
		}
		num /= 2;
		i++;
	}
	long f0 = 0, f1 = 1;
	long fn = ((f0 * tmat[0]) % MOD + (f1 * tmat[1]) % MOD ) % MOD;
	printf("%ld\n", fn);
	return 0;
}