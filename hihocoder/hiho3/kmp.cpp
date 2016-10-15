#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> pattern_strs;
vector<string> origin_strs;
vector<int> result;
int n;

void input()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		string pat, ori;
		cin >> pat >> ori;
		pattern_strs.push_back(pat);
		origin_strs.push_back(ori);
	}
}

vector<int> calc_next(string &s)
{
	int slen = s.length();
	vector<int> next(slen+1);

	next[0] = 0;
	for (int i = 1; i <= slen; i++) {
		int j = next[i-1];
		while ((s[i] != s[j] || i == slen) && j != 0) {
			j = next[j-1];
		}

		if (s[i] == s[j]) {
			next[i] = j + 1;
		} else {
			next[i] = 0;
		}
	}


	// printf("next array: ");
	// for (int i = 0; i <= slen; i++) {
	// 	printf("%d ", next[i]);
	// }
	// printf("\n");
	return next;
}

void kmp(string &pat, string &ori) 
{
	int slen = pat.length();
	int olen = ori.length();
	vector<int> next = calc_next(pat);
	
	int cnt = 0;
	int j = 0;
	for (int i = 0; i < olen; i++) {
		if (pat[j] == ori[i]) {
			j++;
		} else {
			if (j > 0) {
				i--;
				j = next[j-1];
			}
		}

		if (j >= slen) {
			//printf("match index:%d\n", i - slen + 1);
			j = next[slen-1];
			//i = i - next[j-1];
			cnt++;
		}
	}
	result.push_back(cnt);
	//printf("cnt: %d\n", cnt);
}

void calc()
{
	for (int i = 0; i < n; i++) {
		kmp(pattern_strs[i], origin_strs[i]);
	}
}

void output()
{
	for (int i = 0; i < n; i++) {
		printf("%d\n", result[i]);
	}
}

int main()
{
	input();
	calc();
	output();
	return 0;
}