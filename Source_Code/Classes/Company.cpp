#include "Company.h"
Company::Company(): Clock(1,0){} // company time starts at day = 1, hour = 0

Company::~Company(){}

bool Company::AddCargo(Cargo *c){
    if(c->getCargoType()=='V'){ 
        WaitingVIP.enqueue(c,c->getVIPPriority());
        return true;
    }else if(c->getCargoType()=='S'){
        WaitingSpecial.enqueue(c);
        return true;
    }else if(c->getCargoType()=='N'){
        WaitingNormal.insertLast(c);
        return true;
    }
    return false;
}
bool Company::checkWH(){
    if(Clock.getHour() >= 5 && Clock.getHour() <=23) return true;
    return false;
}


Cargo* Company::getCargo(int Id,LinkedList<Cargo*>*q){
    for(int i=1;i<=(q->getCount());i++){
        cargoPtr=q->getEntry(i);
        if(cargoPtr->getCargoID()==Id) return cargoPtr; 
    }    
    return nullptr;//this cargo doesn't exist
}

void Company::RemoveNormalCargo(Cargo *c, LinkedList<Cargo*>*q){// Used in promotion and cancel events
    q->Remove(c);
}

int Company::getTotalEventsNumber(){return TotalEventsTime;}

bool Company::ReadInputFile(){
    ifstream myfile;
    myfile.open(UIPtr->readInputFileName());
    if(!myfile.is_open()) return false;// checks if file is successfully opened
    int N, S, V, NS, SS, VS, NTC, STC, VTC, J, CN, CS, CV, AutoP, MaxW;
    myfile>>N>>S>>V>>NS>>SS>>VS>>NTC>>STC>>VTC>>J>>CN>>CS>>CV>>AutoP>>MaxW;
    setMaxW(MaxW);   //might be set directly without the setter
    setAutoP(AutoP); //might be set directly without the setter
    int TruckSpeed = 0,TruckCapacity = 0;
    bool NightShift = false;
    // Truck Speeds are randomized within a reasonable range
    // Note: it doesn't make sense for the truck speeds to be random, but the requirement was to allow for
    // trucks with different speeds, while keeping the input file format the std::is_same
    // Hence the only viable option was to randomize the speeds
    // The same applies for trucks that can work night shifts
    for(int i = 0; i < V; i++){
        srand(i); // srand(time(NULL)); better but there's a problem with time function 
        TruckSpeed= 0.8 * VS + (rand() % VS); //random generated speed required for bonus part
        TruckCapacity=0.5 * VTC + (rand()%VTC);
        NightShift = (rand() % 100 > 70);
        truckPtr= new Truck('V', TruckCapacity, CV, J, TruckSpeed, NightShift);
        VIPTrucks.enqueue(truckPtr,truckPtr->getTruckPriority());
        if(NightShift) NightShiftTrucks.enqueue(truckPtr,truckPtr->getTruckPriority());
    }
    
    for(int i = 0; i < S; i++){
        srand(i);
        TruckSpeed= 0.8*SS+(rand() % SS); //random generated speed 
        TruckCapacity=0.5*STC+(rand()%STC);
        NightShift=(rand()%100>70);
        truckPtr = new Truck('S',TruckCapacity,CS,J,TruckSpeed,NightShift);
        SpecialTrucks.enqueue(truckPtr,truckPtr->getTruckPriority());
        if(NightShift) NightShiftTrucks.enqueue(truckPtr,truckPtr->getTruckPriority());
    }
    
    for(int i=0;i<N;i++){
        srand(i);
        TruckSpeed= 0.8*NS+(rand() % NS); //random generated speed 
        TruckCapacity=0.5*NTC+(rand()%NTC);
        NightShift=(rand()%100>70);
        truckPtr = new Truck('N',TruckCapacity,CN,J,TruckSpeed,NightShift);
        NormalTrucks.enqueue(truckPtr,truckPtr->getTruckPriority());
        if(NightShift) NightShiftTrucks.enqueue(truckPtr,truckPtr->getTruckPriority());
    }
    int E;
    myfile>>E;
    char EventType, CargoType;
    Time EventTime;
    int CargoID, CargoDistance, CargoLoadingTime, ExtraMoney, CargoCost;
    for(int i = 0; i < E;i++){
        myfile >> EventType;
        if(EventType == 'R'){ // 'R' for ready/preparation event
            myfile >> CargoType >> EventTime >> CargoID >> CargoDistance >> CargoLoadingTime >> CargoCost;
            eventPtr = new PreparationEvent(EventTime,CargoID,CargoType,CargoDistance,CargoLoadingTime,CargoCost,this);
            EventsList.enqueue(eventPtr);
        }else if(EventType == 'X'){ // 'X' for cancellation event
            myfile >> EventTime >> CargoID;
            eventPtr = new CancelEvent(EventTime, CargoID, this);
            EventsList.enqueue(eventPtr);
        }else if(EventType == 'P'){ // 'P' for promotion event
            myfile >> EventTime >> CargoID >> ExtraMoney;
            eventPtr=new PromotionEvent(EventTime, CargoID, ExtraMoney, this);
            EventsList.enqueue(eventPtr);
        }
    }
    return true;
}
// PHASE 2 REQUIREMENTS

