#include <cstdio>
#include <cstring>
using namespace std;
int T;
int y,m,d;
int cnt, day_cnt;
int num[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int mon[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//             0  1   2    3   4   5  6   7   8   9   10  11  12
int years[3000];
int montths[13];
int days[32];

int bihua(int x) {
	int sum = 0;
	while (x > 0) {
		sum += num[x % 10];
		x /= 10;
	}
	return sum;
}

void init0()
{
	for (int i = 0; i < 10; i++) {
		years[i] = num[0] * 3 + bihua(i);
	}
	for (int i = 10; i < 100; i++) {
		years[i] = num[0] * 2 + bihua(i);
	}
	for (int i = 100; i < 1000; i++) {
		years[i] = num[0] + bihua(i);
	}
	for (int i = 1000; i < 3000; i++) {
		years[i] = bihua(i);
	}
	for (int i = 1; i < 10; i++) {
		montths[i] = num[0] + bihua(i);
	}
	for (int i = 10; i <= 12; i++) {
		montths[i] = bihua(i);
	}
	for (int i = 1; i < 10; i++) {
		days[i] = bihua(i) + num[0];
		//printf("days[%d]=%d\n",i,days[i] );
	}
	for (int i = 10; i < 32; i++) {
		days[i] = bihua(i);
		//printf("days[%d]=%d\n",i,days[i] );
	}

}

void init()
{
	scanf("%4d%2d%2d%d", &y, &m, &d, &cnt);
	//printf("%d %d %d %d\n", y, m, d, cnt);
	day_cnt = 0;
}

bool isLeap(int x)
{
	if((x%4==0 && x%100!=0) || x%400==0)
		return true;
	else 
		return false;
}

int calc()
{
	int ans = 0;
	if (isLeap(y)) {
		mon[2] = 29;
	} else {
		mon[2] = 28;
	}
	ans = years[y] + montths[m] + days[d];
	if (ans == cnt) {
		return 0;
	}
	for (int dd = d + 1; dd <= mon[m]; dd++) {
		if (y == 1752 && m == 9 && dd > 2 && dd < 14) {
			continue;
		}
		day_cnt++;
		ans = years[y] + montths[m] + days[dd];
		if (ans == cnt) {
			return 0;
		}
	}
	for (int mm = m + 1; mm <= 12; mm++) {
		for (int dd = 1; dd <= mon[mm]; dd++) {
			if (y == 1752 && mm == 9 && dd > 2 && dd < 14) {
				continue;
			}
			day_cnt++;
			ans = years[y] + montths[mm] + days[dd];
			if (ans == cnt) {
				return 0;
			}
		}
	}
	for (int yy = y + 1; yy < 3000; yy++) {
		if (isLeap(yy)) {
			mon[2] = 29;
		} else {
			mon[2] = 28;
		}
		for (int mm = 1; mm <= 12; mm++) {
			for (int dd = 1; dd <= mon[mm]; dd++) {
				if (yy == 1752 && mm == 9 && dd > 2 && dd < 14) {
					continue;
				}
				day_cnt++;
				ans = years[yy] + montths[mm] + days[dd];
				if (ans == cnt) {
					//printf("%d %d %d\n", yy, mm , dd);
					return 0;
				}
			}
		}
	}
	return -1;
}

void output(int ret)
{	
	if (ret == 0) {
		printf("%d\n", day_cnt);
	} else {
		printf("-1\n");
	}
}

int main()
{
	init0();
	scanf("%d", &T);
	while (T--) {
		init();
		int ret = calc();
		output(ret);
	}
	return 0;
}