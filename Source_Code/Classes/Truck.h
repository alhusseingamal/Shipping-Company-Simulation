#ifndef TRUCK_H
#define TRUCK_H
#include "PriorityQueue.h"
#include "Queue.h"
#include "Cargo.h"
#include "Time.h"

using namespace std;
class Truck
{
    char TruckType; // V for VIP, S for special, N for normal
    // As per the project document, the type won't be read explicitly from input file, we only have the number of trucks of each type
    // we can loop on that number assigning TruckType to which Truck we are reading
    int TruckCapacity; // no. of cargos a truck can hold, read from input files, non-const
    const int MaintenanceTime; // the time a trucks takes in maintenance
    const int j; //num Of Deliveries Before Maintenance
    int Speed; //in m/s , non-const for bonus part
    const int TruckID;
    int NumberofDeliveries; // consider renaming it to total...
    Time TruckCheckupTime;
    Time MovingTime;
    int furthestDDLoadedCargo=0, CargosUnloadTimeSum=0;
    int TimeToComeBack;
    Time DI; //Delivery Interval
    Time TruckActiveTime;
    Time TruckLoadingTime;//Needed in calculating truck-related stats
    Time TruckDeliveryTime;
    PriorityQueue<Cargo*> CargoList;// a list of the cargos in a truck, priority according to CDT(cargo delivery time)
    
    int CargosDeliveredbyTruck;
    bool NightShiftAvailability;
    int TruckPriority;
    static int IDGenerator; // Used to generate IDs for Trucks
    static int TotalTrucksCount;
    static int VIPTrucksCount;
    static int SpecialTrucksCount;
    static int NormalTrucksCount;
    static Time TotalTruckActiveTime;
public:
    Truck(char TT, int TC, int MT, int j, int S, bool NSA);
    
    //Getters & Setters
    
    int getTruckPriority() const;
    void setTruckPriority();
    
    PriorityQueue<Cargo*>* getCargoList();
    char getTruckType() const;
    int getTruckMaintenanceTime() const;
    int getTruckCapacity() const;
    int getTruckSpeed() const;
    int getTruckID() const;
    int getNumberofDeliveries() const;
    Time getDI() const;
    void setDI();
    Time getTruckMovingTime() const;
    void IncremenetNumberofDeliveries();
    bool NeedsCheckup(); // Checks if truck needs checkup
    void LoadCargo(Cargo*c); // Loads Cargo on the truck
    void UnloadCargo(Cargo*c); // Unloads Cargo from the truck
    void StampCargos(); // Assigns Moving Time and CDT for loaded Cargos
    void ArrangeTruckCargoList();//Arranges cargos in Cargo list according to their CDT
    void resetCargoRelatedTruckInfo();
    void IncrementCargosDeliveredbyTruck();
    int getCargosDeliveredbyTruck() const;
    Time getTruckActiveTime()const;
    void IncrementTruckActiveTime();
    Time getTruckCheckupTime()const;
    void setTruckCheckupTime();
    Time getTotalTrucksActiveTime()const;
    int getTotalTrucksCount() const;
    int getVIPTrucksCount() const;
    int getSpecialTrucksCount() const;
    int getNormalTrucksCount() const;
    void setTruckLoadingTime(Time t);
    Time getTruckLoadingTime()const;
    void setTruckDeliveryTime();
    Time getTruckDeliveryTime()const;
    

    //Setters
    void setTruckMovingTime(Time mt);
    friend ostream &operator<<(ostream &output, Truck &truck);
    ~Truck();
};

#endif // TRUCK_H
