#include "Measurement.h"//підключення інтерфейсної частини
#include <stdio.h>//бібліотека вводу-виводу
#include "in_out.h"////модуль вводу-виводу масива-вектора
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

void InsertExchangeArr3D_Measurement(int ***A)//виміру часу при гібридному алгоритмі "вставка – обмін" для масива
{
	float ordered, random, backordered;
	for (int i = 0; i < measurements_number; i++)
	{
		FillArray(A, 1);//заповнюємо масив впорядковано
		Res[i] = InsertExchangeArr3D(A);//заповнюємо масив вимірами часу, які повертає функція
		FillArray(A, 2);//заповнюємо масив рандомними значеннями
		Res1[i] = InsertExchangeArr3D(A);//заповнюємо другий масив вимірами часу, які повертає функція 
		FillArray(A, 3);//заповнюємо масив обернено впорядковано
		Res2[i] = InsertExchangeArr3D(A);//заповнюємо третій масив вимірами часу, які повертає функція
	}
	ordered = MeasurementProcessing(Res);
	random = MeasurementProcessing(Res1);
	backordered = MeasurementProcessing(Res2);
	Out_Res(ordered, random, backordered);//викликаємо функцію виведення результатів на консоль
}

//в подальших функціях ..._Measurement, дії відбуваються аналогічно 

void Insert1Arr3D_Measurement(int ***A)//виміру часу при гібридному алгоритмі "вибір№4 – обмін" для масива
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


void Select4ExchangeArr3D_Maesurement(int ***A)//виміру часу при алгоритмі сортування №1 методу прямої вставки для масива
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

void InsertExchangeVector_Measurement(int *V)//виміру часу при гібридному алгоритмі "вставка – обмін" для вектора
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


void Insert1Vector_Measurement(int *V)//виміру часу при гібридному алгоритмі "вибір№4 – обмін" для вектора
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


void Select4ExchangeVector_Maesurement(int *V)//виміру часу при алгоритмі сортування №1 методу прямої вставки для вектора
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

void OutTable()//функція для виведення "шапки" таблиці
{
	printf("\n\t\t TABLEs WITH MEASUREMENTS: \n");
	printf("\n\t\t------------------------------------------------------\n");
	printf("\t\t|\t Ordered |\t Random |\t BackOrdered | \n");
	printf("\t\t------------------------------------------------------\n");
}


void Out_Res(float ordered, float random, float backordered)//функція для виводу значень, отриманих при обробці результатів
{
	printf("\n\t\t|   %7.2f   \t|%7.2f \t| %7.2f\t     |\n", (float)ordered, (float)random, (float)backordered);
	printf("\t\t------------------------------------------------------\n");
}

 
