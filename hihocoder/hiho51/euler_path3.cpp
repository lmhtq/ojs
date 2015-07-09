#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>

using namespace std;

#define N 32768
int mp[N][2];
int n, num, off;

stack<int> S, R;
vector<int> V;

int powint(int d, int n) {
	int res = 1;
	for (int i = 0; i < n; i++) {
		res *= d;
	}
	return res;
}

void init()
{
	memset(mp, 0, sizeof(int) * N * 2);
	while (!S.empty()) {
		S.pop();
	}
	while (!R.empty()) {
		R.pop();
	}
	V.clear();

	scanf("%d", &n);
	num = powint(2, n-1);
	off = ~(1 << (n-1));
}

void construct()
{
	for (int i = 0; i < num; i++) {
		mp[i][0] = (i << 1) & (off);
		mp[i][1] = (i << 1) & (off) | 1;
	}
}

void dfs(int s)
{
	for (int i = 0; i < 2; i++) {
		int t = mp[s][i];
		if (t >= 0) {
			mp[s][i] = -1;
			dfs(t);
		}
	}
	S.push(s);
}

void fleury(int s)
{
	S.push(s);
	while (S.size() > 0) {
		int st = S.top();
		bool flag = true;
		if (mp[st][0] < 0 && mp[st][1] < 0) {
			flag = false;
		}
		if (flag) {
			S.pop();
			dfs(st);
		} else {
			S.pop();
			R.push(st);
		}
	}
}

void output()
{
	// for (int i = 0; i < num; i++) {
	// 	printf("%d %d\n%d %d\n\n", i, mp[i][0], i, mp[i][1]);
	// }
	while (!R.empty()) {
		V.push_back(R.top());
		R.pop();
	} 
	for (int i = V.size()-1; i > 0; i--) {
		int edge = (V[i] << 1) | (V[i-1] & 1);
		//printf("%d %d %d\n",V[i], V[i-1], edge);
		printf("%d", edge & 1);
	}
	printf("\n");
}

int main()
{
	init();
	construct();
	fleury(0);
	output();
	return 0;
}