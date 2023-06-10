#ifndef CANCELEVENT_H
#define CANCELEVENT_H
#include "Event.h"
#include "Company.h"
class CancelEvent : public Event {
public:
    CancelEvent(Time ET, int ID, Company *cPtr);
    ~CancelEvent();
    bool Execute();
    void PrintEvent();
};

#endif // CANCELEVENT_H
