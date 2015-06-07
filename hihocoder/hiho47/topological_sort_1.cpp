#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;
#define T 6
#define N 100001
#define M 500001

int T_cases, N_node, N_edge;
struct Node{
	int in_degree;
	vector<int> next;
} nodes[N];
queue<int> Q;

void init()
{
	memset(nodes, 0, sizeof(Node) * N);//the commented content also runs.
	// for (int i = 0; i < N; i++) {
	// 	nodes[i].in_degree = 0;
	// 	nodes[i].next.clear();
	// }
	while (!Q.empty()) {
		Q.pop();
	}
}

void construct()
{
	scanf("%d%d", &N_node, &N_edge);
	for (int i = 0; i < N_edge; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		nodes[a].next.push_back(b);
		nodes[b].in_degree++;
	}
}

void simulate()
{
	for (int i = 1; i <= N_node; i++) {
		if (nodes[i].in_degree == 0) {
			Q.push(i);
		}
	}
	while(!Q.empty()) {
		int e = Q.front();
		Q.pop();
		for (int i = 0; i < nodes[e].next.size(); i++) {
			int en = nodes[e].next[i];
			nodes[en].in_degree--;
			if (nodes[en].in_degree == 0) {
				Q.push(en);
			}
		}
	}
}

bool check()
{
	for (int i = 1; i <= N_node; i++) {
		if (nodes[i].in_degree > 0) {
			return false;
		}
	}
	return true;
}

int main()
{
	scanf("%d", &T_cases);
	while(T_cases--) {
		init();
		construct();
		simulate();
		if (check()) {
			printf("Correct\n");
		} else {
			printf("Wrong\n");
		}
	}
	return 0;
}