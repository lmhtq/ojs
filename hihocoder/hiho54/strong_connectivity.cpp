#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#include <set>
#include <queue>
#include <map>

using namespace std;

#define N 20005
#define M 100005

int n, m;
int grass[N];
pair<int, int> E[M];
vector<int> G[N];
int dfn[N];
int low[N];

int mystack[N], top;

int belong[N];
int grass2[N];
int grass2_extra[N];
vector<int> G2[N];
int in_degree2[N];
bool visited[N];
int order, new_id;

queue<int> Q;
int res;

void init()
{
	for (int i = 0; i < N; i++)
		G[i].clear();
	for (int i = 0; i < N; i++)
		G2[i].clear();
	top = 0;
	memset(grass, 0, sizeof(grass));
	memset(grass2, 0, sizeof(grass2));
	memset(grass2_extra, 0, sizeof(grass2_extra));
	memset(belong, 0, sizeof(belong));
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(in_degree2, 0, sizeof(in_degree2));
	memset(visited, false, sizeof(visited));
	order = 0;
	new_id = 0;
	res = 0;
	while (!Q.empty())
		Q.pop();

	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", grass + i);
	for (int i = 0; i < m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		E[i].first = u, E[i].second = v;
		G[u].push_back(v);
	}
}

bool in_stack(int v)
{
	for (int i = 0 ; i < top; i++) {
		if (mystack[i] == v)
			return true;
	}
	return false;
}

void tarjan(int u)
{
	low[u] = dfn[u] = ++order;
	mystack[top++] = u;
	visited[u] = true;
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (!visited[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (in_stack(v)) {
			low[u] = min(low[u], dfn[v]);
		}
	}

	if (low[u] == dfn[u]) {
		new_id++;
		while (top >= 0) {
			int j = mystack[--top];
			belong[j] = new_id;
			grass2[new_id] += grass[j];
			if (j == u)
				break;
		}
	}
}

void reconstruct()
{
	for (int i = 0; i < m; i++) {
		int u = belong[E[i].first];
		int v = belong[E[i].second];
		if (u == 0 || v == 0)
			continue;
		if (u != v) {
			for (int j = 0; j < G2[u].size(); j++) {
				if (v == G2[u][j]) {
					continue;
				}
			}
			G2[u].push_back(v);
			in_degree2[v]++;
		}
	}
	memset(visited, false, sizeof(visited));
}

void topology_sort()//WA, FUCK ERR
{
	Q.push(belong[1]);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		res = max(res, grass2[u] + grass2_extra[u]);
		for (int i = 0; i < G2[u].size(); ++i) {
			int v = G2[u][i];
			//grass2[v] += grass2[u]; ERR
			grass2_extra[v] = max(grass2_extra[v], grass2_extra[u] + grass2[u]);//AC
			in_degree2[v]--;
			if (in_degree2[v] == 0) {
				Q.push(v);
			}
		}
	}
}

void dfs(int u, int sum)
{
	res = max(res, sum);
	for (int i = 0; i < G2[u].size(); i++) {
		int v = G2[u][i];
		if (!visited[v]) {
			visited[v] = true;
			dfs(v, sum + grass2[v]);
			visited[v] = false;
		}

	}
}

void output()
{
	printf("%d\n", res);
}

int main()
{
	init();
	tarjan(1);
	reconstruct();
	topology_sort();
	//dfs(belong[1], grass2[belong[1]]);
	output();
	return 0;
}