bool Company::WriteOutputFile(){
    ofstream myfile;
    myfile.open("OutputFile.txt");
    myfile<<"CDT     ID     PT     WT     TID"<<endl;
    int DeliveredCargosListSize=this->getDeliveredCargosList()->getCount();
    for(int i=0;i<DeliveredCargosListSize;i++){
        this->getDeliveredCargosList()->dequeue(cargoPtr);
        this->getDeliveredCargosList()->enqueue(cargoPtr);
        Time cPT=cargoPtr->getCargoPreparationTime();
        myfile<<cargoPtr->getCDT().getDay()<<":"<<cargoPtr->getCDT().getHour()<<"     "<<cargoPtr->getCargoID()<<"     "<<cPT.getDay()<<":"<<cPT.getHour()<<"     "<<cargoPtr->getWT().getDay()<<":"<<cargoPtr->getWT().getHour()<<"     "<<cargoPtr->getCargoTID()<<endl;
    }
    myfile<<endl<<endl<<"....................................................."<<endl;
    myfile<<"           Important Statistics        "<<endl;
    myfile<<"Cargos: "<<cargoPtr->getTotalCargosCount()<<"     [N: "<<cargoPtr->getNormalCargosCount()<<", S: "<<cargoPtr->getSpecialCargosCount()<<", V: "<<cargoPtr->getVIPCargosCount()<<"]"<<endl;
    Time CargoAvgWait(cargoPtr->getCargoAverageWaitTime());
    myfile<<"Cargo Avg Wait = "<<CargoAvgWait<<endl;
    myfile<<"Auto-Promoted Cargos: "<<cargoPtr->getPercentageofAutoPromotedCargos()<<"%"<<endl;
    myfile<<"Trucks: "<<truckPtr->getTotalTrucksCount()<<"     [N: "<<truckPtr->getNormalTrucksCount()<<", S: "<<truckPtr->getSpecialTrucksCount()<<", V: "<<truckPtr->getVIPTrucksCount()<<"]"<<endl;  
    myfile<<"Avg Active Time = "<<(((float)truckPtr->getTotalTrucksActiveTime().TimetoHrs())/(float)this->getCompanyClock().TimetoHrs())*100<<"%"<<endl;
    myfile.close();
    return true;
}


