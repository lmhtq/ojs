#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>

using namespace std;

#define N 1001
#define M 5001

int n, m, start, num;

int mp[N][N];
int degree[N];

stack<int> S;
stack<int> R;

void init()
{
	memset(mp, 0, sizeof(int) * N * N);
	memset(degree, 0, sizeof(int) * N);
	while (!S.empty()) {
		S.pop();
	}
	while (!R.empty()) {
		R.pop();
	}
	start = 0;
	num = 0;

	scanf("%d%d", &n, &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		mp[a][b]++;
		mp[b][a]++;//ke neng you chong bian
		degree[a]++;
		degree[b]++;
	}

	for (int i = 1; i <= n; i++) {
		if (degree[i] % 2 == 1) {
			num++;
			start = i;
		}
	}
}

void dfs(int s) 
{
	//S.push(s);//WA here
	for (int j = 1; j <= n; j++) {
		if (mp[s][j] > 0 && mp[j][s] > 0) {
			mp[s][j]--;//ke neng you chong bian, suo yi bu neng zhi jie = 0
			mp[j][s]--;
			dfs(j);
			//break;//key position
		}
	}
	S.push(s);//AC here, because tui zhan caishi zhengque de shunxu
	
}

void fleury(int s)
{
	S.push(s);
	while (S.size() > 0) {//key
		bool flag = false;
		for (int j = 1; j <= n; j++) {
			if (mp[s][j] > 0) {
				flag = true;
				break;
			}
		}

		if (flag) {
			int r = S.top();//key position
			S.pop();
			dfs(r);
		} else {
			int r = S.top();
			S.pop();
			R.push(r);
		}
	}
	
}

void output()
{
	printf("%d", R.top());
	R.pop();
	while (!R.empty()) {
		printf(" %d", R.top());
		R.pop();
	}
	printf("\n");
}

int main()
{
	init();
	if (num == 2) {
		fleury(start);
	} else if (num == 0) {
		start = 1;
		for (; start <= n; start++) {
			bool flag = false;
			for (int jj = 0; jj <= n; jj++) {
				if (mp[start][jj] > 0) {
					flag = true;
					break;
				}
			}
			if (flag) {
				break;
			}
		}
		fleury(start);
	}
	output();
	return 0;
}