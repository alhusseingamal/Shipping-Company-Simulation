#include "Time.h"

Time::Time() :Day{0}, Hour{0}// This is initialized that way since, for now, we only needed it in Company class
{
}
Time::Time(int d,int h):Day{d}, Hour{h} // if want our company time to pickoff from a specific start point
{
}

Time::~Time()
{
}

void Time::IncrementTime(){
    if(Hour==23){
        Hour=0;
        Day++;
        return;
    }
    Hour++;
}

// In many cases, we are interested in comparing time variables, so instead of overloading operators to compare time
// we can just change eacht time to an equivalent integer (hrs specifically), and do the comparison
int Time::TimetoHrs(){
    return (this->getDay() * 24) + this->getHour();
}
Time Time::HrstoTime(int t){
    Time temp(t / 24,t % 24);
    return temp;
}
Time Time::getTime(){
    return *this;
}
bool Time::checkWH(){//checks if time is during working hours; from 5 am to 11 pm
    if(Hour >= 5 && Hour <= 23) return true;
    else return false;
}
void Time::displayTime(){
    cout << Day << ":" << Hour;
}
//Getters

int Time::getDay()const{return Day;}

int Time::getHour()const{return Hour;}

Time Time::operator-(Time&t){//No validation provided, that minuend time is greater than the subtrahend time

    Time temp;
    
    temp.Day = this->getDay() - t.getDay();
    
    if(t.getHour() > this->getHour()){
        
        temp.Day--;
        
        temp.Hour = 24 - (t.getHour() - this->getHour());
    
    }else{
    
        temp.Hour = this->getHour() - t.getHour();

    }
    
    return temp;
}

Time Time::operator+(Time&t){
    
    Time temp;
    
    temp.Day = this->getDay() + t.getDay();
    
    if(t.getHour() + this->getHour() > 23){
    
        temp.Day++;

        temp.Hour = ((t.getHour() + this->getHour()) % 24);
    
    }else{
    
        temp.Hour = this->getHour() + t.getHour();
    }
    
    return temp;
}

Time Time::operator+(int t){
    
    Time temp;
    
    temp.Day=this->getDay();
    
    temp.Hour=this->getHour();
    
    if(t + temp.getHour() > 23){
    
        temp.Day += (t + temp.getHour()) / 24;
        
        temp.Hour = (t + temp.getHour()) % 24;
    
    }else{
        temp.Hour += t;
    }
    
    if(temp.getHour() == 24){
        
        temp.Day++;
        
        temp.Hour=0;
    }
    
    return temp;
}

bool Time::operator==(Time&t){
    if(t.getDay() == this->getDay() && t.getHour() == this->getHour()) return true;
    
    return false;
}

istream &operator>>(istream &input, Time &t){
    input >> t.Day;
    
    char tmp; input >> tmp;// inputs the ':' character, doesn't have an actual use 
    
    input >> t.Hour;
    
    return input;
}

ostream &operator<<(ostream &output, Time &t){
    
    output << t.getDay() << ":" << t.getHour();
    
    return output;
}