//NormalCargos
void Company::AssignTrucks(PriorityQueue<Truck*>*q, LinkedList<Cargo*>*ListPtr){
    if(!q->isEmpty()){
        truckPtr=q->peek();
        while(truckPtr && ListPtr->getCount()>=truckPtr->getTruckCapacity()){
            Time movingTime=Clock;
            q->dequeue(truckPtr);       
            for(int i=0;i<truckPtr->getTruckCapacity();i++){
                ListPtr->RemoveFirst(cargoPtr);
                LoadingCargos.enqueue(cargoPtr,1);//1 since moving Time in not known yet
                truckPtr->LoadCargo(cargoPtr);
                movingTime=movingTime+cargoPtr->getLoadTime();
            }
            truckPtr->setTruckMovingTime(movingTime);
            truckPtr->setTruckLoadingTime(movingTime-Clock);
            int TruckPriority = -1*movingTime.TimetoHrs();
            LoadingTrucks.enqueue(truckPtr,TruckPriority);
            truckPtr->StampCargos();//Could be done here; difference to be examined later
            truckPtr->ArrangeTruckCargoList();
            truckPtr=q->peek();
        }
    }
}
//SpecialCargos
void Company::AssignTrucks(PriorityQueue<Truck*>*q, Queue<Cargo*>*ListPtr){
    if(!q->isEmpty()){
        truckPtr=q->peek();
        while(truckPtr && ListPtr->getCount()>=truckPtr->getTruckCapacity()){
            Time movingTime=Clock;
            q->dequeue(truckPtr);
            for(int i=0;i<truckPtr->getTruckCapacity();i++){
                ListPtr->dequeue(cargoPtr);
                LoadingCargos.enqueue(cargoPtr,1);//Priority according to MT, not known at this point
                truckPtr->LoadCargo(cargoPtr);
                movingTime=movingTime+cargoPtr->getLoadTime();
            }
            truckPtr->setTruckMovingTime(movingTime);
            truckPtr->setTruckLoadingTime(movingTime-Clock);
            int TruckPriority = -1*movingTime.TimetoHrs();
            LoadingTrucks.enqueue(truckPtr,TruckPriority);
            truckPtr->StampCargos();//Could be done here; difference to be examined later
            truckPtr->ArrangeTruckCargoList();
            truckPtr=q->peek();
        }
    }
}

void Company::UpdateLoadingCargosList(){// rearranges the list by dequeueing list elements and reenqueuing according to MT priority
    if(LoadingCargos.isEmpty()) return;
    int LoadingCargosListSize=LoadingCargos.getCount();
    for(int i=0;i<LoadingCargosListSize;i++){
        LoadingCargos.dequeue(cargoPtr);
        LoadingCargos.enqueue(cargoPtr,-1*cargoPtr->getMT().TimetoHrs());//Now MT is known
    }
}

