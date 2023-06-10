#include "Event.h"

Event::Event(Time ET, int ID, Company* cPtr): CompanyPtr{cPtr}, EventTime{ET}, CargoId{ID}
{
}

Event::~Event()
{
}
Time Event::getEventTime()const{
    return EventTime;
}

int Event::getEventId()const{return CargoId;}//the name getEventId might be misleading as it actually returns cargoId
