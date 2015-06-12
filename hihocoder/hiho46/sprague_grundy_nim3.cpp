#include <cstdio>
#include <cstring>
#include <queue>
#include <cstring>

#define N 20001
int sg[N], hash[N];
int stones[N], num, res;

void Calc_SG()
{
	sg[0] = 0;
	sg[1] = 1;
	for (int i = 2; i < N; i++) {
		memset(hash, 0, sizeof(int) * N);
		hash[sg[0]] = 1;
		hash[sg[1]] = 1;
		for (int j = 2; j < i; j++) {
			hash[sg[j]] = 1;
		}
		for (int j = 1; j <= i/2; j++) {
			hash[sg[j] ^ sg[i-j]] = 1;
		}
		for (int j = 1; j <= i+1; j++) {
			if (hash[j] == 0) {
				sg[i] = j;
				break;
			}
		}
	}
	// for (int i = 0; i < N; i++) {
	// 	printf("%3d%c", i, i==(N-1) ? '\n':' ');
	// }
	// for (int i = 0; i < N; i++) {
	// 	printf("%3d%c", sg[i], i==(N-1) ? '\n':' ');
	// }
}

int main()
{
	Calc_SG();
	scanf("%d", &num);
	for (int i = 0; i < num; i++) {
		scanf("%d", stones + i);
	}
	res = sg[stones[0]];
	for (int i = 1; i < num; i++) {
		res ^= sg[stones[i]];
	}
	if (res) {
		printf("Alice\n");
	} else {
		printf("Bob\n");
	}
	return 0;
}