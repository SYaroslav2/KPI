#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <algorithm>


using namespace std;

typedef long double (*myFunc) (const long double x);

struct Task1 {
	Task1(double e, double h, double v, double err) {
		eps = e;
		step = h;
		value = v;
		error = err;
	}

	double eps;
	double step;
	double value;
	double error;
};

struct Task2 {
	Task2(double e, double h, double err) {
		eps = e;
		step = h;
		error = err;
	}
	double eps;
	double step;
	double error;
};

void print_table1(const vector<Task1>& t) {

	cout << "eps    h             I_value       abs_err" << endl;

	for (size_t i = 0; i < t.size(); ++i)
		cout << setw(7) << setiosflags(ios::left) << t[i].eps << setw(14) << t[i].step
		<< setw(14) << t[i].value << setw(14) << t[i].error << "\n";
	cout << endl;
}

void print_table2(const vector<Task2>& t) {

	cout << "eps           h             abs_err" << endl;

	for (size_t i = 0; i < t.size(); ++i)
		cout << setw(14) << setiosflags(ios::left) << t[i].eps
		<< setw(14) << t[i].step << setw(12) << t[i].error << "\n";
	cout << endl;
}

long double func(const long double x) { return -x * x * x * sin(x) + 3 * x * x * cos(x); }
long double func_4der(const long double x) { return (-60) * cos(x) - x * x * x * sin(x) + 15 * x *x * cos(x) + 60 * x * sin(x); }
long double prim(const long double x) { return x * x * x * cos(x); }

long double calculate_h(const long double a, const long double b, const long double eps) {

	return pow(180 * eps / ((b - a) * max(abs(func_4der(a)), abs(func_4der(b)))), 0.25);

}

Task1 integrate(myFunc f, const long double a, const long double b, const long double eps, const long double exact_val) {

	long double sig1 = 0.0; 
	long double sig2 = 0.0;
	long double I = 0;
	I += (f(a) + f(b)) / 2;
	long double x = a;
	long double h = calculate_h(a, b, eps);
	int n = (int)ceil(((b - a) / h));
	if (n % 2 == 0)
		n = n;
	else
		n--;
	h = (b - a) / n;
	for (int i = 1; i <= n - 1; ++i) {
		if (i % 2 == 0)
			sig2 += f(a + i * h);
		else
			sig1 += f(a + i * h);
	}
	I = h / 3 * (f(a) + f(b) + 4 * sig1 + 2 * sig2);

	return (*new Task1(eps, h, exact_val, abs(exact_val - I)));
}

Task2 integrate_runge(myFunc f, const long double a, const long double b, const long double eps, const long double exact_val) {

	int r = 4;
	int n = (int)ceil(pow(eps, -1 / (double)r));

	if (n % 2 == 0)
		n = n;
	else
		n--;

	long double sig1 = 0.0;
	long double sig2 = 0.0;
	long double I_n = 0, I_2n = 0;
	I_n += (f(a) + f(b)) / 2;
	long double h = (b - a) / n;
	long double x = a;
	for (int i = 1; i <= n - 1; ++i) {
		if (i % 2 == 0)
			sig2 += f(a + i * h);
		else
			sig1 += f(a + i * h);
	}
	I_n = h / 3 * (f(a) + f(b) + 4 * sig1 + 2 * sig2);

	I_2n = I_n;

	do {
		n *= 2;
		sig1 = 0.0;
		sig2 = 0.0;
		I_n = I_2n;
		I_2n = (f(a) + f(b)) / 2;
		h = (b - a) / n;
		long double x = a;
		for (int i = 1; i <= n - 1; ++i) {
			if (i % 2 == 0)
				sig2 += f(a + i * h);
			else
				sig1 += f(a + i * h);
		}
		I_2n = h / 3 * (f(a) + f(b) + 4 * sig1 + 2 * sig2);
	} while (abs(I_n - I_2n) > 15 * eps);

	return (*new Task2(eps, h, abs(exact_val - I_2n)));
}

int main() {

	const long double a = 5;
	const long double b = 18;
	const long double EXACT_VAL = prim(b) - prim(a);

	vector<Task1> table1;
	vector<Task2> table2;

	double eps = 0.01;
	while (eps - 1e-8 >= 1e-20) {
		table1.push_back(integrate(func, a, b, eps, EXACT_VAL));
		eps *= 1e-2;
	}
	print_table1(table1);

	for (size_t i = 0; i < table1.size(); ++i)
		table2.push_back(integrate_runge(func, a, b, table1[i].error, EXACT_VAL));

	print_table2(table2);

	cout << setprecision(18);
}