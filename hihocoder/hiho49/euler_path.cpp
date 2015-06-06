#include <stdio.h>
#include <string.h>
#include <map>
#include <vector>
#include <queue>

using namespace std;
#define N 10002
#define M 50002
int N_island, N_bridge;
int bridgs[M][2];
bool islands_label[N];
queue<int> Q;

struct Node {
	int id;
	int degree;
	vector<int> neigbors;
} islands[N];

void init()
{
	for (int i = 1; i <= N_island; i++ ) {
		islands[i].degree = 0;
	}
	for (int i = 0; i < N_bridge; i++) {
		int a = bridgs[i][0], b = bridgs[i][1];
		islands[a].degree++;
		islands[a].neigbors.push_back(b);
		islands[b].degree++;
		islands[b].neigbors.push_back(a);
	}
}

bool connected_cons()
{
	memset(islands_label, 0, sizeof(char) * N);
	while(!Q.empty()) {
		Q.pop();
	}
	int init = bridgs[0][0];
	Q.push(init);
	islands_label[init] = true;
	while (!Q.empty()) {
		int s = Q.front();
		Q.pop();
		for (int i = 0; i < islands[s].neigbors.size(); i++) {
			int e = islands[s].neigbors[i];
			if (islands_label[e]) {
				continue;
			} else {
				islands_label[e] = true;
				Q.push(e);
			}
		}
	}
	for (int i = 1; i <= N_island; i++) {
		if (islands_label[i] == false) {
			return false;
		}
	}
	return true;
}

bool degree_cons()
{
	int cnt = 0;
	for (int i = 1; i <= N_island; i++) {
		if (islands[i].degree % 2 == 1) {
			cnt++;
		}
	}
	if (cnt == 0 || cnt == 2) {
		return true;
	} else {
		return false;
	}
}

int main()
{
	scanf("%d%d", &N_island, &N_bridge);
	for (int i = 0; i < N_bridge; i++) {
		scanf("%d%d", bridgs[i], bridgs[i]+1);
	}
	init();
	if ( degree_cons() && connected_cons() ) {
		printf("Full\n");
	} else {
		printf("Part\n");
	}
	return 0;
}