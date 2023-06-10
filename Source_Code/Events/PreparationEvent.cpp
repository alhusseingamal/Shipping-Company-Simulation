#include "PreparationEvent.h"

PreparationEvent::PreparationEvent(Time ET, int ID, char CT, int DIST, int LT, int cost, Company* cPtr)
:Event{ET,ID, cPtr}, CargoType{CT}, CargoDistance{DIST}, CargoLoadingTime{LT}, CargoCost{cost}
{
    
}

PreparationEvent::~PreparationEvent()
{
}

bool PreparationEvent::Execute(){
    Cargo *CargoPtr = new Cargo(EventTime, CargoLoadingTime, CargoType, CargoDistance, CargoCost, CargoId);
    if(!CargoPtr) return false;//checks that cargo was allocated successfully
    CompanyPtr->AddCargo(CargoPtr);
    return true;
}
void PreparationEvent::PrintEvent(){
    cout<<"R "<<CargoType<<" "<<EventTime<<" "<<CargoId<<" "<<CargoDistance<<" "<<CargoLoadingTime<<" "<<CargoCost;
}


