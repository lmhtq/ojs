#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
	int num;
	int res;
	scanf("%d%d", &num, &res);
	for (int i = 1; i < num; i++) {
		int tmp;
		scanf("%d", &tmp);
		res ^= tmp;
	}
	if (res) {
		printf("Alice\n");
	} else {
		printf("Bob\n");
	}
	return 0;
}