void Company::AssignVIPCargos(){
    if(WaitingVIP.isEmpty() || (VIPTrucks.isEmpty() && NormalTrucks.isEmpty() && SpecialTrucks.isEmpty())) return;
    AssignTrucks(this->getVIPTrucksList(), this->getWaitingVIPList());
    AssignTrucks(this->getNormalTrucksList(), this->getWaitingVIPList());
    AssignTrucks(this->getSpecialTrucksList(), this->getWaitingVIPList());
}
void Company::AssignNormalCargos(){
    if(WaitingNormal.isEmpty() || (VIPTrucks.isEmpty() && NormalTrucks.isEmpty())) return;
    AssignTrucks(this->getNormalTrucksList(), this->getWaitingNormalList());
    AssignTrucks(this->getVIPTrucksList(), this->getWaitingNormalList());
}
void Company::AssignSpecialCargos(){
    if(WaitingSpecial.isEmpty() || SpecialTrucks.isEmpty()) return;
    AssignTrucks(this->getSpecialTrucksList(), this->getWaitingSpecialList());
}
void Company::MoveTrucks(){//At a truck's moving time, this function moves a truck from LoadingTrucks list to MovingTrucks list
    if(LoadingTrucks.isEmpty()) return;
    truckPtr=LoadingTrucks.peek();
    while(truckPtr && truckPtr->getTruckMovingTime()==Clock){
        LoadingTrucks.dequeue(truckPtr);
        truckPtr->setDI();
        MovingTrucks.enqueue(truckPtr,-1*truckPtr->getDI().TimetoHrs());//Priortiy according to DI(Delivery interval)
//        truckPtr->StampCargos();//Not necessarily here; Other place is in AssignTrucks function(s)
        truckPtr=LoadingTrucks.peek();
    }
}
void Company::MoveCargos(){//At a cargo's moving time, this function moves a cargo from LoadingCargos list to MovingCargos list
    if(LoadingCargos.isEmpty()) return;
    cargoPtr=LoadingCargos.peek();
    while(cargoPtr && cargoPtr->getMT()==Clock){
        LoadingCargos.dequeue(cargoPtr);
        MovingCargos.enqueue(cargoPtr,-1*cargoPtr->getCDT().TimetoHrs());
        cargoPtr=LoadingCargos.peek();
    }
}
void Company::DeliverCargos(){
    if(MovingCargos.isEmpty()) return;
    cargoPtr=MovingCargos.peek();
    while(cargoPtr && cargoPtr->getCDT()==Clock){
        MovingCargos.dequeue(cargoPtr);
        DeliveredCargos.enqueue(cargoPtr);
        //We should also remove the cargo from Truck's Cargo List
        cargoPtr->getCargoTruck()->IncrementCargosDeliveredbyTruck();
        cargoPtr->getCargoTruck()->UnloadCargo(cargoPtr);

        //
        //collecting statistics
        Time cWT=cargoPtr->getWT();
        cargoPtr->IncrementCargototalWaitTime(cWT);
//        if(cargoPtr->isAutoPromoted()) {
//            cargoPtr->IncrementAutoPromotedCargosCount();
//        }
        //
        cargoPtr=MovingCargos.peek();
    }
}

void Company::ContinueTruckJourney(){
    if(MovingTrucks.isEmpty()) return;
    truckPtr=MovingTrucks.peek();
    while(truckPtr && truckPtr->getDI()==Clock){/*truckPtr->getCargoList()->isEmpty() previously; to be remove later when sure of =>*/
        MovingTrucks.dequeue(truckPtr);
        truckPtr->setTruckDeliveryTime();
        truckPtr->IncrementTruckActiveTime();
        truckPtr->IncremenetNumberofDeliveries();
        truckPtr->resetCargoRelatedTruckInfo();
        if(truckPtr->NeedsCheckup()){
            truckPtr->setTruckCheckupTime();
            IncheckupTrucks.enqueue(truckPtr, -1*truckPtr->getTruckCheckupTime().TimetoHrs());
        }
        else{
            if(truckPtr->getTruckType()=='V') VIPTrucks.enqueue(truckPtr,truckPtr->getTruckPriority());
            else if(truckPtr->getTruckType()=='N') NormalTrucks.enqueue(truckPtr,truckPtr->getTruckPriority());
            else if(truckPtr->getTruckType()=='S') SpecialTrucks.enqueue(truckPtr,truckPtr->getTruckPriority());
        }
        truckPtr=MovingTrucks.peek();
    }
    
}  
void Company::UpdateIncheckupList(){
    if(IncheckupTrucks.isEmpty()) return;
    truckPtr=IncheckupTrucks.peek();
    while(truckPtr && truckPtr->getTruckCheckupTime()==Clock){
        IncheckupTrucks.dequeue(truckPtr);
        if(truckPtr->getTruckType()=='V') VIPTrucks.enqueue(truckPtr,truckPtr->getTruckPriority());
        else if(truckPtr->getTruckType()=='N') NormalTrucks.enqueue(truckPtr,truckPtr->getTruckPriority());
        else if(truckPtr->getTruckType()=='S') SpecialTrucks.enqueue(truckPtr,truckPtr->getTruckPriority());
        truckPtr=IncheckupTrucks.peek();
    }
}

