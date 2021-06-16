#include "CDetop.h"
#include "CVehicle.h"
#include <stdexcept>



int main() {

    CDepot Depot;
    bool res = Depot.loadDataFromCSV("Depot.csv");
    if (!res) throw out_of_range(" Bad name of csv file");
    printf(" loadDataFromCSV test\n");
    Depot.ShowAll();
    printf("\n");

    const char* str = "Audi";
    char* s = new char[strlen(str) + 1];
    strcpy(s, str);

    Depot.AddCar(12, s, 30, 20, 31, 23);
    printf(" AddCar test\n");
    Depot.ShowAll();
    printf("\n");


    Depot.AddCar(7, s, 30, 20, 31, 23);
    printf(" AddCar test with existing id\n");
    Depot.ShowAll();
    printf("\n");


    res = Depot.RemoveVehicle(7);
    printf(" RemoveVehicle test with id=7\n");
    if (!res) throw out_of_range(" There is no record with this id");
    Depot.ShowAll();
    printf("\n");

    printf(" FindCheapest test\n");
    CVehicle* Vc = Depot.FindCheapest(15, 17);
    Vc->Display();
    printf("\n");

    printf(" SQL test\n");
    list<CVehicle*> lst = Depot.SQL("max_distance", "ge", "800");
    if (lst.empty()) printf(" List is empty");
    else 
        Depot.ShowRecordSet(lst);
    printf("\n");

    printf(" VehiclesAvailable test\n");
    list<CVehicle*> lst1 = Depot.VehiclesAvailable(15, 25, 21000);
    if (lst1.empty()) printf(" List is empty");
    else 
        Depot.ShowRecordSet(lst1);
    printf("\n");

    delete[] s;

	return 0;
}