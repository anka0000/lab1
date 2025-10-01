#include <stdio.h>
#include <math.h>

int main() {
	double x, y, z, u;
	double hx = 1.3;
	double hy = 0.8;
	double hz = 1.3;
	printf(" x y z u \n");
	for ( x = 1; x <= 3; x += hx) {
		for ( y = 2; y <= 4; y += hy) {
			for ( z = 0.5; z <= 1.5; z += hz) {
				u = -sqrt(pow(y, 2) + 4 * pow(x,2) / 3) + 5 * pow(cos(x * y), 4) / (x * y);
			printf("%0.2f  %0.2f  %0.2f  %0.2f \n ", x, y, z, u);
			}
		}
	}
	return 0;
}