bool Company::LoadCargoImmediately(PriorityQueue<Truck*>*q){
        if(q->isEmpty())    
            return false;        
        Time movingTime=Clock+cargoPtr->getLoadTime();
        q->dequeue(truckPtr);
        truckPtr->setTruckMovingTime(movingTime);
        LoadingTrucks.enqueue(truckPtr,-1*movingTime.TimetoHrs());
        LoadingCargos.enqueue(cargoPtr,-1*movingTime.TimetoHrs());
        truckPtr->LoadCargo(cargoPtr);
        truckPtr->setTruckLoadingTime(movingTime-Clock);
        truckPtr->StampCargos();
        return true;
}
 
 
void Company::ApplyMaximumWaitRule(){
    Time cargoWaitingTime;//Time the cargo has been waiting to be assigned
    if(!WaitingSpecial.isEmpty()){
        cargoPtr=WaitingSpecial.peek();
        Time cPT=cargoPtr->getCargoPreparationTime();
        cargoWaitingTime=Clock-cPT;
        while(cargoPtr&&cargoWaitingTime.TimetoHrs()>=MaxW){
            if(LoadCargoImmediately(this->getSpecialTrucksList())){
                WaitingSpecial.dequeue(cargoPtr);
            }
            else break;
            cargoPtr=WaitingSpecial.peek();
            if(cargoPtr){
                cPT=cargoPtr->getCargoPreparationTime();
                cargoWaitingTime=Clock-cPT;
            }            
        }
    }
    if(!WaitingNormal.isEmpty()){
        cargoPtr=WaitingNormal.getEntry(1);
        Time cPT=cargoPtr->getCargoPreparationTime();//To avoid overloading the - operator for Time objects(it is overloaded for &Time objects)
        cargoWaitingTime=Clock-cPT;
        while(cargoPtr&&cargoWaitingTime.TimetoHrs()>=MaxW){
            if(LoadCargoImmediately(this->getNormalTrucksList()) || LoadCargoImmediately(this->getVIPTrucksList())){
                WaitingNormal.RemoveFirst(cargoPtr);
            }
            else break;
            cargoPtr=WaitingNormal.getEntry(1);
            if(cargoPtr){
                cPT=cargoPtr->getCargoPreparationTime();
                cargoWaitingTime=Clock-cPT;
            }
        }
    }
}

void Company::ApplyAutoPromotion(){
    if(WaitingNormal.isEmpty()) return;
    for(int i=1;i<=WaitingNormal.getCount();i++){
        cargoPtr=WaitingNormal.getEntry(i);
        Time pt=cargoPtr->getCargoPreparationTime();
        Time WaitingTime=getCompanyClock()-pt;
        bool NeedsAutoPromotion=(WaitingTime.TimetoHrs()>=AutoP);
        if(NeedsAutoPromotion){
            cargoPtr->setAutoPromoted();
            WaitingNormal.Remove(cargoPtr);
            cargoPtr->UpdatetoVIP();
            WaitingVIP.enqueue(cargoPtr,cargoPtr->getVIPPriority());
            cargoPtr->IncrementAutoPromotedCargosCount();
        }
    }
}


Cargo* Company::getCargoPtr(){return cargoPtr;}
            
bool Company::ExecuteEvents(){
    if(EventsList.isEmpty())return false;
    eventPtr=EventsList.peek();
        while(eventPtr->getEventTime()==Clock){
            eventPtr->Execute();
            EventsList.dequeue(eventPtr);// EventPtr is used to temporarily store the dequeued event pointer
            if(EventsList.isEmpty()) break;
            eventPtr=EventsList.peek();
        }
    return true;
}

void Company::Phase_2_TestFunction(){
    this->ReadInputFile();
    this->getUIPtr()->SelectMode();
}


