#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;
#define N 1002
#define M 5002
struct Node
{
	vector<int> next;
} nodes[N];

int matched[N];
bool searched[N];

int res, n, m;

void init()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++) 
		nodes[i].next.clear();
	memset(matched, 0, sizeof(matched));
	memset(searched, 0, sizeof(searched));
	res = 0;
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		nodes[a].next.push_back(b);
		nodes[b].next.push_back(a);
	}
}

bool findpath(int u) {
	for (int i = 0; i < nodes[u].next.size(); i++) {
		int v = nodes[u].next[i];
		if (!searched[v]) {
			searched[v] = true;
			if (!matched[v] || findpath(matched[v])) {
				matched[u] = v;
				matched[v] = u;
				return true;
			}
		}
	}
	return false;
}

void calc()
{
	for (int i = 1; i <= n; i++) {
		if (matched[i]) {
			continue;
		}
		memset(searched, 0, sizeof(searched));
		if (findpath(i)) {
			res++;
		}
	}
}

void output()
{
	printf("%d\n%d\n", res, n - res);
}

int main()
{
	init();
	calc();
	output();
	return 0;
}