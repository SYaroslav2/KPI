#include <iostream>
#include "CommonVector.h"

void FillArray(int ***A, int b)//���������� ������
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
					A[k][i][j] = number++ ;//���������� ������ �� ��������� �������� � ��������
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
					A[k][i][j] = rand() % (P * M * N);// �������� ���������� �����
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
					A[k][i][j] = number--;//���������� ������ �� ��������� ������� � ��������
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
�������, ��� ����������� ��� ������ ������ �� �����
� ������ ������� ������� ������
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
{  // ������� ��� ���������� �������
	int i;
	long double number;
	switch (mode)
	{
	case 1: // �����-������������ ����� �
		number = 0;
		for (i = 0; i < M*N; i++)
			Vec[i] = number++;
		break;
	case 2: // ���������� ������ � ���������� �������
		for (i = 0; i < M*N; i++)
			Vec[i] = rand() % (N * M);
		break;
	case 3: // ��������-������������ ����� �
		number = N * M;
		for (i = 0; i < M*N; i++)
			Vec[i] = number--;
		break;
	default: break;
	}
}
void showVector(int *Vec)
/*
�������, ��� ����������� ��� ������ ������� �� �����
*/
{
	for (int j = 0; j < M*N; j++)
		printf("|%4d", Vec[j]);
}
int*** Multi_Dimentional_Dynamic_Array()//�������� �������� ���'�� ��� ���������� ������
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

int* Multi_Dimentional_Dynamic_Vector()//�������� �������� ���'�� ��� �������
{
	int* Vec = (int*)malloc(N * M * sizeof(int));
	return Vec;
}

void FreeMemory(int*** A, int* V)//��������� ���'�� ���� ������ � ��������� �������
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

