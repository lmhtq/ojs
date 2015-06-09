#include <cstdio>
#include <cstring>

using namespace std;
#define N 100
int a[N];
int num, res;
int main()
{
	scanf("%d", &num);
	for (int i = 0; i < num; i++) {
		scanf("%d", a + i);
	}
	res = a[0];
	for (int i = 1; i < num; i++) {
		res ^= a[i];
	}
	if (res) {
		printf("Alice\n");
	} else {
		printf("Bob\n");
	}
	return 0;
}