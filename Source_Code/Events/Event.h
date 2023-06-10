#ifndef EVENT_H
#define EVENT_H
#include "Time.h"
#include "Cargo.h"

class Company;

class Event
{
protected:
    Company *CompanyPtr=nullptr;
    Time EventTime;
    int CargoId;
public:
    void setCompanyPtr(Company* cPtr){CompanyPtr=cPtr;}
    //Event();
    Event(Time ET, int ID, Company* cPtr);
    ~Event();
    Time getEventTime()const;
    int getEventId()const;
    virtual bool Execute()=0;
    virtual void PrintEvent()=0;
};

#endif // EVENT_H