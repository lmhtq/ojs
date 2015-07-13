#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#include <set>
#include <queue>

using namespace std;

#define N 20001
#define M 100001

int n, m;

struct Node
{
	int grass;
	int low, dfn;
	int in_dgree;
	set<int> next;
} nodes[N], nodes2[N];

bool visited[N];
int trans[N];
int mystack[N+2], top = 0;

vector<int> tmp;
queue<int> Q;
//set<int>::iterator it;//Error, use local variable will be AC

void init()
{
	scanf("%d%d", &n, &m);
	// memset(nodes, 0, sizeof(nodes));//Error
	// memset(nodes2, 0, sizeof(nodes2));//Error
	for (int i = 0; i <= n; i++) {
		nodes[i].grass = nodes[i].low = nodes[i].dfn = nodes[i].in_dgree = 0;
		nodes[i].next.clear();
	}
	for (int i = 0; i <= n; i++) {
		nodes2[i].grass = nodes2[i].low = nodes2[i].dfn = nodes2[i].in_dgree = 0;
		nodes2[i].next.clear();
	}
	memset(visited, 0, sizeof(visited));
	memset(mystack, 0, sizeof(mystack));
	for (int i = 0; i < N; i++) {
		trans[i] = i;
	}
	while (!Q.empty()) Q.pop();
	for (int i = 1 ; i <= n; i++) {
		scanf("%d", &nodes[i].grass);
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		nodes[a].next.insert(b);
		//nodes[b].in_dgree++;
	}
	// Q.push(1);
	// while(!Q.empty()) {
	// 	int u = Q.front();
	// 	visited[u] = true;
	// 	Q.pop();
	// 	set<int>::iterator it;
	// 	for (it = nodes[u].next.begin(); it != nodes[u].next.end(); it++) {
	// 		int v = *it;
	// 		visited[v] = true;
	// 		if (nodes[v].in_dgree <= 0) {
	// 			continue;
	// 		}
	// 		nodes2[v].in_dgree--;
	// 		nodes2[v].grass += nodes2[u].grass;
	// 		if (nodes2[v].in_dgree == 0) {
	// 			Q.push(v);
	// 		}
	// 	}
	// }
	// for (int i = 1; i <= n; i++) {
	// 	if (!visited[i]) {
	// 		nodes[i].grass = 0;
	// 	}
	// }
	// memset(visited, 0, sizeof(visited));
}

bool in_stack(int e, int arr[])
{
	for (int i = 0; i < top; i++) {
		if (e == arr[i]) {
			return true;
		}
	}
	return false;
}

int order = 0;
void tarjan(int u)
{
	order++;
	nodes[u].low = nodes[u].dfn = order;
	visited[u] = true;
	mystack[top++] = u;
	set<int>::iterator it;
	for (it = nodes[u].next.begin(); it != nodes[u].next.end(); ++it) {
		//printf("%d\n", *it);
		int v = *it;
		if (!visited[v]) {
			tarjan(v);
			nodes[u].low = min(nodes[u].low, nodes[v].low);
		} else {
			if (in_stack(u, mystack)) {
				nodes[u].low = min(nodes[u].low, nodes[v].dfn);
			}
		}
	}
	
	if (nodes[u].low == nodes[u].dfn) {
		tmp.clear();
		while (top > 0) {
			//printf("%d ", mystack[--top]);
			tmp.push_back(mystack[--top]);
			if (mystack[top] == u) {
				break;
			}
		}
		//printf("\n\n");
		int min = N + 2;
		for (int i = 0; i < tmp.size(); i++) {
			if (tmp[i] < min) {
				min = tmp[i];
			}
		}
		for (int i = 0; i < tmp.size(); i++) {
			trans[tmp[i]] = min;
		}
	}
}

void construct()
{
	for (int u = 1; u <= n; u++) {
		int new_node = trans[u];
		if (new_node <= 0) {
			continue;
		}
		nodes2[new_node].grass += nodes[u].grass;
		set<int>::iterator it;
		for (it = nodes[u].next.begin(); it != nodes[u].next.end(); it++) {
			int v = *it;
			int e = trans[v];
			nodes2[new_node].next.insert(e);
			nodes2[e].in_dgree++;
			if (e == u || e == new_node) {//key
				nodes2[e].in_dgree--;
			}
			
		}
	}
}

set<int> keda;
void topology_sort()
{
	// for (int i = 1; i <= n; i++) {
	// 	//printf("%d:%d\n", i, nodes2[i].in_dgree);
	// 	if (nodes2[i].in_dgree == 0) {
	// 		Q.push(i);
	// 	}
	// }
	Q.push(1);
	keda.insert(1);
	while (!Q.empty()) {
		int u = Q.front();
		keda.insert(u);
		Q.pop();
		set<int>::iterator it;
		for (it = nodes2[u].next.begin(); it != nodes2[u].next.end(); it++) {
			int v = *it;
			keda.insert(v);
			if (nodes2[v].in_dgree <= 0) {
				continue;
			}
			nodes2[v].in_dgree--;
			nodes2[v].grass += nodes2[u].grass;
			if (nodes2[v].in_dgree == 0) {
				Q.push(v);
			}
		}
	}
}

void output()
{
	int max = -1;
	set<int>::iterator it;
	for (it = keda.begin(); it != keda.end(); it++) {
		int i = *it;
		//printf("%d:%d\n", i, nodes2[i].grass);
		if (max < nodes2[i].grass) {
			max = nodes2[i].grass;
		}
	}
	printf("%d\n", max);
}

int main()
{
	init();
	tarjan(1);
	construct();
	topology_sort();
	output();
	return 0;
}