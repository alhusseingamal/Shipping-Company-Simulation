#include "PromotionEvent.h"

PromotionEvent::PromotionEvent(Time ET, int ID, int EM, Company* cPtr)
:Event{ET, ID, cPtr}, ExtraMoney{EM}
{
}

PromotionEvent::~PromotionEvent()
{
}
bool PromotionEvent::Execute(){
    Cargo* CargoPtr=CompanyPtr->getCargo(getEventId(),CompanyPtr->getWaitingNormalList());
    if(CargoPtr){
        CargoPtr->UpdatetoVIP();
        CompanyPtr->AddCargo(CargoPtr);
        CompanyPtr->RemoveNormalCargo(CargoPtr,CompanyPtr->getWaitingNormalList());
        return true;
    }
    return false;
    
}
void PromotionEvent::PrintEvent(){
    cout<<"P "<<EventTime<<" "<<CargoId<<" "<<ExtraMoney;
}

