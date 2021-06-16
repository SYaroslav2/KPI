#pragma once
#include "CVehicle.h"
#include "CCar.h"
#include "CTrain.h"

class CDepot {//add whatever you need

public:
	bool loadDataFromCSV(const char* path); 
	CVehicle* AddCar(int _id, char* _name, double _load_capacity, double _cost_per_mile, double _average_speed, int _max_distance); //????????????????????
	CVehicle* AddTrain(int _id, char* _name, double _load_capacity, double _cost_per_mile, double _average_speed, int _max_distance); //???????????????????? в описании тип Vehicle*
	bool RemoveVehicle(int id);
	void ShowAll();
	CVehicle*  FindCheapest(double weight, double dist);/*очевидно, что в методичке ошибка, 
	потому что эта фунцкия должна вернуть одну запись*/
	list<CVehicle*> SQL(const char* field, const char* cond, const char* value);
	void ShowRecordSet(list< CVehicle*> rs);
	list<CVehicle*> VehiclesAvailable(double weight, double dist, double cost); /*очевидно, что в методичке ошибка, 
	потому что в описании функции написано, что она возвращает "набор записей"*/
	void ChangeCostPerMile(int id, double new_cost); 

private:
	bool Search_for_id(int id);
	list<CVehicle*> vehicles;
};