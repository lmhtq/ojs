#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAX 1000006
int T;
char s[MAX];
int slen, ret;
char ss[MAX*2];
int sslen;
int  P[MAX*2];

void change()
{
	int j = 0;
	ss[j++] = '@';
	for (int i = 0; i < slen; i++) {
		ss[j++] = '#';
		ss[j++] = s[i];
	}
	ss[j++] = '#';	
	sslen = j;
	ss[j++] = '\0';
}

void manacher()
{
	int i, maxid = 0, mid = 0;
	for (i = 0; i < sslen; i++) {
		if (i >= maxid) {
			P[i] = 1;
		} else {
			P[i] = min(P[mid * 2 - i], maxid - i);
		}
		while (i - P[i] >= 0 && ss[i-P[i]] == ss[i+P[i]]) {
			P[i]++;
		}
		if (i + P[i] > maxid) {
			maxid = i + P[i];
			mid = i;
		}

	}
}

void calc()
{
	slen = strlen(s);
	change();
	manacher();
	for (int i = 0; i < sslen; i++) {
		if (ret < P[i]) {
			ret = P[i];
		}
	}
}

int main()
{
	scanf("%d", &T);
	while (T--) {
		ret = 0;
		scanf("%s", s);
		calc();
		printf("%d\n", ret - 1);
	}
	return 0;
}