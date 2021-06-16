#include "CCar.h"


CCar::CCar(int _id, char* _name, double _load_capacity, double _cost_per_mile, double _average_speed, int _max_distance)
	: CVehicle(_id, 0, _average_speed, _load_capacity, _cost_per_mile), make(_name), max_distance(_max_distance) {}


void CCar::Display() {
    printf("%-10s%-5d%-20s%-20.2lf%-20.2lf%-20.2lf%-10d\n",
        " Truck", id, make.c_str(), average_speed, load_capacity, cost_per_mile, max_distance);
}

double CCar::CalculateCost(int weight, int dist) {
    if (dist > max_distance) return -1;
    return weight * dist * cost_per_mile;
}

double CCar::CalculateTime(int dist) {
    if (dist > max_distance) return -1;
    return dist / average_speed;
}


void CCar::ChangeCost(double new_cost) {
    cost_per_mile = new_cost;
}