void Company::RunCompany(){ 
    this->ExecuteEvents();
//    this->ApplyMaximumWaitRule();
//    this->ApplyAutoPromotion();
    if(this->checkWH()){
        this->ApplyMaximumWaitRule();
        this->ApplyAutoPromotion();
        this->AssignVIPCargos();
        this->AssignSpecialCargos();
        this->AssignNormalCargos();
    }
    else{
        //AssignNightShifts();
    }
    this->UpdateLoadingCargosList();
    this->MoveTrucks();
    this->MoveCargos();
    this->DeliverCargos();
    this->ContinueTruckJourney();
    this->UpdateIncheckupList();

}

// List Getters; They return pointers to the list not the whole list
LinkedList<Cargo*>* Company::getWaitingNormalList(){return &WaitingNormal;}
Queue<Cargo*>* Company::getWaitingSpecialList(){return &WaitingSpecial;}
PriorityQueue<Cargo*>* Company::getWaitingVIPList(){return &WaitingVIP;}
PriorityQueue<Truck*>* Company::getVIPTrucksList(){return &VIPTrucks;}
PriorityQueue<Truck*>* Company::getSpecialTrucksList(){return &SpecialTrucks;}
PriorityQueue<Truck*>* Company::getNormalTrucksList(){return &NormalTrucks;}
Queue<Event*>* Company::getEventsList(){return &EventsList;}
PriorityQueue<Truck*>* Company::getLoadingTrucksList(){return &LoadingTrucks;}
PriorityQueue<Truck*>* Company::getMovingTrucksList(){return &MovingTrucks;}
PriorityQueue<Truck*>* Company::getIncheckupTrucksList(){return &IncheckupTrucks;}
PriorityQueue<Cargo*>* Company::getMovingCargosList(){return &MovingCargos;}
PriorityQueue<Cargo*>* Company::getLoadingCargosList(){return &LoadingCargos;}
Queue<Cargo*>* Company::getDeliveredCargosList(){return &DeliveredCargos;}
Queue<Truck*>* Company::getIncheckupVIPTrucksList(){return &IncheckupVIPTrucks;}
Queue<Truck*>* Company::getIncheckupSpecialTrucksList(){return &IncheckupSpecialTrucks;}
Queue<Truck*>* Company::getIncheckupNormalTrucksList(){return &IncheckupNormalTrucks;}

// DATA MEMBER SETTERS : Some of them are only needed for testing and may be removed later
void Company::setMaxW(int maxw){MaxW=maxw;}
void Company::setAutoP(int autop){AutoP=autop;}    
UI* Company::getUIPtr(){return UIPtr;}
Time Company::getCompanyClock()const{return Clock;}    
void Company::IncrementCompanyClock(){Clock=Clock+1;}
void Company::setCompanyClock(Time &t){Clock=t;}


void Company::AssignTrucks(PriorityQueue<Truck*>*q, PriorityQueue<Cargo*>*ListPtr){
    if(!q->isEmpty()){
        truckPtr=q->peek();
        while(truckPtr && ListPtr->getCount()>=truckPtr->getTruckCapacity()){
            Time movingTime=Clock;
            q->dequeue(truckPtr);
            for(int i=0;i<truckPtr->getTruckCapacity();i++){
                ListPtr->dequeue(*&cargoPtr);
                LoadingCargos.enqueue(cargoPtr,1);
                truckPtr->LoadCargo(cargoPtr);
                movingTime=movingTime+cargoPtr->getLoadTime();
            }
            truckPtr->setTruckMovingTime(movingTime);// sets time at which trucks starts to move
            truckPtr->setTruckLoadingTime(movingTime-Clock);//sets time trucks takes in loading cargos
            int TruckPriority = -1*movingTime.TimetoHrs();
            LoadingTrucks.enqueue(truckPtr,TruckPriority);
            truckPtr->StampCargos();//Could be done here; difference to be examined later
            truckPtr->ArrangeTruckCargoList();
            truckPtr=q->peek();
        }
    }
}
