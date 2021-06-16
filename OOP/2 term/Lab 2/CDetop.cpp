#include "CDetop.h"

bool CDepot::Search_for_id(int id) {
	
	for(auto it = vehicles.begin(); it != vehicles.end(); it++) {
		CVehicle* CV = *it;
		if (CV->GetId() == id) return true;
	}
	return false;
}

bool CDepot::loadDataFromCSV(const char* path) {
	char* string, * str_ptr;
	int j, lenght;
	int _type, _id, _max_distance;
	
	double _average_speed, _load_capacity, _cost_per_mile;
	char str[256], _name[256];
	
	FILE* csv_File;
	csv_File = fopen(path, "r");
	if (!csv_File) return false;

	
	
	while (fgets(str, 255, csv_File)) {
		
		lenght = strlen(str);
		string = (char*)malloc(lenght + 1);
		str_ptr = string;
		
		for (j = 0; j < lenght; j++) {
			if (str[j] == ';') {
				string[j] = '\0';
			
			}
			else
				string[j] = str[j];
		}
		string[j] = '\0';
		_id = atoi(str_ptr);
		str_ptr += strlen(str_ptr) + 1;
		_type = atoi(str_ptr);
		str_ptr += strlen(str_ptr) + 1;
		strcpy(_name, str_ptr);
		str_ptr += strlen(str_ptr) + 1;
		_load_capacity = atof(str_ptr);
		str_ptr += strlen(str_ptr) + 1;
		_cost_per_mile = atof(str_ptr);
		str_ptr += strlen(str_ptr) + 1;
		_average_speed = atof(str_ptr);
		if (strcmp(_name, "Electrical") == 0)
		{
			free(string);
			AddTrain(_id, _name, _load_capacity, _cost_per_mile, _average_speed, 0);
			continue;
		}
		str_ptr += strlen(str_ptr) + 1;
		_max_distance = atoi(str_ptr);
		free(string);
		if (_type == 0) {
			AddCar(_id, _name, _load_capacity, _cost_per_mile, _average_speed, _max_distance);
		}
		else AddTrain(_id, _name, _load_capacity, _cost_per_mile, _average_speed, _max_distance);
	}
	fclose(csv_File);

	return true;
}


CVehicle* CDepot::AddCar(int _id, char* _name, double _load_capacity, double _cost_per_mile, double _average_speed, int _max_distance) {
	if (Search_for_id(_id)) return NULL;

	CCar* car = new CCar(_id, _name, _load_capacity, _cost_per_mile, _average_speed, _max_distance);
	if (!car) return NULL;
	CVehicle* CV_ptr = car;
	if (!CV_ptr) return NULL;
	vehicles.push_back(CV_ptr);
	return CV_ptr;
}



CVehicle* CDepot::AddTrain(int _id, char* _name, double _load_capacity, double _cost_per_mile, double _average_speed, int _max_distance) {
	if (Search_for_id(_id)) return NULL;

	if (strcmp(_name, "Diezel") == 0) {
		CTrain* Diezel = new CTrain(_id, _name, _load_capacity, _cost_per_mile, _average_speed, _max_distance);
		if (!Diezel) return NULL;
		CVehicle* CV_ptr = Diezel;
		if (!CV_ptr) return NULL;
		vehicles.push_back(CV_ptr);
		return CV_ptr;
	}
	if (strcmp(_name, "Electrical") == 0) {
		CTrain* Electrical = new CTrain(_id, _name, _load_capacity, _cost_per_mile, _average_speed);
		if (!Electrical) return NULL;
		CVehicle* CV_ptr = Electrical;
		if (!CV_ptr) return NULL;
		vehicles.push_back(CV_ptr);
		return CV_ptr;
	}

	return NULL;
}



bool CDepot::RemoveVehicle(int id) {

	for (auto it = vehicles.begin(); it != vehicles.end(); it++) {
		CVehicle* CV = *it;
		if (CV->GetId() == id) { 
			vehicles.erase(it);
			return true; 
		}
	}
	return false;
}



void CDepot::ShowAll() {
	printf("%-10s%-5s%-20s%-20s%-20s%-20s%-20s\n", " Type", "Id", "Man/fuel type", "Average speed",  "Load capacity", "Cost per mile", "Max dist");
	for (auto it = vehicles.begin(); it != vehicles.end(); it++) {
		CVehicle* cv = *it;
		cv->Display();
	}
	
}




