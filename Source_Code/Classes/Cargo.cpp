#include "Cargo.h"
#include "Truck.h"

int Cargo::VIPCargosCount=0;
int Cargo::NormalCargosCount=0;
int Cargo::SpecialCargosCount=0;
int Cargo::TotalCargosCount=0;
Time Cargo::CargototalWaitTime(0,0);  
int Cargo::AutoPromotedCargosCount=0;
Cargo::Cargo(Time PT, int LT, char CT, int DD, int cost, int id):
PrepTime{PT}, LoadTime{LT}, CargoType{CT}, DeliveryDistance{DD}, Cost{cost}, CargoID{id}, VIPPriority{0}, CDT(0,0),CargoTruck{nullptr},
AutoPromoted{false}
{
    if(CargoType=='V'){ setVIPPriority(); IncrementVIPCargosCount();}
    else if(CargoType=='S'){SpecialCargosCount++;}
    else if(CargoType=='N'){NormalCargosCount++;}
    TotalCargosCount++;
}

void Cargo::DecrementNormalCargosCount(){NormalCargosCount--;}
void Cargo::IncrementVIPCargosCount(){VIPCargosCount++;}
void Cargo::DecrementTotalCargosCount(){TotalCargosCount--;}
int Cargo::getNormalCargosCount() const{return NormalCargosCount;}
int Cargo::getSpecialCargosCount() const{return SpecialCargosCount;}
int Cargo::getVIPCargosCount() const{return VIPCargosCount;}
int Cargo::getTotalCargosCount() const{
    TotalCargosCount = NormalCargosCount + SpecialCargosCount + VIPCargosCount;
    return TotalCargosCount;
}
void Cargo::setVIPPriority(){VIPPriority=0.5*PrepTime.TimetoHrs()+0.3*Cost+0.2*DeliveryDistance;}
bool Cargo::isAutoPromoted(){return AutoPromoted;}
void Cargo::setAutoPromoted(){this->AutoPromoted=true;}
float Cargo::getPercentageofAutoPromotedCargos(){return ((float)AutoPromotedCargosCount/(float)TotalCargosCount)*100;}
void Cargo::IncrementAutoPromotedCargosCount(){AutoPromotedCargosCount++;}
int Cargo::getAutoPromotedCargosCount() const{return AutoPromotedCargosCount;}
void Cargo::IncrementCargototalWaitTime(Time &t){CargototalWaitTime=CargototalWaitTime+t;}
Time Cargo::getCargototalWaitTime() const{return CargototalWaitTime;}
Time Cargo::getCargoAverageWaitTime() const{
    Time temp;
    temp=temp.HrstoTime(ceil((float)CargototalWaitTime.TimetoHrs()/TotalCargosCount));
    return temp;
}

void Cargo::UpdatetoVIP(){
    CargoType='V';
    IncrementVIPCargosCount();
    DecrementNormalCargosCount();
    setVIPPriority();
}

int Cargo::getVIPPriority() const{return VIPPriority;}
Time Cargo::getCargoPreparationTime() const{return PrepTime;}
char Cargo::getCargoType() const{return CargoType;}
int Cargo::getCargoID() const{return CargoID;}
int Cargo::getLoadTime() const{return LoadTime;}
int Cargo::getDeliveryDistance() const{return DeliveryDistance;}
int Cargo::getCargoCost() const{return Cost;}
void Cargo::AssignMT(Truck*t){// t is the truck on which the Cargo is loaded
    MT=t->getTruckMovingTime();
}
Time Cargo::getMT() const{return MT;}
void Cargo::calculateWT(){
    Time pt=PrepTime;//to avoid overloading operator - for const objects of Time
    WT=MT-pt;
}
Time Cargo::getWT() const{return WT;}
void Cargo::calculateCDT(Truck*t){
    int tt= this->getLoadTime()+ ceil((float)this->getDeliveryDistance()/t->getTruckSpeed());
    CDT=MT+tt;
}
Time Cargo::getCDT() const{return CDT;}
void Cargo::setCargoTruck(Truck* t){CargoTruck=t;}
Truck* Cargo::getCargoTruck(){return CargoTruck;}
void Cargo::setCargoTID(Truck* t){CargoTID=t->getTruckID();}
int Cargo::getCargoTID() const {return CargoTID;}
ostream &operator<<(ostream &output, Cargo &c){    
    output<<c.getCargoID()<<" "<<c.getCargoType();cout<<" ";c.getMT().displayTime();output<<" ";c.getCDT().displayTime();
        return output;
}
Cargo::~Cargo(){}