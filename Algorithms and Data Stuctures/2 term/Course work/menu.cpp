#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "Measurement.h"
#include "sorting.h"
#include "in_out.h"

void timemeasurement(int*** A, int* V)    //пункт виміру часу в меню
{
	do {
		system("cls");
		int mode;
		printf("Time measurement\nSizes of array: P=%d M=%d N=%d\n", P, M, N);
		printf("\nChoose sorting:\n");
		printf("1.Insert1(vector)\n2.Select4Exchange (vector)\n");
		printf("3.InsertExchange (vector)\n4.Insert1 (array)\n");
		printf("5.Select4Exchange (array)\n6.InsertExchange(array)\n");
		printf("7.Pack mode(array)\n8.Pack mode(vector)\n");
		printf("\nPlease input the number of menu(0-back):");
		scanf_s("%d", &mode);
		switch (mode)//вибір пункту меню
		{
			case 0: return; break;
			case 1:
				system("cls");
				OutTable();
				printf("Insert1");
				Insert1Vector_Measurement(V);
				system("pause");
				break;
			case 2:
				system("cls");
				OutTable();
				printf("Select4Exchange");
				Select4ExchangeVector_Maesurement(V);
				system("pause");
				break;
			case 3:
				system("cls");
				OutTable();
				printf("InsertExchange");
				InsertExchangeVector_Measurement(V);
				system("pause");
				break;
			case 4:
				system("cls");
				OutTable();
				printf("Insert1");
				Insert1Arr3D_Measurement(A);
				system("pause");
				break;
			case 5:
				system("cls");
				OutTable();
				printf("Select4Exchange");
				Select4ExchangeArr3D_Maesurement(A);
				system("pause");
				break;
			case 6:
				system("cls");
				OutTable();
				printf("InsertExchange");
				InsertExchangeArr3D_Measurement(A);
				system("pause"); 
				break;
			case 7:
				system("cls");
				printf("Sizes of array:\n P=%d M=%d N=%d", P, M, N);
				printf("\n");
				OutTable();
				printf("Insert1");
				Insert1Arr3D_Measurement(A);
				printf("Select4Exchange");
				Select4ExchangeArr3D_Maesurement(A);
				printf("InsertExchange");
				InsertExchangeArr3D_Measurement(A);
				system("pause"); 
				break;
			case 8:
				system("cls");
				printf("Sizes of array:\n M=%d N=%d", M, N);
				printf("\n");
				OutTable();
				printf("Insert1");
				Insert1Vector_Measurement(V);
				printf("Select4Exchange");
				Select4ExchangeVector_Maesurement(V);
				printf("InsertExchange");
				InsertExchangeVector_Measurement(V);
				system ("pause");
				break;
			default:
				printf("Please input CORRECT number (Enter)");
				_getch();
				break;
		}
	} while (1);
}

void Insert1V(int* V)	//тестування сортування вставки на векторі 
{
	system("cls");
	printf("Insert1\n");
	printf("Ordered array\n");
	FillVec(V, 1);
	showVector(V);
	Insert1(V);
	printf("\nAfter sorting\n");
	showVector(V);
	printf("\n\nRandom array\n");
	FillVec(V, 2);
	showVector(V);
	Insert1(V);
	printf("\nAfter sorting\n");
	showVector(V);	
	printf("\n\nBackOrdered array\n");
	FillVec(V, 3);
	showVector(V);
	Insert1(V);
	printf("\nAfter sorting\n");
	showVector(V);
	printf("\nPress Enter for back");
	_getch();
}


void Select4ExchangeV(int* V) //тестування сортування "вибір№4 – обмін" на векторі
{
	system("cls");
	printf("Select4Exchange\n");
	printf("Ordered array\n");
	FillVec(V, 1);
	showVector(V);
	Select4Exchange(V);
	printf("\nAfter sorting\n");
	showVector(V);
	printf("\n\nRandom array\n");
	FillVec(V, 2);
	showVector(V);
	Select4Exchange(V);
	printf("\nAfter sorting\n");
	showVector(V);
	printf("\n\nBackOrdered array\n");
	FillVec(V, 3);
	showVector(V);
	Select4Exchange(V);
	printf("\nAfter sorting\n");
	showVector(V);
	printf("\nPress Enter for back");
	_getch();
}

void InsertExchangeV(int* V)	//тестування сортування "вставка – обмін" на векторі
{
	system("cls");
	printf("InsertExchange\n");
	printf("Ordered array\n");
	FillVec(V, 1);
	showVector(V);
	InsertExchange(V);
	printf("\nAfter sorting\n");
	showVector(V);
	printf("\n\nRandom array\n");
	FillVec(V, 2);
	showVector(V);
	InsertExchange(V);
	printf("\nAfter sorting\n");
	showVector(V);
	printf("\n\nBackOrdered array\n");
	FillVec(V, 3);
	showVector(V);
	InsertExchange(V);
	printf("\nAfter sorting\n");
	showVector(V);
	printf("\nPress Enter for back");
	_getch();
}

