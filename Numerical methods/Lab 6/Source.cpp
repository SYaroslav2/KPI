#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

using namespace std;


double func_der(double x) {
	return -24 * x * x * cos(8 * x) - 6 * x * sin(8 * x) + 1;
}


double accurate_func(double x) {
	return x - 3 * x * x * sin(8 * x);
}


void Runge_kutta(double x_0, double& x, double& y, double y_0, double h) {
	double k1, k2, k3, k4;
	k1 = h * func_der(x_0);
	k2 = h * func_der(x_0 + h / 2);
	k3 = h * func_der(x_0 + h / 2);
	k4 = h * func_der(x_0 + h);
	double delta_y = (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);
	x = x_0 + h;
	y = y_0 + delta_y;
}


vector<double> adams(double a, double b, double& h, double& error, int n){
	h = (b - a) / n;
	double y = 0, x = a;
	vector<double> f(n + 1);
	vector<double> solution(n + 1);
	for (int i = 0; i < 4; i++) {
		f[i]= func_der(x);
		solution[i] = y;
		Runge_kutta(x, x, y, y, h);
	}
	error = 0;
	y = solution[3];
	
	for (int i = 4; i < n + 1; i++) {
		x = a + h * i;
		y += h * (55.0 / 24.0 * f[i - 1] - 59.0 / 24.0 * f[i - 2] + 37.0 / 24.0 * f[i - 3] - 3.0 / 8.0 * f[i - 4]);
		solution[i] = y;
		error += fabs(accurate_func(x) - (y));
		
		f[i] = func_der(x);
	}
	error /= (n - 3.0);
	return solution;
}


int main() {
	double a = 0, b = 15;
	int n = 1000;
	double h = fabs(b - a) / n;
	double x = a, error = 0;
	double y = 0, y0 = 0;
	for (int i = 0; i < n; i++)	{
		error += fabs(accurate_func(x) - (y));
		Runge_kutta(x, x, y, y, h);
	}
	double h_4_task1 = h;
	double eps = error / n;
	cout << endl << " Task 1"<< endl;
	cout << " eps = " << eps << endl;
	double h_new = sqrt(sqrt(eps));
	double y2;
	do {
		y2 = y;
		x = a;
		y = y0;
		h_new /= 2;
		n = (b - a) / h_new;
		for (int i = 0; i < n; i++)
			Runge_kutta(x, x, y, y, h_new);
	} while (fabs(y2 - y) > 15 * eps);

	cout << endl << " Task 2" << endl;
	cout << " h from task 1 = " << h << endl;
	cout << " h_enough from task 2 = " << h_new << endl;
	cout << " Difference between h from task 1 and h from task 2 = " << (h - h_new) << endl;
	cout << endl << " Task 3" << endl;
	cout << " h from task 1 = " << h << endl;
	double h_prev = h;
	
	error = 0;
	n = 10;
	do {
		adams(a, b, h, error, n);
		n += 1;
	} while (error > 0.0001);
	int n_for_task_4 = n - 1;

	cout << " Admissible for this task h = " << h << endl;
	cout << " Difference between h from task 1 and h from task 3 = " << (h_prev - h) << endl;
	cout << endl << " Task 4" << endl;
	
	ofstream file1("Adams.csv", ofstream::out);
	ofstream file2("Ruhge_kutta.csv", ofstream::out);
	ofstream file3("accurate func.csv", ofstream::out);
	cout << setw(35) << " Result using Adams method" << endl;
 
	vector<double> adams_res = adams(a, b, h, error, n_for_task_4);
	x = a;
	double temp = 0.15;
	double h_4 = (b - a) / 3200;
	int count = 0;
	adams_res = adams(a, b, h, error, 3200);
	for (int i = 0; i < 3201; i++) {
		if (i % 32 == 0) {
			cout << setw(15) << " x:" << x << setw(10) << " \t" << "y(n): " << adams_res[i] << endl;
			file1 << to_string(x) << ';' << to_string(adams_res[i]) << std::endl;
			
		}
		x+=h_4;
	}
	cout << setw(35) << "Result using Runge-Kutta method" << setw(35) << "Result using accurate func" << endl;
	y = 0, x = a; 
	for (int i = 0; i < 1001; i++) {
		if (i % 10 == 0) {
			cout << setw(15) << " x:" << x << setw(10) << " \t" << "y(n): " << y << setw(10) << " \t" << "y(n): " << accurate_func(x) << endl;
			file2 << to_string(x) << ';' << to_string(y) << std::endl;
			file3 << to_string(x) << ';' << to_string(accurate_func(x)) << std::endl;
		}
		Runge_kutta(x, x, y, y, h_4_task1);
	}

	return 0;
}