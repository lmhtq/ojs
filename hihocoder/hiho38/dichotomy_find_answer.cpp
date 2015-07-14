#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

#define N 10002
#define K 10002
#define M 100002

int n, m, k, t;

struct Edge
{
	int to;
	int w;
};
struct Node
{
	vector<Edge> next;
} nodes[N];

queue<int> Q;
bool visited[N];

int res, maxw;

void init()
{
	scanf("%d%d%d%d", &n, &m, &k, &t);
	for (int i = 0; i <= n; i++) {
		nodes[i].next.clear();
	}
	maxw = -1;
	int a, b, v;
	Edge e;
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &a, &b, &v);
		e.to = b;
		e.w = v;
		nodes[a].next.push_back(e);
		e.to = a;
		nodes[b].next.push_back(e);
		if (v > maxw) {
			maxw = v;
		}
	}
}

bool f(int threshold) {
	while (!Q.empty()) {
		Q.pop();
	}
	memset(visited, 0, sizeof(visited));

	Q.push(1);
	visited[1] = true;
	int tmpk = k;
	while (!Q.empty()) {
		int u = Q.front();
		//printf("%d\n", u);
		Q.pop();
		for (int i = 0; i < nodes[u].next.size(); i++) {
			int v = nodes[u].next[i].to;
			int val = nodes[u].next[i].w;
			if (!visited[v] && threshold >= val) {
				visited[v] = true;
				if (v == t && tmpk > 0) {
					return true;
				}
				Q.push(v);
			}
			
		}
		tmpk--;
	}

	// if (t == 1 && visited[t] == true) {
	// 	return true;
	// }
	return false;
}

void divide()
{
	int left = 1;
	int right = maxw;
	int mid;
	while (left + 1 != right) {
		//printf("%d %d\n", left, right);
		mid = (left + right) / 2;
		//printf("%d %d %d \n", f(left), f(mid), f(right));
		bool l = f(left), m = f(mid), r = f(right);
		if ( l == m && m != r) {
			left = mid;
		}
		if (l != m && m == r) {
			right = mid;
		}
	}
	res = right;
}

void output()
{
	printf("%d\n", res);
}

int main()
{
	init();
	divide();
	output();
	return 0;
}