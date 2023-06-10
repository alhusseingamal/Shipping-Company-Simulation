#include "Truck.h"
int Truck::IDGenerator=0;// initializing of static data member used for assigning IDs to trucks
int Truck::TotalTrucksCount=0;
int Truck::VIPTrucksCount=0;
int Truck::SpecialTrucksCount=0;
int Truck::NormalTrucksCount=0;
Time Truck::TotalTruckActiveTime(0,0);
Truck::Truck (char TT, int TC, int MT, int j, int S, bool NSA) 
    : TruckType{TT} , TruckCapacity{TC}, MaintenanceTime{MT}, j{j}, Speed{S}, TruckID{++IDGenerator}, NumberofDeliveries{0},TimeToComeBack{1},
    TruckActiveTime(0,0),CargosDeliveredbyTruck{0}, NightShiftAvailability{NSA}, TruckPriority{0}{
    TotalTrucksCount++;
    if(this->getTruckType()=='V') VIPTrucksCount++;
    else if(this->getTruckType()=='S') SpecialTrucksCount++;
    else if(this->getTruckType()=='N') NormalTrucksCount++;
    setTruckPriority();
}
Truck::~Truck(){}
//Getters
void Truck::setTruckPriority(){TruckPriority=10*TruckCapacity+1*Speed;}
int Truck::getTruckPriority() const{return TruckPriority;}
int Truck::getTotalTrucksCount() const{return TotalTrucksCount;}
int Truck::getVIPTrucksCount() const{return VIPTrucksCount;}
int Truck::getSpecialTrucksCount() const{return SpecialTrucksCount;}
int Truck::getNormalTrucksCount() const{return NormalTrucksCount;}
PriorityQueue<Cargo*>* Truck::getCargoList(){return &CargoList;}
char Truck::getTruckType() const{return TruckType;}
int Truck:: getTruckMaintenanceTime() const{return MaintenanceTime;}
int Truck::getTruckCapacity() const{return TruckCapacity;}
int Truck::getTruckSpeed() const{return Speed;}
int Truck::getTruckID() const{return TruckID;}
Time Truck::getTruckMovingTime() const{return MovingTime;}
Time Truck::getDI()const{return DI;}
int Truck::getCargosDeliveredbyTruck() const {return CargosDeliveredbyTruck;}
Time Truck::getTruckCheckupTime()const{return TruckCheckupTime;}
// Setters
void Truck::setTruckLoadingTime(Time t){TruckLoadingTime=t;}
Time Truck::getTruckLoadingTime()const{return TruckLoadingTime;}
void Truck::setTruckDeliveryTime(){
    Time ZeroTime(0,0);
    int cargosDeliveryTime=ceil((float)furthestDDLoadedCargo/this->getTruckSpeed())+CargosUnloadTimeSum;
    TruckDeliveryTime=ZeroTime+cargosDeliveryTime;
}
Time Truck::getTruckDeliveryTime()const{return TruckDeliveryTime;}
Time Truck::getTruckActiveTime() const {return TruckActiveTime;}
void Truck::IncrementTruckActiveTime(){
    Time t1=this->getTruckLoadingTime();
    Time t2=this->getTruckDeliveryTime();
    Time t=t1+t2;
    TruckActiveTime=TruckActiveTime+t; 
    TotalTruckActiveTime=TotalTruckActiveTime+t;
}
Time Truck::getTotalTrucksActiveTime() const{
    return TotalTruckActiveTime;
}
void Truck::setDI(){
    int cargosDeliveryTime=ceil((float)furthestDDLoadedCargo/this->getTruckSpeed())+CargosUnloadTimeSum;
    DI = MovingTime + cargosDeliveryTime + TimeToComeBack;
}
void Truck::setTruckMovingTime(Time mt){MovingTime = mt;}
void Truck::resetCargoRelatedTruckInfo(){
    CargosUnloadTimeSum=0;
    MovingTime=MovingTime-MovingTime; //reset to zero
    furthestDDLoadedCargo=0;
}
void Truck::IncrementCargosDeliveredbyTruck(){CargosDeliveredbyTruck++;}
void Truck::setTruckCheckupTime(){TruckCheckupTime=DI+MaintenanceTime;}
void Truck::LoadCargo(Cargo*c){
    CargoList.enqueue(c,1);// -1 if we deliver nearer trucks first which is reasonable and more realistic
    c->setCargoTruck(this);
    c->setCargoTID(this);
    if(c->getDeliveryDistance()>furthestDDLoadedCargo) furthestDDLoadedCargo=c->getDeliveryDistance();
    CargosUnloadTimeSum=CargosUnloadTimeSum+c->getLoadTime();
}

void Truck::UnloadCargo(Cargo*c){ //Unloads Cargo from Truck
    CargoList.dequeue(c); // cargo is removed from the list of cargos loaded on the truck
    c->setCargoTruck(nullptr); // Cargo is no longer loaded on a truck so we set the pointer to the truck carrying it to nullptr
}
void Truck::StampCargos(){// After a truck is fully loaded; MT,WT and CDT are assigned for each cargo in CargoList
    Cargo*cargoPtr;
    int cargoListSize=CargoList.getCount();
    for(int i=0;i<cargoListSize;i++){
        CargoList.dequeue(cargoPtr); // In code, we assume we removed the cargo to stamp it, and we will load it again
        cargoPtr->AssignMT(this); // the moving time of each cargo is the moving time of the truck carring it, reasonable
        cargoPtr->calculateWT(); // calculate the time before a cargo is delivered
        cargoPtr->calculateCDT(this); // cargo delivery time
        CargoList.enqueue(cargoPtr,-1*cargoPtr->getCDT().TimetoHrs());
    }
}
void Truck::ArrangeTruckCargoList(){
    Cargo* cargoPtr;
    for(int i=0;i<this->getCargoList()->getCount();i++){
        this->getCargoList()->dequeue(cargoPtr);
        this->getCargoList()->enqueue(cargoPtr,-1*cargoPtr->getCDT().TimetoHrs());
    }
}

int Truck::getNumberofDeliveries() const {return NumberofDeliveries;}//returns number of deliveries
void Truck::IncremenetNumberofDeliveries(){NumberofDeliveries++;}// called everytime a truck empties its CargoList
bool Truck::NeedsCheckup(){ 
    if(this->NumberofDeliveries%(this->j)==0) return true;
    return false;
}

ostream &operator<<(ostream &output, Truck &truck){
    output<<truck.getTruckSpeed()<<" "<<truck.getTruckCapacity()<<" "<<truck.getTruckType()<<" ";
    return output;
}

