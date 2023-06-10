#include "CancelEvent.h"

CancelEvent::CancelEvent(Time ET, int ID,Company* cPtr)
:Event{ET,ID,cPtr} // cancel event has a time and an ID.
{
}

CancelEvent::~CancelEvent()
{
}
bool CancelEvent::Execute(){
    Cargo *CargoPtr=CompanyPtr->getCargo(getEventId(), CompanyPtr->getWaitingNormalList());
    if(!CargoPtr) return false; //cargo wasn't found
    CompanyPtr->RemoveNormalCargo(CargoPtr, CompanyPtr->getWaitingNormalList());
    CargoPtr->DecrementNormalCargosCount();
    CargoPtr->DecrementTotalCargosCount();
    return true;
}
void CancelEvent::PrintEvent(){
    cout<<"X " << EventTime << " " << CargoId;
}
