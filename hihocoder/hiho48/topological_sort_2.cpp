#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
#define N 100002
#define M 500002
#define MOD 142857

int N_node, N_edges, N_virus;

struct Node {
	int in_degree;
	int n_virus;
	vector<int> neighbors;
} nodes[N];
bool flag[N];

queue<int> Q;

int virus_position[N];
int edges[M][2];

void init()
{
	for (int i = 0; i < N; i++) {
		nodes[i].in_degree = 0;
		nodes[i].n_virus = 0;
	}
	while(!Q.empty()) {
		Q.pop();
	}
	memset(flag, 0, sizeof(bool) * N);
}

void construct()
{
	for (int i = 0; i < N_virus; i++) {
		int j = virus_position[i];
		nodes[j].n_virus = 1;
	}
	for (int i = 0; i < N_edges; i++) {
		int a = edges[i][0], b = edges[i][1];
		nodes[a].neighbors.push_back(b);
		nodes[b].in_degree++;
	}
}

int get_start_node()
{
	for (int i = 1; i <= N_node; i++) {
		if (nodes[i].in_degree == 0) {
			Q.push(i);
			flag[i] = true;
		}
	}
}

void simulate()
{
	while (!Q.empty()) {
		int e = Q.front();
		Q.pop();
		//int num = nodes[e].n_virus;
		int num = nodes[e].n_virus % MOD;
		for (int i = 0; i < nodes[e].neighbors.size(); i++) {
			int en = nodes[e].neighbors[i];
			if (flag[en]) {
				continue;
			}
			nodes[en].in_degree--;
			//nodes[en].n_virus += num;
			nodes[en].n_virus += num;
			nodes[en].n_virus % MOD;
			if (nodes[en].in_degree == 0) {
				Q.push(en);
				flag[en] = true;
			}
		}
	}
}

int sum()
{
	int sum = 0, num;
	for (int i = 1; i <= N_node; i++) {
		num = nodes[i].n_virus % MOD;
		sum += num;
		sum %= MOD;
	}
	return sum;
}

int main()
{
	init();
	scanf("%d%d%d", &N_node, &N_edges, &N_virus);
	for (int i = 0; i < N_virus; i++) {
		scanf("%d", &virus_position[i]);
	}
	for (int i = 0; i < N_edges; i++) {
		scanf("%d%d", edges[i], edges[i] + 1);
	}
	construct();
	get_start_node();
	simulate();
	printf("%d\n", sum());
	return 0;
}