void Insert1A(int*** A) {//тестування сортування вставки на масиві
	system("cls");
	printf("Insert1\n");
	printf("Ordered array\n");
	FillArray(A, 1);
	showArray(A);
	Insert1Arr3D(A);
	printf("\nAfter sorting\n");
	showArray(A);
	printf("\n\nRandom array\n");
	FillArray(A, 2);
	showArray(A);
	Insert1Arr3D(A);
	printf("\nAfter sorting\n");
	showArray(A); 
	printf("\n\nBackOrdered array\n");
	FillArray(A, 3);
	showArray(A);
	Insert1Arr3D(A);
	printf("\nAfter sorting\n");
	showArray(A);
	printf("\nPress Enter for back");
	_getch();
}

void Select4ExchangeA(int*** A) //тестування сортування "вибір№4 – обмін" на векторі
{
	system("cls");
	printf("Select4Exchange\n");
	printf("Ordered array\n");
	FillArray(A, 1);
	showArray(A);
	Select4ExchangeArr3D(A);
	printf("\nAfter sorting\n");
	showArray(A);
	printf("\n\nRandom array\n");
	FillArray(A, 2);
	showArray(A);
	Select4ExchangeArr3D(A);
	printf("\nAfter sorting\n");
	showArray(A);
	printf("\n\nBackOrdered array\n");
	FillArray(A, 3);
	showArray(A);
	Select4ExchangeArr3D(A);
	printf("\nAfter sorting\n");
	showArray(A);
	printf("\nPress Enter for back");
	_getch();
}

void InsertExchangeA(int*** A)//тестування сортування "вставка – обмін" на масиві
{
	system("cls");
	printf("InsertExchange\n");
	printf("Ordered array\n");
	FillArray(A, 1);
	showArray(A);
	InsertExchangeArr3D(A);
	printf("\nAfter sorting\n");
	showArray(A);
	printf("\n\nRandom array\n");
	FillArray(A, 2);
	showArray(A);
	InsertExchangeArr3D(A);
	printf("\nAfter sorting\n");
	showArray(A);
	printf("\n\nBackOrdered array\n");
	FillArray(A, 3);
	showArray(A);
	InsertExchangeArr3D(A);
	printf("\nAfter sorting\n");
	showArray(A);
	printf("\nPress Enter for back");
	_getch();
}

void testsorting(int*** A, int* V) {//пункт меню для тестування сортування і виводу його на екран
	do {
		system("cls");
		int mode;
		printf("Test sortings\nSizes of array: P=%d M=%d N=%d\n", P, M, N);
		printf("\nChoose sorting:\n");
		printf("1.Insert1(vector)\n2.Select4Exchange (vector)\n");
		printf("3.InsertExchange (vector)\n4.Insert1 (array)\n");
		printf("5.Select4Exchange (array)\n6.InsertExchange(array)\n");
		printf("\nIf the window with sorting is closed, please, enter the number again");
		printf("\nPlease input the number of menu(0-back):");
		scanf_s("%d", &mode);
		switch (mode)//вибір виду сортування
		{
		case 0: return; break;
		case 1:
			Insert1V(V);
			_getch();
			break;
		case 2:
			Select4ExchangeV(V);
			_getch();
			break;
		case 3:
			InsertExchangeV(V);
			_getch();
			break;
		case 4:
			Insert1A(A);
			_getch();
			break;
		case 5:
			Select4ExchangeA(A);
			_getch();
			break;
		case 6:
			InsertExchangeA(A);
			_getch();
			break;
		default:
			printf("Please input CORRECT number (Enter)");
			_getch();
			break;
		}
	} while (1);
}


void Menu(int*** A, int* V) {//меню з вибором тестування часу і тестування сортувань
	do {
		system("cls");
		printf("\n\n");
		printf("\t\t\t\t -------------------------------------------------\n");
		printf("\t\t\t\t|                 COURSE WORK                     |\n");
		printf("\t\t\t\t|  The study of the effectiveness of different    |\n");
		printf("\t\t\t\t|  methods for sorting algorithms on multidime-   |\n");
		printf("\t\t\t\t|              nsional arrays                     |\n");
		printf("\t\t\t\t|                 Variant #158.                   |\n");
		printf("\t\t\t\t|             Made by Savytskiy Yaroslav          |\n");
		printf("\t\t\t\t|                 group KV - 84                   |\n");
		printf("\t\t\t\t ------------------------------------------------- \n");
		printf("\n\n\n");
		printf("\t\t\t\tChoose mode:\n\t\t\t\t1 - time measurement\n");
		printf("\t\t\t\t2 - testing sorting\n\t\t\t\t3 - exit: ");
		int vote;
		scanf_s("%d", &vote);
		switch (vote)//вибір одного з пунктів
		{
		case 1: timemeasurement(A, V); break;
		case 2: testsorting(A, V); break;
		case 3: return;
		default:
			printf("\t\t\t\tPlease input CORRECT number (Press Enter)");
			_getch();
			break;
		}
	} while (1);
}