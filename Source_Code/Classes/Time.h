#ifndef TIME_H
#define TIME_H
#include <iostream>
#include <cmath>
using namespace std;

class Time // 
{
    int Day;
    
    int Hour;
    
public:
    Time();
    
    Time(int d,int h); // has no use currently
    
    ~Time();
    
    void IncrementTime();
    
    Time getTime();
    
    bool checkWH();
    
    void displayTime();
    
    int TimetoHrs();
    
    Time HrstoTime(int t);
    
    int getDay()const;
    
    int getHour()const;
    
    Time operator-(Time&t);
    
    Time operator+(Time&t);
    
    Time operator+(int t);
    
    bool operator==(Time&t);
    
    friend istream &operator>>(istream &input, Time &t);
    
    friend ostream &operator<<(ostream &output, Time &t);
};

#endif // TIME_H
