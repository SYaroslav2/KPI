#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

typedef long double (*myFunc) (long double x);

struct Solution {
	Solution(long double r, int n_i, long double err) {
		root = r;
		num_iter = n_i;
		error = err;
	}
	long double root;
	long double error;
	int num_iter;
};

long double func(long double x) {

	return sin(2 * x) + cos(x) * cos(x) - x/2;

}

long double func_1der(long double x) {

	return 2 * cos(2*x) - 2 * cos(x)*sin(x) - 0.5;

}

long double func_2der(long double x) {

	return 2 * sin(x) * sin(x) - 4 * cos(2 * x) - 2 * cos(x) * cos(x);

}

Solution fixedPointIteration(long double a, long double b, long double eps, myFunc f, myFunc f_1der) {

	long double m1 = min(abs(f_1der(a)), abs(f_1der(b)));
	long double M1 = max(abs(f_1der(a)), abs(f_1der(b)));
	long double lambda = 1 / M1;
	long double q = 1 - m1 / M1;
	int num_iter = 0;
	long double prec_estimate = 0;

	if (f_1der(a) < 0) lambda *= -1;

	long double x0 = (a + b) / 2;

	long double x_next = x0, x_cur;
	do {
		x_cur = x_next;
		x_next -= lambda * f(x_next);
		++num_iter;
	} while (abs(x_next - x_cur) > (1 - q) / q * eps);
	prec_estimate = (q * abs(x_next - x_cur)) / (1 - q);

	return *(new Solution(x_next, num_iter, prec_estimate));
}

Solution chordMethod(long double a, long double b, long double eps, myFunc f, myFunc f_1der, myFunc f_2der) {
	
	long double m1 = min(abs(f_1der(a)), abs(f_1der(b)));
	int num_iter = 0;
	long double prec_estimate = 0;
	long double c;
	long double x_n = 0;
	if ((f(a) * f_2der(a)) > 0) {
		c = a;
		x_n = b;
	}
	else {
		c = b;
		x_n = a;
	}

	while (abs(f(x_n)) / m1 > eps) {
		x_n -= f(x_n) / (f(x_n)-f(c)) * (x_n - c);
		++num_iter;
	}
	prec_estimate = abs(f(x_n)) / m1;

	return *(new Solution(x_n, num_iter, prec_estimate));
}


int main() {

	const int a1 = -2, b1 = -1;
	const int a2 = 0, b2 = 1;

	vector<Solution> fpiM; //for fixed point iteration method
	vector<Solution> cM; //for chord method
	double eps = 1e-2;

	for (int i = 0; i < 5; ++i) {
		fpiM.push_back(fixedPointIteration(a1, b1, eps, func, func_1der));
		fpiM.push_back(fixedPointIteration(a2, b2, eps, func, func_1der));
		cM.push_back(chordMethod(a1, b1, eps, func, func_1der, func_2der));
		cM.push_back(chordMethod(a2, b2, eps, func, func_1der, func_2der));
		eps *= 1e-3;
	}

	cout << "Table 1 --------- fixed point iteration method" << endl;
	cout << "eps    root value  		error estimation" << endl << endl;

	eps = 1e-2;
	for (size_t i = 0; i < fpiM.size(); ++i) {
		cout << setw(7) << setiosflags(ios::left) << eps
			<< setprecision(14) << setw(24) << fpiM[i].root << setw(12) << fpiM[i].error << "\n";
		if (i % 2 == 1)
			eps *= 1e-3;
	}

	cout << endl << "Table 2 --------- chord method" << endl;
	cout << "eps    root value  		error estimation" << endl << endl;

	eps = 1e-2;
	for (size_t i = 0; i < cM.size(); ++i) {
		cout << setw(7) << setiosflags(ios::left) << eps
			<< setw(24) << cM[i].root << setw(12) << cM[i].error << "\n";
		if (i % 2 == 1)
			eps *= 1e-3;
	}

	cout << endl << "Table 3 --------- comparison the rate of convergence" << endl;
	cout << "eps    num iter(Iter)  num iter(Chord)" << endl << endl;

	eps = 1e-2;
	for (size_t i = 0; i < cM.size(); i += 2, eps *= 1e-3)
		cout << setw(7) << setiosflags(ios::left) << eps
		<< setw(16) << fpiM[i].num_iter << setw(12) << cM[i].num_iter << "\n";

}