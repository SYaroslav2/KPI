#include "CTrain.h"

CTrain::CTrain(int _id, char* _name, double _load_capacity, double _cost_per_mile, double _average_speed)
    : CVehicle(_id, 0, _average_speed, _load_capacity, _cost_per_mile), type(_name) {}


CTrain::CTrain(int _id, char* _name, double _load_capacity, double _cost_per_mile, double _average_speed, int _max_distance)
    : CVehicle(_id, 0, _average_speed, _load_capacity, _cost_per_mile), type(_name), max_distance(_max_distance) {}


void CTrain::Display() {

    if (strcmp(type.c_str(),"Electrical") == 0) {
        printf("%-10s%-5d%-20s%-20.2lf%-20.2lf%-20.2lf\n",
            " Train", id, type.c_str(), average_speed, load_capacity, cost_per_mile);
    }
    else
        printf("%-10s%-5d%-20s%-20.2lf%-20.2lf%-20.2lf%-10d\n",
        " Train", id, type.c_str(), average_speed, load_capacity, cost_per_mile, max_distance);
}

double CTrain::CalculateCost(int weight, int dist) {
    if (type == "Diezel" && dist > max_distance) return -1;
    return weight * dist * cost_per_mile;
}

double CTrain::CalculateTime(int dist) {
    if (type == "Diezel" && dist > max_distance) return -1;
    return dist / average_speed;
}
\
void CTrain::ChangeCost(double new_cost) {
    cost_per_mile = new_cost;
}