#pragma once
#ifndef INO_OUT_H_INCLUDED
#define INO_OUT_H_INCLUDED
#include <stdio.h>//бібліотека вводу-виводу
#include <stdlib.h>//бібліотека для виділення пам'яті

//прототипи

void FillArray(int ***A, int b);
void showArray(int ***A);
void FillVec(int *Vec, int mode);
void showVector(int *Vec);
int*** Multi_Dimentional_Dynamic_Array();
int* Multi_Dimentional_Dynamic_Vector();
void FreeMemory(int***A, int* Vec);



#endif // INO_OUT_H_INCLUDED