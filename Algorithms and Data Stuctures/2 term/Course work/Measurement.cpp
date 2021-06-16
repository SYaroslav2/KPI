#include "Measurement.h"//���������� ����������� �������
#include <stdio.h>//�������� �����-������
#include "in_out.h"////������ �����-������ ������-�������
#include "sorting.h"
#include <conio.h>


clock_t Res[measurements_number];
clock_t Res1[measurements_number];
clock_t Res2[measurements_number];

void Out_Res(float ordered, float random, float backordered);

float MeasurementProcessing(clock_t *Res)
{
	long int Sum;
	float AverageValue;

	/*("Initial Measurement Results:\n");
	for (int i = 0; i < measurements_number; i++)
		printf("   %ld", Res[i]);
	printf("\n\n");*/

	clock_t buf;
	int L = rejected_number, R = measurements_number - 1;
	int k = rejected_number;
	for (int j = 0; j < min_max_number; j++) {
		for (int i = L; i < R; i++) {
			if (Res[i] > Res[i + 1]) {
				buf = Res[i];
				Res[i] = Res[i + 1];
				Res[i + 1] = buf;
				k = i;
			}
		}
		
			R = k;
		for (int i = R - 1; i >= L; i--) {
			if (Res[i] > Res[i + 1]) {
				buf = Res[i];
				Res[i] = Res[i + 1];
				Res[i + 1] = buf;
				k = i;
			}
		}
		L = k + 1;
	}

	/*printf("Measurement Results after sorting:\n");
	for (int i = 0; i < measurements_number; i++)
		printf("   %ld", Res[i]);
	printf("\n\n");*/

	Sum = 0;
	for (int i = rejected_number + min_max_number; i <
		measurements_number - min_max_number; i++)
		Sum = Sum + Res[i];
	AverageValue = (float)Sum / (float)(measurements_number -
		2 * min_max_number - rejected_number);
	//printf("\n %f\n", AverageValue);
	printf("");
	return AverageValue;
}

void InsertExchangeArr3D_Measurement(int ***A)//����� ���� ��� ��������� �������� "������� � ����" ��� ������
{
	float ordered, random, backordered;
	for (int i = 0; i < measurements_number; i++)
	{
		FillArray(A, 1);//���������� ����� ������������
		Res[i] = InsertExchangeArr3D(A);//���������� ����� ������� ����, �� ������� �������
		FillArray(A, 2);//���������� ����� ���������� ����������
		Res1[i] = InsertExchangeArr3D(A);//���������� ������ ����� ������� ����, �� ������� ������� 
		FillArray(A, 3);//���������� ����� �������� ������������
		Res2[i] = InsertExchangeArr3D(A);//���������� ����� ����� ������� ����, �� ������� �������
	}
	ordered = MeasurementProcessing(Res);
	random = MeasurementProcessing(Res1);
	backordered = MeasurementProcessing(Res2);
	Out_Res(ordered, random, backordered);//��������� ������� ��������� ���������� �� �������
}

//� ��������� �������� ..._Measurement, 䳿 ����������� ��������� 

void Insert1Arr3D_Measurement(int ***A)//����� ���� ��� ��������� �������� "����4 � ����" ��� ������
{
	float ordered, random, backordered;
	for (int i = 0; i < measurements_number; i++)
	{
		FillArray(A, 1);
		Res[i] = Insert1Arr3D(A);
		FillArray(A, 2);
		Res1[i] = Insert1Arr3D(A);
		FillArray(A, 3);
		Res2[i] = Insert1Arr3D(A);
	}
	ordered = MeasurementProcessing(Res);
	random = MeasurementProcessing(Res1);
	backordered = MeasurementProcessing(Res2);
	Out_Res(ordered, random, backordered);
	
}


void Select4ExchangeArr3D_Maesurement(int ***A)//����� ���� ��� �������� ���������� �1 ������ ����� ������� ��� ������
{
	float ordered, random, backordered;
	for (int i = 0; i < measurements_number; i++)
	{
		FillArray(A, 1);
		Res[i] = Select4ExchangeArr3D(A);
		FillArray(A, 2);
		Res1[i] = Select4ExchangeArr3D(A);
		FillArray(A, 3);
		Res2[i] = Select4ExchangeArr3D(A);
	}
	
	ordered = MeasurementProcessing(Res);
	random = MeasurementProcessing(Res1);
	backordered = MeasurementProcessing(Res2);
	Out_Res(ordered, random, backordered);
	
}

void InsertExchangeVector_Measurement(int *V)//����� ���� ��� ��������� �������� "������� � ����" ��� �������
{
	float ordered, random, backordered;
	for (int i = 0; i < measurements_number; i++)
	{
		FillVec(V, 1);
		Res[i] = InsertExchange(V);
		FillVec(V, 2);
		Res1[i] = InsertExchange(V);
		FillVec(V, 3);
		Res2[i] = InsertExchange(V);
	}
	ordered = MeasurementProcessing(Res);
	random = MeasurementProcessing(Res1);
	backordered = MeasurementProcessing(Res2);
	Out_Res(ordered, random, backordered);
}


void Insert1Vector_Measurement(int *V)//����� ���� ��� ��������� �������� "����4 � ����" ��� �������
{
	float ordered, random, backordered;
	for (int i = 0; i < measurements_number; i++)
	{
		FillVec(V, 1);
		Res[i] = Insert1(V);
		FillVec(V, 2);
		Res1[i] = Insert1(V);
		FillVec(V, 3);
		Res2[i] = Insert1(V);
	}
	ordered = MeasurementProcessing(Res);
	random = MeasurementProcessing(Res1);
	backordered = MeasurementProcessing(Res2);
	Out_Res(ordered, random, backordered);
}


void Select4ExchangeVector_Maesurement(int *V)//����� ���� ��� �������� ���������� �1 ������ ����� ������� ��� �������
{
	float ordered, random, backordered;
	for (int i = 0; i < measurements_number; i++)
	{
		FillVec(V, 1);
		Res[i] = Select4Exchange(V);
		FillVec(V, 2);
		Res1[i] = Select4Exchange(V);
		FillVec(V, 3);
		Res2[i] = Select4Exchange(V);
	}
	ordered = MeasurementProcessing(Res);
	random = MeasurementProcessing(Res1);
	backordered = MeasurementProcessing(Res2);
	Out_Res(ordered, random, backordered);
}

void OutTable()//������� ��� ��������� "�����" �������
{
	printf("\n\t\t TABLEs WITH MEASUREMENTS: \n");
	printf("\n\t\t------------------------------------------------------\n");
	printf("\t\t|\t Ordered |\t Random |\t BackOrdered | \n");
	printf("\t\t------------------------------------------------------\n");
}


void Out_Res(float ordered, float random, float backordered)//������� ��� ������ �������, ��������� ��� ������� ����������
{
	printf("\n\t\t|   %7.2f   \t|%7.2f \t| %7.2f\t     |\n", (float)ordered, (float)random, (float)backordered);
	printf("\t\t------------------------------------------------------\n");
}

 
