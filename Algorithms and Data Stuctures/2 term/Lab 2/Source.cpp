#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>

#define M 8
const int m = 7, n = 8;

void sorting(int A[][M]) {
	int i, j, left_border, right_border, k, f;
	float x;
	for (i = 0; i <= m - 1; i++) {
		for (j = 1; j <= n - 1; j++) {
			x = A[i][j];
			left_border = 0;
			right_border = j;

			while (left_border < right_border) {
				f = (left_border + right_border) / 2;
				if (A[i][f] <= x)
					right_border = f;
				else left_border = f + 1;

			}


			for (k = j - 1; k >= right_border; k--) {
				A[i][k + 1] = A[i][k];
			}

			A[i][right_border] = x;

		}
	}
}


void print_A(int A[][M], int key) {

	if (key == 0) {
		printf("\n");
		printf("  Array\n");
		printf("\n");
	}
	else if(key == 1) {
		printf("  Sorted array");
		printf("\n");
		printf("\n");
	}


	for (int i = 0; i <= m - 1; i++) {
		for (int j = 0; j <= n - 1; j++) {
			printf("  %d ", A[i][j]);
			printf("   ");
		}
		printf("\n");
		printf("\n");
	}
}


int main()
{
	int A[m][n];
	
	for (int i = 0; i <= m - 1; i++) {
		for (int j = 0; j <= n - 1; j++) {
			A[i][j] = rand() % 10;
			//A[i][j] = 5 - (i + j);
			//A[i][j] = 5 + (i + j);
		}
	}

	print_A(A, 0);
	sorting(A);
	print_A(A, 1);
	
	int a = _getch();
	return 0;
}