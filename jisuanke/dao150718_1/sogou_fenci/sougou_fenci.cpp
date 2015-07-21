#include <cstdio>
#include <cstring>

using namespace std;
#define N 1000002
char s[N];
char tmp[N];
bool finished;
int len;
void init()
{
	scanf("%s", s);
	len = strlen(s);
	//printf("%s\n", s);
	finished = false;
}

void proc()
{
	for (int i = 0; i < len - 2; i++) {
		if (s[i] == '0' && s[i+1] == 'k') {
			if (s[i+2] == '0') {
				printf("0k0\n");
				i+=2;
			} else {
				int j;
				bool flag =false;
				for (j = 2; j < len - i; j++) {
					if ( ( s[i+j] > 'e' &&  s[i+j] >= 'a' && s[i+j]<='z') ||
					     //s[i+j] >= 'a' && s[i+j] <= 'z' ||
					     (s[i+j] > 'E' &&  s[i+j] >= 'A' && s[i+j]<='Z')  ||
					     (s[i+j] == '\'') ){
						break;
					}
					flag = true;
				}
				memset(tmp, 0, sizeof(tmp));
				strncpy(tmp, s + i, j);
				i += j;
				if (flag) {
					printf("%s\n", tmp);
				}
			}

		}
	}
}

int main()
{
	init();
	proc();
	return 0;
}