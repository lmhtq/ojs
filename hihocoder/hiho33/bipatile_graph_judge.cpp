#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

#define N 10001
#define M 40001
int n, m, T;

struct Node
{
	vector<int> next;
} nodes[N];

int visited[N];
int edges[M][2];
queue<int> Q;

void init()
{
	scanf("%d%d", &n, &m);
	memset(visited, 0, sizeof(visited));
	memset(edges, 0, sizeof(int) * M * 2);
	for (int i = 0; i <= n; i++) {
		nodes[i].next.clear();
	}
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		nodes[a].next.push_back(b);
		nodes[b].next.push_back(a);
		edges[i][0] = a; edges[i][1] = b;
	}
	while (!Q.empty()) {
		Q.pop();
	}
	Q.push(a);
	visited[a] = 1;
}

void paint()
{
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (int i = 0; i < nodes[u].next.size(); i++) {
			int v = nodes[u].next[i];
			if (!visited[v]) {
				if (visited[u] == 1) visited[v] = 2;
				else if (visited[u] == 2) visited[v] = 1;
				Q.push(v);
			}
		}
	}
}

void output()
{
	for (int i = 0; i < m; i++) {
		if (visited[edges[i][0]] == visited[edges[i][1]]) {
			printf("Wrong\n");
			return;
		}
	}
	printf("Correct\n");
	return;
}

int main()
{
	scanf("%d", &T);
	while (T > 0) {
		init();
		paint();
		output();
		T--;
	}
	return 0;
}