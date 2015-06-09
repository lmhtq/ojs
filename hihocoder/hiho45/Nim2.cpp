#include <cstdio>
#include <cstring>
#define N 10001

char s[N];
int num, res;

int main()
{
	scanf("%d%s", &num, s);
	res = 0;
	for (int i = 1; i <= num; i++) {//from 1
		if (s[i-1] == 'H') {
			res ^= i;
		}
	}
	if (res) {
		printf("Alice\n");
	} else {
		printf("Bob\n");
	}
	return 0;
}