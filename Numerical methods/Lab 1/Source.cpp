/********************************************************************************/
/*                  Variant 23 function sh(x) a = - 1.8 b = 5.9                 */
/*                       Written by:Savytskiy Yaroslav                          */
/*  «аметка: при eps = 10^(-14) достигаетс€ максимальна€ точность               */
/*  вычислени€ при которой дельта равно 0                                       */
/********************************************************************************/
#include <cmath>
#include <stdio.h>


void compute(double eps, double x, int task_number) {

	double Uk_1 = x;
	double series_sum = x;
	int n_counter = 1;
	double R = 0;
	double abs_delta = 0;

	while (fabs(Uk_1) > eps) {
		
		Uk_1 = (x * x * Uk_1) / (2 * n_counter * (2 * n_counter + 1));
		series_sum += Uk_1;
		n_counter++;
	}

	R = fabs(Uk_1 / 3);

	double y = sinh(x);
	abs_delta = fabs(series_sum - sinh(x));

	if (task_number == 1)
		printf("|%15E |%5d |%20E |%20E |\n", eps, n_counter, abs_delta, R);
	if (task_number == 2)
		printf("|%10f |%20E |%20E |\n", x, abs_delta, R);
}


int main() {
	double a = -1.8;
	double b = 5.9;
	//double x = a;
	double x = (a + b) / 2;
	double h = fabs((b - a) / 10);
	double eps;
	int i;
	printf("---------------------------------------------------------------------\n");
	printf("|%15s |%5s |%20s |%20s |\n", "eps", "n", "abs_delta", "R");
	printf("---------------------------------------------------------------------\n");

	eps = 1e-2;
	while (eps > 1e-14) {
		compute(eps, x, 1);
		eps /= 1000;
	}
	printf("---------------------------------------------------------\n");
	printf("|%10s |%20s |%20s |\n", "X", "abs_delta", "R");
	printf("---------------------------------------------------------\n");

	x = a;
	for (i = 1; i <= 11; i++) {
		compute(1e-8, x, 2);
		x = a + h * i;
	}

	return 0;
}