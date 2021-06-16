#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

void FillArray(char **A, const int M, const int N);
void showArray(char **A, const int M, const int N);
char** Multi_Dimentional_Dynamic_Array(const int M, const int N);
void FreeMemory(char** A, const int M);
void Obmin(char** A, const int M, const int N);

int main()
{
	int i_1 = 4, i_2 = 7, j_1 = 9, j_2 = 7;
	char** A = NULL;
	char** B = NULL;
	A = Multi_Dimentional_Dynamic_Array(i_1, j_1);
	B = Multi_Dimentional_Dynamic_Array(i_2, j_2);
	FillArray(A, i_1, j_1);
	showArray(A, i_1, j_1);
	Obmin(A, i_1, j_1);
	showArray(A, i_1, j_1);
	FillArray(B, i_2, j_2);
	showArray(B, i_2, j_2);
	Obmin(B, i_2, j_2);
	showArray(B, i_2, j_2);
	FreeMemory(A, i_1);
	FreeMemory(B, i_2);
	_getch();
	return 0;
}
void FillArray(char **A, const int M, const int N)
{
	char number = 0;
		
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < M; i++)
		{
			A[i][j] = number++;
		}
	}
		

}

void showArray(char **A, const int M, const int N)
{
	printf("\n");
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			printf("|%4d", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void Obmin(char **A, const int M, const int N)
{
	char min, max; 
	int i_min = 0, j_min = 0, i_max = 0, j_max = 0;
	min = A[0][0];
	max = A[0][0];
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < M; i++)
		{
			if (A[i][j] < min)
			{
				min = A[i][j];
				i_min = i;
				j_min = j;
			}
			if (A[i][j] > max)
			{
				max = A[i][j];
				i_max = i;
				j_max = j;
			}
		}
	}
	A[i_min][j_min] = max;
	A[i_max][j_max] = min;
}

char** Multi_Dimentional_Dynamic_Array(const int M, const int N)
{

	char** Arr3D = (char**)malloc(M * sizeof(char*));	
	for (int i = 0; i < M; i++)
		Arr3D[i] = (char*)malloc(N * sizeof(char));

	return Arr3D;
}
void FreeMemory(char** A, const int M)
{
	
	for (int i = 0; i < M; i++)
		free(A[i]);
	free(A);
	
}