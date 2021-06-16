#include "M2.h"
#include "M3.h"
#include <stdio.h>
#include "MErr.h"
#include "global.h"

 
void S2(int counter_1 , int counter_2, int counter_3 )
{

	printf("S2 start\n");
	Err();
	
	S5();

	if(counter_1 < 1 || (counter_2 > 0 && counter_2 < 1) )
	{
		
		counter_3 = 0;
		S6(counter_1,counter_3);
		
	}
	
	printf("S2 end\n");
}

void S5()
{
	printf( "S5 start\n");
	Err();
	printf( "Tg5:%s\n\n", Tg5);
	printf( "Cg2:%d\n", Cg2);
	printf( "Tg4:%d\n\n", Tg4);
	printf( "S5 end\n");
}