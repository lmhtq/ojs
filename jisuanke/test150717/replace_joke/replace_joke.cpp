#include <cstdio>
#include <cstring>
#include <stack>

using namespace std;
#define N 102
char s[N];
bool num[N];
int slen, n;
stack<int> S, R;
bool done;

void init()
{
	scanf("%s", s);
	memset(num, 0, sizeof(num));
	slen = strlen(s);
	n = ( slen + 9 ) / 2;
	done = false;
}

void search(char *p)
{
	if (*p == 0) {
		while (!S.empty()) {
			int top = S.top();
			S.pop();
			R.push(top);
		}
		done = true;
		//return true;
	}
	int d;
	sscanf(p, "%1d", &d);
	//printf("1:%d\n", d);
	if (!num[d] && d <= n) {
		num[d] = true;
		S.push(d);
		search(p+1);
		if (done) {
			return;
		}
		//printf("back\n");
		num[d] = false;
		S.pop();
	}
	sscanf(p, "%2d", &d);
	//printf("2:%d\n", d);
	if (!num[d] && d <= n) {
		num[d] = true;
		S.push(d);
		search(p+2);
		if (done) {
			return;
		}
		//printf("back\n");
		num[d] = false;
		S.pop();
	}
	//return false;
}

void output()
{
	while (!R.empty()) {
		int top = R.top();
		R.pop();
		printf("%d%c", top, R.size() == 0 ? '\n' : ' ');
	}
}

int main()
{
	init();
	search(s);
	output();
	return 0;
}