#ifndef COMPANY_H
#define COMPANY_H

#include <fstream>
#include "Queue.h"
#include "LinkedList.h"
#include "PriorityQueue.h"
#include "Time.h"
#include "UI.h"
#include "Cargo.h"
#include "Truck.h"
#include "Event.h"
#include "PreparationEvent.h"
#include "CancelEvent.h"
#include "PromotionEvent.h"


using namespace std;

class Event;
class Company
{
    Event*eventPtr = nullptr;
    Cargo*cargoPtr = nullptr;
    Truck*truckPtr = nullptr;
    UI *UIPtr=new UI(this);
    int MaxW = 0, AutoP = 0;
    Time Clock;
    Queue <Event*> EventsList;
    int TotalEventsTime = 0;
    PriorityQueue <Truck*> VIPTrucks;
    PriorityQueue <Truck*> SpecialTrucks;
    PriorityQueue <Truck*> NormalTrucks;
    PriorityQueue <Truck*> NightShiftTrucks;
    //Waiting Cargos Lists
    PriorityQueue <Cargo*> WaitingVIP;
    LinkedList <Cargo*> WaitingNormal;
    Queue <Cargo*> WaitingSpecial;
    PriorityQueue<Cargo*> LoadingCargos;//Priority according to Delivery time
    PriorityQueue<Cargo*> MovingCargos;//Priority according to CDT
    Queue<Cargo*> DeliveredCargos;//Previously PriQueue;Priority according to Delivery time
    PriorityQueue<Truck*> LoadingTrucks;// A list of cargos being loaded
    PriorityQueue<Truck*> MovingTrucks;
    PriorityQueue<Truck*> IncheckupTrucks;
    Queue<Truck*> IncheckupVIPTrucks;
    Queue<Truck*> IncheckupNormalTrucks;
    Queue<Truck*> IncheckupSpecialTrucks;
public:
    Company();
    ~Company();
    void RunCompany();
    bool ReadInputFile();
    bool WriteOutputFile();
    bool ExecuteEvents();
    bool AddCargo(Cargo*c); //adds one cargo to the suitable cargo list
    void ContinueTruckJourney();
    void SimulatorFunctionMoveCargos();
    
    //Getters
    Cargo*getCargoPtr();
    LinkedList<Cargo*>* getWaitingNormalList(); // returns a pointer to the list of normal cargos waiting
    Queue<Cargo*>* getWaitingSpecialList();
    PriorityQueue<Cargo*>* getWaitingVIPList();
    PriorityQueue<Truck*>* getVIPTrucksList();
    PriorityQueue<Truck*>* getSpecialTrucksList();
    PriorityQueue<Truck*>* getNormalTrucksList();
    Queue<Event*>* getEventsList();
    PriorityQueue<Truck*>* getLoadingTrucksList();
    PriorityQueue<Truck*>* getMovingTrucksList();
    PriorityQueue<Cargo*>* getMovingCargosList();
    PriorityQueue<Cargo*>* getLoadingCargosList();
    PriorityQueue<Truck*>* getIncheckupTrucksList();
    Queue<Cargo*>* getDeliveredCargosList();
    Queue<Truck*>*getIncheckupVIPTrucksList();
    Queue<Truck*>*getIncheckupSpecialTrucksList();
    Queue<Truck*>*getIncheckupNormalTrucksList();
    
    //Setters
    void setMaxW(int maxw);
    void setAutoP(int autop);
    UI* getUIPtr();
    Time getCompanyClock() const;
    void IncrementCompanyClock();
    void setCompanyClock(Time &t); // For testing only
    void Phase_2_TestFunction();
    void SimpleSimulatorFunction();
    Cargo* getCargo(int Id,LinkedList<Cargo*>*q);
    void RemoveNormalCargo(Cargo *c, LinkedList<Cargo*>*q);
    bool checkWH(); // check working hours
    //PHASE 2
    void AssignTrucks(PriorityQueue<Truck*>*q, PriorityQueue<Cargo*>*ListPtr);    
    void AssignTrucks(PriorityQueue<Truck*>*q, LinkedList<Cargo*>*ListPtr);
    void AssignTrucks(PriorityQueue<Truck*>*q, Queue<Cargo*>*ListPtr);
    void AssignVIPCargos();
    void AssignSpecialCargos();
    void AssignNormalCargos();
    void ApplyMaximumWaitRule();
    bool LoadCargoImmediately(PriorityQueue<Truck*>*q);
    void ApplyAutoPromotion();
    void MoveTrucks();
    void DeliverCargos();
    void MoveCargos();
    void UpdateLoadingCargosList();
    void UpdateIncheckupList();
    int getTotalEventsNumber(); // used in step-by-step and silent mode
    void HandleFailedDelivery();
};
#endif // COMPANY_H
