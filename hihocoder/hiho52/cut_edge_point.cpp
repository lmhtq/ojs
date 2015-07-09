#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define N 20001
#define M 100001
int n, m;
int num_cuts;
char visited[N];
int dfn[N];
int low[N];
int order;

struct Node
{
	int dfn;
	int low;
	int parent;
	vector<int> neighbors;
} nodes[N];

struct Edge
{
	int u;
	int v;
};

vector<Edge> cut_edges;
vector<int> cut_points;

void init()
{
	memset(visited, 0, sizeof(char) * N);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		nodes[i].dfn = 0;
		nodes[i].low = 0;
		nodes[i].parent = 0;
		nodes[i].neighbors.clear();
	}
	
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		nodes[a].neighbors.push_back(b);
		nodes[b].neighbors.push_back(a);
	}
	num_cuts = 0;
	order = 0;
}

void dfs(int s)
{
	order++;
	visited[s] = 1;
	nodes[s].dfn = order;
	nodes[s].low = order;
	int ch_tree = 0;

	for (int i = 0; i < nodes[s].neighbors.size(); i++) {
		int t = nodes[s].neighbors[i];
		if (!visited[t]) {
			ch_tree++;
			nodes[t].parent = s;
			dfs(t);
			nodes[s].low = min(nodes[s].low, nodes[t].low);

			if (nodes[s].parent == 0 && ch_tree >= 2) {
				bool flag = true;
				for (int j = 0; j < cut_points.size(); j++) {//chong fu dian
					if (s == cut_points[j]) {
						flag = false;
						break;
					}
				}
				if (flag) {
					cut_points.push_back(s);
				}
			}

			if (nodes[s].parent && nodes[t].low >= nodes[s].dfn) {
				bool flag = true;
				for (int j = 0; j < cut_points.size(); j++) {//chong fu dian
					if (s == cut_points[j]) {
						flag = false;
						break;
					}
				}
				if (flag) {
					cut_points.push_back(s);
				}
			}

			if (nodes[t].low > nodes[s].dfn) {
				Edge e;
				if (s < t) {//key
					e.u = s; e.v = t;
				} else {
					e.u = t; e.v = s;
				}
				bool flag = true;
				for (int i = 0; i < cut_edges.size(); i++ ) {
					Edge ce = cut_edges[i];
					if (ce.u == e.u && ce.v == e.v) {
						flag = false;
						break;
					}
				}
				if (flag) {
					cut_edges.push_back(e);
				}
			}

		} else {
			if (t != nodes[s].parent) {//key position
				nodes[s].low = min(nodes[s].low, nodes[t].dfn);
			}
		}
	}

}

bool cmp(const Edge &a, const Edge &b)
{
	if (a.u != b.u) {
		return a.u < b.u;
	} else {
		return a.v < b.v;
	}
}

void output()
{
	sort(cut_points.begin(), cut_points.end());
	for (int i = 0; i < cut_points.size(); i++) {
		printf("%d%c", cut_points[i], i == (cut_points.size()-1) ? '\n' : ' ');
	}
	if (cut_points.size() < 1 ) {//forget it!!!!
		printf("Null\n");
	}
	sort(cut_edges.begin(), cut_edges.end(), cmp);
	for (int i = 0; i < cut_edges.size(); i++) {
		printf("%d %d\n", cut_edges[i].u, cut_edges[i].v);
	}
}

int main()
{
	init();
	dfs(1);
	output();
	return 0;
}