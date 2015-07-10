#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
#define N 20001
#define M 100001

struct Edge
{
	int u, v;
	bool operator < (const Edge &a) const {
		if (u != a.u) {
			return u < a.u;
		} else {
			return v < a.v;
		}
	}	
};

struct Node
{
	int dfn;
	int low;
	int parent;
	vector<int> neighbors;
} nodes[N];

struct Pair
{
	int id;
	int gid;
};

set<Edge> cut_edges;
stack<int> S;
vector<Pair> R, tmp;

int n, m, order;
bool visited[N];

void init()
{
	memset(nodes, 0, sizeof(nodes));
	memset(visited, 0, sizeof(visited));
	cut_edges.clear();
	while (!S.empty()) {S.pop();}

	order = 0;

	scanf("%d%d", &n, &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		nodes[a].neighbors.push_back(b);
		nodes[b].neighbors.push_back(a);
	}

}

void dfs(int u) {
	order++;
	nodes[u].dfn = nodes[u].low = order;
	visited[u] = true;
	int ch_tree = 0;
	S.push(u);
	for (int i = 0; i < nodes[u].neighbors.size(); i++) {
		int v = nodes[u].neighbors[i];
		if (!visited[v]) {
			ch_tree++;
			nodes[v].parent = u;
			dfs(v);

			nodes[u].low = min(nodes[u].low, nodes[v].low);

			// if (parent[u] == 0 && ch_tree >= 2) {

			// }
			// if (parent[u] && nodes[v].low >= nodes[u].dfn) {

			// }
			if (nodes[v].low > nodes[u].dfn) {
				Edge e;
				e.u = min(u, v); e.v = max(u, v);
				cut_edges.insert(e);
			}

		} else {
			if (nodes[u].parent != v) {
				nodes[u].low = min(nodes[u].low, nodes[v].dfn);
			}
		}
	}

	if (nodes[u].dfn == nodes[u].low) {//key position, put here AC.
		Pair p;
		while (!S.empty()) {
			int d = S.top();
			//bool flag = (nodes[d].dfn == nodes[d].low);
			p.id = p.gid = d;
			tmp.push_back(p);
			S.pop();
			if (d == u) {//key position
				break;
			}
		}
		int gid = N + 2;
		for (int i = 0; i < tmp.size(); i++) {
			if (tmp[i].id < gid) {
				gid = tmp[i].id;
			}
		}
		for (int i = 0; i < tmp.size(); i++) {
			tmp[i].gid = gid;
			R.push_back(tmp[i]);
		}
		tmp.clear();
			
	}
	
}

bool cmp(const Pair &a, const Pair &b)
{
	return a.id < b.id;
}

void output()
{
	printf("%d\n", (int)cut_edges.size() + 1);
	// Pair p;
	// while (!S.empty()) {
	// 	int d = S.top();
	// 	bool flag = (nodes[d].dfn == nodes[d].low);
	// 	p.id = p.gid = d;
	// 	tmp.push_back(p);
	// 	if (flag) {
	// 		int gid = N + 2;
	// 		for (int i = 0; i < tmp.size(); i++) {
	// 			if (tmp[i].id < gid) {
	// 				gid = tmp[i].id;
	// 			}
	// 		}
	// 		for (int i = 0; i < tmp.size(); i++) {
	// 			tmp[i].gid = gid;
	// 			R.push_back(tmp[i]);
	// 		}
	// 		tmp.clear();
	// 	}
	// 	S.pop();
	// }
	sort(R.begin(), R.end(), cmp);
	for (int i = 0; i < R.size(); ++i)
	{
		printf("%d%c", R[i].gid, i == R.size()-1 ? '\n':' ');
	}
}

int main()
{
	init();
	dfs(1);
	output();
	return 0;
}