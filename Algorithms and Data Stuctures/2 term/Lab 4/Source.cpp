#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

float Rec_Down(float F, int i, int n, float S);
float Rec_Up(float F, int n, float& S);
float Rec_Up_Down(float F,int i, int n, float S);

int main()
{
	int i, n = 11;
	float F, Mult = 1, S = 1;

	S  = Rec_Down(1, 2, n, S);
	printf(" \n Recursion on down: %f", S);
	S = 1;
	Rec_Up(1, n + 1, S);
	printf(" \n Recursion on up: %f", S);
	S = 1;
	S = Rec_Up_Down(1, 2, n, S);
	printf(" \n Recursion on up and down: %f", S);
	S = 1;
	for(i = 2; i <= n; i++)
	{
		Mult = sin(i) - 2 * cos(Mult);
		S = S + Mult;
	}
	printf("\n Cycle: %f", S);

	_getch();
	return 0;
}

float Rec_Down(float F, int i, int n, float S)
{
	
	if (i <= n)
	{
		F = sin(i) - 2 * cos(F);
		S = S + F;
		return Rec_Down(F, ++i, n, S);
	}
	else 
	{
		return S;
	}
}

float Rec_Up(float F, int n, float& S)
{
	if (n > 2)
	{
		F = sin(n) - 2 * cos(Rec_Up(F, --n, S));
		S = S + F;
		return F;
	}
	else
	{
		return  1;
	}
}

float Rec_Up_Down(float F,int i, int n, float S)
{
	F = sin(i) - 2 * cos(F);
	if (i <= n)
	{
		return F + Rec_Up_Down(F, ++i, n, S);
	}
	else
	{
		return S;		
	}
}