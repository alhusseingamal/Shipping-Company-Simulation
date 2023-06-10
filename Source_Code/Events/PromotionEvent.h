#ifndef PROMOTIONEVENT_H
#define PROMOTIONEVENT_H

#include "Event.h"
#include "Company.h"
class PromotionEvent : public Event{
    int ExtraMoney;
public:
    PromotionEvent(Time ET, int ID, int EM, Company*cPtr);
    ~PromotionEvent();
    bool Execute();
    void PrintEvent();

};

#endif // PROMOTIONEVENT_H
