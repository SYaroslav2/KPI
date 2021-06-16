#pragma once

#ifndef __Measurement_H__
#define __Measurement_H__
#include "CommonVector.h"//������ � ��������
#include <time.h>
#define measurements_number 28//������� �����
#define rejected_number 2
#define min_max_number 3
extern clock_t Res[measurements_number];//������ ��� ���� ��������������
extern clock_t Res1[measurements_number];//������ ��� ���� ����������������
extern clock_t Res2[measurements_number];//������ ��� ���� ��������-��������������
//���������
void OutTable();
void Out_Res(float ordered, float random, float backordered);
void Select4ExchangeArr3D_Maesurement(int ***A);
void Insert1Arr3D_Measurement(int ***A);
void InsertExchangeArr3D_Measurement(int ***A);
void Select4ExchangeVector_Maesurement(int *V);
void Insert1Vector_Measurement(int *V);
void InsertExchangeVector_Measurement(int *V);
float MeasurementProcessing(clock_t* Res);

#endif
