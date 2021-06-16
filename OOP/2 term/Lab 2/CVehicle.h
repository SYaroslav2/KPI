#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include<string>
#include <list>
#include <typeinfo>

#pragma warning (disable : 26495)
#pragma warning (disable : 26451)
#pragma warning (disable : 6011)
#pragma warning (disable : 6386)
#pragma warning (disable : 6387)


using namespace std;


class CVehicle
{
public:
	CVehicle() {}; 
	CVehicle(int _id, int _v_type, double _average_speed, double _load_capacity, double _cost_per_mile) :
		average_speed(_average_speed), load_capacity(_load_capacity),
		cost_per_mile(_cost_per_mile),
		id(_id), v_type(_v_type) {};
	virtual void Display() = 0;
	//вартість перевезення weight кг на dist км
	//якщо перевезення здійснюється вантажівкою, або дізелем і dist > //max_distance повертає -1
	virtual double CalculateCost(int weight, int dist) = 0;
	// час перевезення вантажів
	//якщо перевезення здійснюється вантажівкою або дизелем і dist > //max_distance повертає -1
	virtual	double CalculateTime(int dist) = 0;
	virtual int GetId() { return id; }
protected:
	int v_type;
	int id;
	double average_speed;
	double load_capacity;
	double cost_per_mile;

};