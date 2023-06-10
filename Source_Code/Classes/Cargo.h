#ifndef CARGO_H
#define CARGO_H
#include "Time.h"
#include <iostream>
#include <cmath>
using namespace std;
class Truck;
class Cargo
{
    Time PrepTime;
    const int LoadTime;//Loading or unloading time
    char CargoType;// V for VIP, S for special, N for normal cargos, not const for promotion event
    const int DeliveryDistance;
    const int Cost;
    const int CargoID;// Is ID a member of Cargo class?
    int VIPPriority;//Available only for VIP Cargos
    Time MT;//Moving Time
    Time WT;//Waiting Time
    Time CDT;// Cargo Delivery Time
    Truck* CargoTruck;
    int CargoTID;
    Time static CargototalWaitTime;//Average Wait Time for successfully delivered cargos
    
    int static VIPCargosCount;//Count for VIP cargos
    int static SpecialCargosCount;//Count for Special cargos
    int static NormalCargosCount;//Count for Normal cargos
    int static TotalCargosCount;//Count for all the cargos
    int static AutoPromotedCargosCount;
    bool AutoPromoted;
public:
    Cargo(Time PT, int LT, char CT, int DD, int cost, int id);
    ~Cargo();
    void setCargoTID(Truck *t);
    int getCargoTID ()const;
    void UpdatetoVIP();
    void setCargoTruck(Truck* t);
    Truck* getCargoTruck();
    Time getCargoPreparationTime()const;
    char getCargoType() const;
    int getCargoID() const;
    int getLoadTime() const;
    int getDeliveryDistance() const;
    int getCargoCost() const;
    void setVIPPriority();
    int getVIPPriority() const;
    void AssignMT(Truck*t); // Should be called before calculateCDT and calculateWT
    Time getMT() const;
    void calculateCDT(Truck*t);
    Time getCDT() const;
    void calculateWT();
    Time getWT() const;
    void setCargoMT(Time t);
    void DecrementTotalCargosCount();
    void DecrementNormalCargosCount();
    void IncrementVIPCargosCount();
    int getSpecialCargosCount()const;
    int getNormalCargosCount()const;
    int getVIPCargosCount()const;
    int getTotalCargosCount()const;
    void IncrementCargototalWaitTime(Time &t);
    Time getCargototalWaitTime() const;
    Time getCargoAverageWaitTime() const;
    void IncrementAutoPromotedCargosCount();
    int getAutoPromotedCargosCount() const;
    bool isAutoPromoted();
    void setAutoPromoted();
    float getPercentageofAutoPromotedCargos();
    friend ostream &operator<<(ostream &output, Cargo &cargo);
};
#endif // CARGO_H