#include "M1.h"
#include <stdio.h>
#include "MErr.h"
#include "global.h"


void S1() {
	printf("S1 start\n");

	S4();

	Err();

	printf( " S1 end\n");
}

void S4() {
	printf("S4 start\n");
	Err();
	printf( " Cg3:%s\n", Cg3);
	printf( "Tg2:%s\n\n", Tg2);
	printf("S4 end\n");
}