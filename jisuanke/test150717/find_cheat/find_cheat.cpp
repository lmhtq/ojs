#include <cstdio>
#include <cstring>

using namespace std;

#define N 1002
#define LEN 10
char s[N][LEN];
int n, m;
char tmp[LEN];
bool matched[N];

void init()
{
	scanf("%s%d", tmp, &n);
	for (int i = 0; i < n; i++) 
		scanf("%s", s[i]);
	m = 0;
	memset(matched, 0, sizeof(matched));
	//memset(s[0], 0, sizeof(char) * N * LEN);
}

bool match(char *src, char *dst)
{
	for (int i = 0; i < LEN - 1; i++) {
		if (dst[i] == '*') 
			continue;
		if (dst[i] != src[i]) {
			return false;
		}
	}
	return true;
}

void calc()
{
	for (int i = 0; i < n; i++) {
		if (match(s[i], tmp)) {
			m++;
			matched[i] = true;
		}
	}
}

void output()
{
	printf("%d\n", m);
	for (int i = 0; i < n; i++) {
		if (matched[i]) {
			printf("%s\n", s[i]);
		}
	}
}

int main()
{
	init();
	calc();
	output();
	return 0;
}