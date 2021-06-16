#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>
int main()
{
	const int m = 7, n = 6, s = 6;
	float A[m][n], r; int i, j, l;
	printf("\n");
	
	printf("\n");
	printf("\n");
	printf("  Matrix\n");
	printf("\n");
	printf("\n");

	
	for (i = 0; i <= m - 1; i++) {
		for (j = 0; j <= n - 1; j++) {
			if (j % 2 == 0)
			{
				A[i][j] = 7 - i - j + 1;
			}
			else A[i][j] = 7 - i - j;
			printf("  %.0f ", A[i][j]);
			printf("   ");
		}
		printf("\n");
		printf("\n");
	}


	
	
		l = 0; r = n - 1;
		while (l < r)
		{

			j = (l + r) / 2;
			if ((A[0][i] >= 0) && (A[0][i] <= 5))

			{
				l = j + 1;
			}
			else r = j;


		}


		if ((A[0][j] >= 0) && (A[0][j] <= 5))
		{

			printf("\n");
			printf("\n");
			printf("  Found on the position [0][%d]", j-1);
			
		}
		else printf("  Not found in first row\n");
	


		l = 0; r = m - 1;

		while (l < r)
		{

			i = (l + r) / 2;

			if ((A[i][n-1] >= 0) && (A[i][n-1] <= 5))
			{
				l = i + 1;
			}
			else r = i;


		}

		printf("\n");
		printf("\n");
		

		if ((A[i][n-1] >= 0) && (A[i][n-1] <= 5))
		{
	
			
			printf("\n");
			printf("\n");
			printf("  Found on the position [%d][%d]", i, n - 1);
			
		}

		else printf("  Not found in last column");
	
	_getch();
	return 0;
}