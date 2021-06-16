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
	A = Multi_Dimentional_Dynamic_Array();//функція для створення динамічного тривірмного масива
	V = Multi_Dimentional_Dynamic_Vector();//функція для створення динамічного масиву
	
	Menu(A, V);//виклик меню
	
	FreeMemory(A, V);//фунцкія для очищення пам'яті 

	_getch();
	return 0;
}