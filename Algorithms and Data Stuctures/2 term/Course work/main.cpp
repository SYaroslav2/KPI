#include <stdio.h>
#include <time.h>
#include <conio.h>
#include "in_out.h"
#include "menu.h"



int main()
{
	int*** A = NULL;
	int* V = NULL;
	srand(time(NULL));
	A = Multi_Dimentional_Dynamic_Array();//������� ��� ��������� ���������� ���������� ������
	V = Multi_Dimentional_Dynamic_Vector();//������� ��� ��������� ���������� ������
	
	Menu(A, V);//������ ����
	
	FreeMemory(A, V);//������ ��� �������� ���'�� 

	_getch();
	return 0;
}