#ifndef PREPARATIONEVENT_H
#define PREPARATIONEVENT_H
#include <iostream>
using namespace std;
#include "Event.h"
#include "Company.h"

class PreparationEvent : public Event{
    char CargoType;
    int CargoDistance;
    int CargoLoadingTime;
    int CargoCost;
public:
    PreparationEvent(Time ET, int ID, char CT, int DIST, int LT, int cost,Company* cPtr);
    ~PreparationEvent();
    bool Execute();
    void PrintEvent();
};

#endif // PREPARATIONEVENT_H