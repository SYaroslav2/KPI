#pragma once
#include "CVehicle.h"
class CCar : public CVehicle{
public:
	CCar(int _id, char* _name, double _load_capacity, double _cost_per_mile, double _average_speed, int _max_distance);
	void Display();
	double CalculateCost(int weight, int dist);
	double CalculateTime(int dist);
	double GetAverageSpeed() { return average_speed; }
	int GetMaxDist() { return max_distance; }
	void ChangeCost(double new_cost);
protected:
		int max_distance;// max distance without refueling
		string make;//manufactorer
};
