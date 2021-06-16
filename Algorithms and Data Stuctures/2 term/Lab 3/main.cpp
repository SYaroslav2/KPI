#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "MErr.h"
#include "M1.h"
#include "M2.h"
#include "M3.h"
#include "global.h"
int main()
{
	common();
	int counter_1 = 0, counter_2 = 0, counter_3 = 0;
	//printf("main start\n");
	Err();
	S1();
	printf( "\n");

	S2(counter_1, counter_2, counter_3);
	printf("\n");

	S3();
	printf("main end");

	_getch();
	return 0;
}