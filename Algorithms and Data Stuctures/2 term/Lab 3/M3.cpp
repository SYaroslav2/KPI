#include "M2.h"
#include "M3.h"
#include <stdio.h>
#include "MErr.h"
#include "global.h"
int counter_1 = 0;
int counter_2 = 0;
int counter_3 = 0;
int counter_4 = 0;
void S3()
{
	printf("S3 start\n");

	Err();

	printf( "Cg1:%d\n", Cg1);
	printf( "Tg2:%s\n", Tg2);
	printf( "Cg3:%s\n\n", Cg3);
	counter_3 = 2;
	S6(counter_1, counter_3);

	S7();

	S8();

	printf("S3 end\n");
}

void S6(int counter_1, int counter_3)
{
	printf( "S6 start\n");
	if (counter_3 == 2)
	{
		Err();
		counter_2++;
		S2(counter_1, counter_2, counter_3);
	}
	counter_4++;
	if (counter_4 == 1)
	{
		Err();
		counter_1++;
		S2(counter_1, counter_2, counter_3);
	}
	

	printf( "S6 end\n");
}

void S7()
{
	printf("S7 start\n");
	Err();
	//printf( "Vg3:%d\n", Vg3);
	//printf( "Vg4:%d\n", Vg4);
	printf( "S7 end\n");
}


void S8()
{
	printf( "S8 start\n");
	Err();
	printf( "\nCg3:%s\n", Cg3);
	//fprintf(f, "Vg2:%d\n", Vg2);
	printf("Tg1:%d\n\n", Tg1);
	printf( "S8 end\n");
}