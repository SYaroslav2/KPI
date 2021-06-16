#include <stdlib.h>
#include <time.h>
#include "CommonVector.h"//������ ������, �������





clock_t Select4ExchangeArr3D(int ***A)
{
	int   k, j_1, L, R, min, max, counter_1, counter_2;//���������� ������

	clock_t time_start, time_stop;
	time_start = clock();//������� ����� ����
	for (k = 0; k < P; k++)
	{
		j_1 = 0; //����������� ������, �� ������ ���� ���� ��� �������� ��� ��������� ������ �������
		L = 0;
		R = M - 1;
		counter_1 = 0;
		counter_2 = N - 1;
		while (L < R || counter_1 < counter_2)//���������� ���������� ���� ���������� ������� �� ����������� 
		{
			j_1 = counter_1;
			if (j_1 > counter_2) break;
			for (int i = L; i < R + 1 || j_1 < counter_2; i++)//����, �� ��������� ���� ����������
			{
				if (i == M)
				{
					i = 0;
					j_1++;
				}

				if (A[k][i][j_1] < A[k][L][counter_1])
				{
					min = A[k][i][j_1];
					A[k][i][j_1] = A[k][L][counter_1];
					A[k][L][counter_1] = min;
				}
				else
					if (A[k][i][j_1] > A[k][R][counter_2])
					{
						max = A[k][i][j_1];
						A[k][i][j_1] = A[k][R][counter_2];
						A[k][R][counter_2] = max;
					}
			}

			L = L + 1;
			R = R - 1;
			if (L == M)//���� ��� ������� �������� �� ��� ������, ���������� �� �������� 0 � ���������� �� ����� ��������
			{
				L = 0;
				counter_1++;
			}
			if (R == -1)//���� ����� ������� �������� �� ��� ������, ���������� �� �������� ���������� �������� ������ � ���������� �� ����� ��������
			{
				R = M - 1;
				counter_2--;
			}
		}
	}
	time_stop = clock();//����� �����
	return time_stop - time_start;
}

clock_t Select4Exchange(int *V)
{
	int Min, Max;
	int L, R;
	clock_t time_start, time_stop;
	time_start = clock();
	L = 0; R = M *N - 1;
	while (L < R) {
		for (int i = L; i < R + 1; i++) {
			if (V[i] < V[L]) {
				Min = V[i];
				V[i] = V[L];
				V[L] = Min;
			}
			else
				if (V[i] > V[R]) {
					Max = V[i];
					V[i] = V[R];
					V[R] = Max;
				}
		}
		L = L + 1; R = R - 1;
	}
	time_stop = clock();
	return P * (time_stop - time_start);
}

clock_t Insert1Arr3D(int ***A)
{
	int i, j, k, p, v, d, elem, g;//����������� ������

	clock_t time_start, time_stop;
	time_start = clock();//������� �����
	for (g = 0; g < P; g++)
	{
		for (j = 0; j <= N - 1; j++)
		{
			for (i = 0; i <= M - 1; i++)
			{

				if (j == 0 && i == 0)//���������� �������� ������� �� ������ ����������
				{
					continue;
				}

				elem = A[g][i][j];
				k = 0;
				p = 0;

				while (elem > A[g][k][p])// �������� ��������, ���� ����� ������� ������� ��� ��������
				{
					k++;
					if (k == M)//���� �������� ������ ������� �������, �������� �������� ��������� ��������, � ��������� ����� ���������� 0 
					{
						p = p + 1;
						k = 0;
					}
				}

				v = i - 1;
				d = j;


				for (v = i - 1; v >= k || d != p; v--)
				{

					if (v != -1) 
					{
						A[g][v + 1][d] = A[g][v][d];
					}

					if (v == -1)
					{
						A[g][0][d] = A[g][M - 1][d - 1];//���� ������ � 0 �����, ������� ������� ���� ������ � ������� ��������� ������������ �������
						v = M - 1;
						d--;
					}


				}
				A[g][k][p] = elem;

			}
		}
	}
	time_stop = clock();//����� �����
	return time_stop - time_start;
}


clock_t Insert1(int *V)
{
	int Elem, j;
	clock_t time_start, time_stop;
	time_start = clock();
	for (int i = 1; i < M * N; i++) {
		Elem = V[i];
		j = 0;
		while (Elem > V[j]) j = j + 1;
		for (int k = i - 1; k >= j; k--)
			V[k + 1] = V[k];
		V[j] = Elem;
	}
	time_stop = clock();
	return P * (time_stop - time_start);
}//��������� ��� ����������� �������� � �����



clock_t InsertExchangeArr3D(int ***A)
{
	int p, g, tmp, i, j, k;//����������� ������

	clock_t time_start, time_stop;
	time_start = clock();//������� �����
	for (k = 0; k < P; k++) 
	{
		for (j = 0; j < N; j++) 
		{
			for (i = 0; i < M; i++) 
			{
				if (i == 0 && j == 0)//��������� �������� ������ �� ������ ������
				{
					continue;
				}

				p = i;
				g = j;
				while (!(p == 0 && g == 0))//�������� ���������� ���� �� ������ �� 0 �������� ������
				{
					if (p == 0) {
						if (A[k][p][g] < A[k][M - 1][g - 1]) {
							tmp = A[k][p][g];
							A[k][p][g] = A[k][M - 1][g - 1];
							A[k][M - 1][g - 1] = tmp;
						}
						g--;//�������� �������� ���������, ��� ���� ��� ���������
						p = M - 1;//��� ������� �� ����� ������� ����������� �������� �� ������� ������� �������
					}
					else {
						if (A[k][p][g] < A[k][p - 1][g]) {
							tmp = A[k][p][g];
							A[k][p][g] = A[k][p - 1][g];
							A[k][p - 1][g] = tmp;
						}
						p--;//�������� �������� ���������, ��� ���� ��� ���������
					}
				}
			}
		}
		
	}
	time_stop = clock();//����� �����
	return time_stop - time_start;
}

clock_t InsertExchange(int *V)
{
	int j, tmp;
	clock_t time_start, time_stop;
	time_start = clock();
	for (int i = 1; i < M * N; i++) {
		j = i;
		while (j > 0 && V[j] < V[j - 1]) {
			tmp = V[j];
			V[j] = V[j - 1];
			V[j - 1] = tmp;
			j = j - 1;
		}
	}
	time_stop = clock();
	return P * (time_stop - time_start);
}


