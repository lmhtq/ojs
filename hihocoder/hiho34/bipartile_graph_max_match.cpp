#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

#define N 1002
#define M 5002

struct Node
{
	vector<int> next;
} nodes[N];

bool searched[N];
int matched[N];
bool visited[N];
int flag[N];

queue<int> Q;

int n, m, res;

void init()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++) 
		nodes[i].next.clear();
	memset(searched, 0, sizeof(searched));
	memset(matched, 0, sizeof(matched));
	memset(visited, 0, sizeof(visited));
	memset(flag, 0, sizeof(flag));
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		nodes[a].next.push_back(b);
		nodes[b].next.push_back(a);
	}
	res = 0;
	while(!Q.empty()) {
		Q.pop();
	}
	Q.push(a);
	flag[a] = 1;
	visited[a] = true;
}

void paint()
{
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (int i = 0; i < nodes[u].next.size(); i++) {
			int v = nodes[u].next[i];
			if (!visited[v]) {
				visited[v] = true;
				if (flag[u] == 1) flag[v] = 2;
				else if (flag[u] == 2) flag[v] = 1;
				Q.push(v);
			}
		}
	}
}

bool findpath(int u)
{
	for (int i = 0; i < nodes[u].next.size(); i++) {
		int v = nodes[u].next[i];
		if (!searched[v]) {// && flag[u] != flag[v]) {
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
		bool falg = findpath(i);
		if (falg) {
			res++;
		}
		//searched[i] = true;
	}
}

void output()
{
	printf("%d\n", res);
}

int main()
{
	init();
	//paint();
	calc();
	output();
	return 0;
}