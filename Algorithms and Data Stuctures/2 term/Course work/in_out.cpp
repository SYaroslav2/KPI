#include <iostream>
#include "CommonVector.h"

void FillArray(int ***A, int b)//заповнення масива
{
	switch (b)
	{
	case 1:
	{
		long double number = 0;
		for (int k = 0; k < P; k++)
		{
			for (int j = 0; j < N; j++)
			{
				for (int i = 0; i < M; i++)
				{
					A[k][i][j] = number++ ;//заповнення масива по зростанню елементів у стовпцях
				}
			}
		}
		break;
	}
	case 2:
	{
		for (int k = 0; k < P; k++)
		{
			for (int j = 0; j < N; j++)
			{
				for (int i = 0; i < M; i++)
				{
					A[k][i][j] = rand() % (P * M * N);// рандомно заповнений масив
				}
			}
		}
		break;
	}
	case 3:
	{
		int number = P * M * N;
		for (int k = 0; k < P; k++)
		{
			for (int j = 0; j < N; j++)
			{
				for (int i = 0; i < M; i++)
				{
					A[k][i][j] = number--;//заповнення масива за спаданням елментів у стовпцях
				}
			}
		}
	}
	default:
		break;
	}
}
void showArray(int ***A)
/*
Функція, яка призначення для виводу масиву на екран
у вигляді матриці перерізів масиву
*/
{
	for (int k = 0; k < P; k++) {
		printf("Number %d\n", k);
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				printf("|%4d", A[k][i][j]);
			}
			printf("|\n");
		}
		printf("\n");
	}
}

void FillVec(int *Vec, int mode)
{  // функція для заповнення вектора
	int i;
	long double number;
	switch (mode)
	{
	case 1: // прямо-відсортований масив А
		number = 0;
		for (i = 0; i < M*N; i++)
			Vec[i] = number++;
		break;
	case 2: // заповнення масиву А рандомними числами
		for (i = 0; i < M*N; i++)
			Vec[i] = rand() % (N * M);
		break;
	case 3: // обернено-відсортований масив А
		number = N * M;
		for (i = 0; i < M*N; i++)
			Vec[i] = number--;
		break;
	default: break;
	}
}
void showVector(int *Vec)
/*
Функція, яка призначення для виводу вектора на екран
*/
{
	for (int j = 0; j < M*N; j++)
		printf("|%4d", Vec[j]);
}
int*** Multi_Dimentional_Dynamic_Array()//динамічне виділення пам'яті для тривірмного масива
{
	
	int*** Arr3D = (int***)malloc(P * sizeof(int**));
	for (int k = 0; k < P; k++)
	{
		Arr3D[k] = (int**)malloc(M * sizeof(int*));
		for (int i = 0; i < M; i++)
			Arr3D[k][i] = (int*)malloc(N * sizeof(int));
	}
	return Arr3D;
}

int* Multi_Dimentional_Dynamic_Vector()//динамічне виділення пам'яті для вектора
{
	int* Vec = (int*)malloc(N * M * sizeof(int));
	return Vec;
}

void FreeMemory(int*** A, int* V)//звільнення пам'яті після роботи з динамічним масивом
{
	for (int k = 0; k < P; k++)
	{
		for (int i = 0; i < M; i++)
			free(A[k][i]);
		free(A[k]);
	}
	free(A);
	free(V);
}

