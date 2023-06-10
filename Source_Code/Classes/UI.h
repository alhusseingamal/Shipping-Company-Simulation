#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <string.h>
#include "windows.h"
class Company;
using namespace std;
class UI
{
    Company* CompanyPtr=nullptr;
    string InputFileName;
    string OutputFileName;
    int Mode = 0;
public:
    UI(Company*cPtr);
    ~UI();
    void OutputWindow();
    void RunInteractiveMode();
    void RunStepbyStepMode();
    void RunSilentMode();
    void SelectMode();
    int getMode();
    string readInputFileName();
    string readOutputFileName();
    void printDeliveredCargosList();
};

#endif // UI_H


