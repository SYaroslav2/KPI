#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>

#pragma warning (disable : 26451)

using namespace std;


const double a = 0;
const double b = 7;


double chebishev_polynomial(const double x, const int n_che) {
	if (n_che == 0)   return 1;
	if (n_che == 1.0) return x;

	double P_prev = 1, P_curr = x, P_next = 0;

	for (int i = 1; i <= n_che - 1; ++i) {
		P_next = 2.0 * x * P_curr - P_prev;
		P_prev = P_curr;
		P_curr = P_next;
	}

	return P_curr;
}


double f(const double x) { return (x * x - sin(x)) * cos(2.5 * x); }


double func(int n_che, double x, int pos_i, int pos_j) {
	if (pos_j == n_che)
		return  f(x) * chebishev_polynomial(x, pos_i);
	else
		return  chebishev_polynomial(x, pos_i) * chebishev_polynomial(x, pos_j);
}


vector<double> unit_division_method(vector<vector<double>> matrix, int n) {
	double tmp;
	vector<double> vector (n);
	for (int i = 0; i < n; i++) {
		tmp = matrix[i][i];
		for (int j = i; j < n + 1; j++) {
			matrix[i][j] = matrix[i][j] / tmp;
		}
		for (int k = i + 1; k < n; k++) {
			tmp = matrix[k][i];
			for (int p = i; p < n + 1; p++) {
				matrix[k][p] -= matrix[i][p] * tmp;
			}
		}
	}

	int i = n - 1;
	while (i >= 0) {
		tmp = 0;
		int j = n - 1;
		while (j != i) {
			tmp += matrix[i][j] * vector[j];
			j--;
		}
		vector[j] = matrix[i][n] - tmp;
		i--;
	}

	return vector;
}


double trap(int pos_i, int pos_j, int n, int n_che, double a, double b) {
	double x = a;
	double h = (b - a) / n;
	long double integral = h * (func(n_che, a, pos_i, pos_j) + func(n_che, b, pos_i, pos_j)) / 2.0;
	for (int i = 0; i < n - 1; i++) {
		x += h;
		integral += h * func(n_che, x, pos_i, pos_j);
	}
	return integral;
}


double integrate_legendre(int pos_i, int pos_j, const double a, const double b, const int n_che) {
	double eps = 1e-6;
	double In, I2n;
	int n = (int)ceil((b - a) / sqrt(sqrt(eps)));
	In = trap(pos_i, pos_j, n, n_che, a, b);
	I2n = trap(pos_i, pos_j, 2 * n, n_che, a, b);
	//do {} while() cannot be used here, otherwise the calculation of the necessary integrals will take dozens of times more time
	//verified by personal experience
	while(fabs(In - I2n) > 3 * eps) {
		In = I2n;
		n *= 2;
		I2n = trap(pos_i, pos_j, n, n_che, a, b);
	}
	return I2n;
}


vector<double> make_matrix(double a, double b, int n) {
	int i, j;
	vector<vector<double>> matrix(n, vector<double>(n + 1));
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n + 1; j++) {
			matrix[i][j] = integrate_legendre(i, j, a, b, n);
		}
	}	

	return unit_division_method(matrix, n);
}


double Polynomial(double x, double a, double b, int n) {
	vector<double> A = make_matrix(a, b, n);
	double y = 0;
	for (int i = 0; i < n; ++i)
		y += A[i] * chebishev_polynomial(x, i);
	return y;
}

//it takes an average of 3-5 minutes to get all the result
int main() {
	FILE* g;
	double x, y;
	double step = 0.2;
	double n_curr = 0, deviation = 0, n = 4;
	int n_i = (int)ceil((b - a) / step);
	
	do {
		deviation = 0;
		++n_curr;
		x = a;
		for (int i = 0; i <= n_i; ++i) {
			y = f(x) - Polynomial(x, a, b, n);
			deviation += y * y;
			x += step;
		}
		n *= 2;
		deviation = sqrt(deviation / n_i);
		cout << "Deviation" << "["<< n_curr <<"]" << " = " << deviation << std::endl;
	} while (deviation > 0.1); //as far as I understand this epsilon will be enough
	//which is confirmed by the order of the polynomial and the running time of the program
	
	//ofstream file("polynomial_result.txt", ofstream::out);
	cout << setw(5) << "x" << setw(20) << "P(x)" << endl;
	for (double i = a; i <= b; i += step) {
		const auto result = Polynomial(i, a, b, n);
		if (abs(0 - i) < step / 2) { //used to print 0 as 0, but not num e-16
			cout << setw(5) << "0" << setw(20) << result << endl;
		//	file << "0.0" << '\t' << result << std::endl;
			continue;
		}
		cout << setw(5) << i << setw(20) << result << endl;
		//file << i << '\t' << result << std::endl;
	}
	//file.close();
	return 0;
}