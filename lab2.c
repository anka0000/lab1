#include <stdio.h>
#include <limits.h>
long long arkerman (int m, int n) {
	if (m == 0) {
		return n+1;
	} else if (n == 0) {
		return arkerman(m - 1, 1);
	} else {
		return arkerman(m - 1, arkerman(m, n - 1));
	}
}
int isvalidinput (int m, int n) {
	if (m < 0 || n < 0) {
		return 0;
	} else {
		return 1;
	}
}
int main() {
	int m;
	int n;
	scanf("%d", &m);
	scanf("%d", &n);
	if (!isvalidinput(m, n)) {
		return 1;
	}
long long resultat = arkerman(m, n);
	printf("%lld\n", resultat);
		return 0;
}
