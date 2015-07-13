#include <cstdio>
#include <cmath>

using namespace std;

int a, b, c;
int x, y;

double da, db, dc, dx, dy;
double res = 0.0;

void init()
{
	scanf("%d%d%d%d%d", &a, &b, &c, &x, &y);
	da = double(a); db = double(b); dc = double(c);
	dx = double(x); dy = double(y);
}

void tripe_divide(double left, double right)
{
	double lm = left + (right - left) / 3.0;
	double rm = right - (right - left) / 3.0;
	double ylm = da * lm * lm + db * lm + dc;
	double dl =  (ylm - dy) * (ylm - dy) + (lm - dx) * (lm - dx);
	double yrm = da * rm * rm + db * rm + dc;
	double dr =  (yrm - dy) * (yrm - dy) + (rm - dx) * (rm - dx);
	//printf("%lf %lf\n", dl, dr);
	if ( ( ((dl-dr) < 1e-8) && ( (dl-dr) > -1e-6) ) || ( ((dr-dl) < 1e-6) && ((dr-dl) > -1e-6) ) ) {
		res = (dl + dr) / 2.0;
	} else if (dl < dr) {
		tripe_divide(left, rm);
	} else if (dr < dl){
		tripe_divide(lm, right);
	}
}

void output()
{
	res = sqrt(res);
	printf("%.3lf\n", res);
}

int specail()
{
	if (a*x*x+b*x+c == y) {
		printf("0.000\n");
		return 1;
	}
	if (a == 0 && b != 0) {
		int aa = (b * x - y + c);
		int bb = b * b + 1;
		double dd = fabs(double(aa) / sqrt(bb));
		printf("%.3lf\n", dd);
	}
	if (a == 0 && b == 0) {
		int dd = y - c;
		if (dd < 0) {
			dd = 0 - dd;
		}
		printf("%d.000\n", dd);
		return 1;
	}
	return 0;
}

int main()
{
	init();
	if (specail()) {//Key
		return 0;
	}

	//tripe_divide(-600.0,600.0);//Error
	double axis = -1.0 * b / (2.0*a);
	if (axis < double(x)) {
		tripe_divide(axis, axis + 400.0);
	} else {
		tripe_divide(axis-400.0, axis);
	}
	output();
	return 0;
}