CVehicle* CDepot::FindCheapest(double weight, double dist) {
	list<CVehicle*>::iterator lst;
	lst = vehicles.begin();
	CVehicle* Min = *lst;
	double min_cost = Min->CalculateCost((int)weight, (int)dist);
	for (auto it = vehicles.begin(); it != vehicles.end(); it++) {
		CVehicle* CV;
		CV = *it;
		if(CV->CalculateCost((int)weight, (int)dist) < min_cost) Min = CV, min_cost = CV->CalculateCost((int)weight, (int)dist);
	}
	return Min;
}



list<CVehicle*> CDepot::SQL(const char* field, const char* cond, const char* value) {
	list<CVehicle*> lst;
	string Field = field, Cond = cond;
	for (auto it = vehicles.begin(); it != vehicles.end(); it++) {
		CVehicle* CV;
		CV = *it;
		if (Field == "average_speed") {
			if (Cond == "le") {
				if (typeid(*CV) == typeid(CCar)) {
					if (dynamic_cast<CCar*>(CV)->GetAverageSpeed() <= atof(value))
						lst.push_back(CV);

				}
				else if (typeid(*CV) == typeid(CTrain)) {
					if (dynamic_cast<CTrain*>(CV)->GetAverageSpeed() <= atof(value))
						lst.push_back(CV);
				}
			}
			else if (Cond == "ge") {
				if (typeid(*CV) == typeid(CCar)) {
					if (dynamic_cast<CCar*>(CV)->GetAverageSpeed() >= atof(value))
						lst.push_back(CV);
				}
				else if (typeid(*CV) == typeid(CTrain)) {
					if (dynamic_cast<CTrain*>(CV)->GetAverageSpeed() >= atof(value))
						lst.push_back(CV);
				}
			}
		}
		else if (Field == "max_distance") {
			if (Cond == "le") {
				if (typeid(*CV) == typeid(CCar)) {
					if (dynamic_cast<CCar*>(CV)->GetMaxDist() <= atoi(value))
						lst.push_back(CV);

				}
				else if (typeid(*CV) == typeid(CTrain)) {
					if (dynamic_cast<CTrain*>(CV)->GetMaxDist() <= atoi(value))
						lst.push_back(CV);
				}
			}
			else if (Cond == "ge") {
				if (typeid(*CV) == typeid(CCar)) {
					if (dynamic_cast<CCar*>(CV)->GetMaxDist() >= atoi(value))
						lst.push_back(CV);

				}
				else if (typeid(*CV) == typeid(CTrain)) {
					if (dynamic_cast<CTrain*>(CV)->GetMaxDist() >= atoi(value))
						lst.push_back(CV);
				}
			}
		}
	}
	return lst;

}



void CDepot::ShowRecordSet(list< CVehicle*> rs) {
	for (auto it = rs.begin(); it != rs.end(); it++) {
		CVehicle* CV = *it;
		CV->Display();
	}
}



list<CVehicle*> CDepot::VehiclesAvailable(double weight, double dist, double cost) {
	list<CVehicle*> lst;

	for (auto it = vehicles.begin(); it != vehicles.end(); it++) {
		CVehicle* CV = *it;
		if (typeid(*CV) == typeid(CCar)) {
			if (dynamic_cast<CCar*> (CV)->GetMaxDist() >= dist && dynamic_cast<CCar*> (CV)->CalculateCost((int)weight, (int)dist) < cost)
				lst.push_back(CV);
		}
		else if (typeid(*CV) == typeid(CTrain)) {
			if (dynamic_cast<CTrain*> (CV)->GetMaxDist() >= dist && dynamic_cast<CTrain*> (CV)->CalculateCost((int)weight, (int)dist) < cost)
				lst.push_back(CV);
		}
	}
	return lst;
}



void CDepot::ChangeCostPerMile(int id, double new_cost) {
	if (!Search_for_id(id)) return;
	
	for (auto it = vehicles.begin(); it != vehicles.end(); it++) {
		CVehicle* CV = *it;
		if (!CV) return;
		if (CV->GetId() == id) {
			if (typeid(*CV) == typeid(CCar))
				dynamic_cast<CCar*>(CV)->ChangeCost(new_cost);
			else if (typeid(*CV) == typeid(CTrain))
				dynamic_cast<CTrain*>(CV)->ChangeCost(new_cost);
			return;
		}
	}
}