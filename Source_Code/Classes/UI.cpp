#include "UI.h"
#include "Company.h"
#include "windows.h"
UI::UI(Company* cPtr) :CompanyPtr{ cPtr } {}
UI::~UI() {}
int UI::getMode()
{
    return Mode;
}
void UI::SelectMode() {
    cout << "Select Program Mode: (1 for Interactive mode, 2 for Step-by-step mode, 3 for Silent mode): ";
    cin >> Mode;
    while (Mode != 1 && Mode != 2 && Mode != 3) {
        cout << "Invalid Input! Re-enter Program Mode: (1 for ineractive mode, 2 for Step-by-step mode, 3 for Silent mode): ";
        cin >> Mode;
    }
    if (Mode == 1) {
        cout << "INTERACTIVE MODE" << endl;
        this->RunInteractiveMode();
    }
    else if (Mode == 2) {
        cout << "STEP-BY-STEP MODE" << endl;
        this->RunStepbyStepMode();
    }
    else if (Mode == 3) {
        cout << "SILENT MODE" << endl;
        this->RunSilentMode();
    }
}
void UI::RunInteractiveMode() {
    string InputString = "";
    cout << "Press Enter to Start." << endl;
    getline(std::cin, InputString);
    while (InputString.length() == 0) {
        CompanyPtr->RunCompany();
        this->OutputWindow();
        CompanyPtr->IncrementCompanyClock();
        cout << "Press ENTER to proceed with next time." << std::endl;
        getline(std::cin, InputString);
    }
    CompanyPtr->WriteOutputFile();
    cout << "Simulation ends, Output file is created" << endl;
}

void UI::RunStepbyStepMode() {
    string InputString = "";
    cout << "Press Enter to Start." << endl;
    getline(std::cin, InputString);
    int count = 0;
    while (count < CompanyPtr->getTotalEventsNumber() || (CompanyPtr->getDeliveredCargosList()->getCount() != CompanyPtr->getCargoPtr()->getTotalCargosCount()) || !CompanyPtr->getLoadingCargosList()->isEmpty() || !CompanyPtr->getMovingTrucksList()->isEmpty() || !CompanyPtr->getIncheckupTrucksList()->isEmpty())
    {
        CompanyPtr->RunCompany();
        this->OutputWindow();
        CompanyPtr->IncrementCompanyClock();
        count++;
        Sleep(1000);
    }
    cout << "End of step-by-step simulation!" << endl;
    CompanyPtr->WriteOutputFile();
    cout << "Simulation ends, Output file is created" << endl;
}
void UI::RunSilentMode() {
    cout << "Simulation Starts..." << endl;
    int count = 0;
    int time = CompanyPtr->getCompanyClock().TimetoHrs();
    while (count < 100)
    {
        CompanyPtr->RunCompany();
        CompanyPtr->IncrementCompanyClock();
        count++;
        int time = CompanyPtr->getCompanyClock().TimetoHrs();
    }
    CompanyPtr->WriteOutputFile();
    cout << "Simulation ends, Output file is created" << endl;
}

void UI::printDeliveredCargosList() {
    Cargo* cargoPtr;
    int DeliveredCargosListSize = CompanyPtr->getDeliveredCargosList()->getCount();
    for (int i = 0; i < DeliveredCargosListSize; i++) {
        CompanyPtr->getDeliveredCargosList()->dequeue(cargoPtr);
        if (cargoPtr->getCargoType() == 'V') cout << "{" << *cargoPtr << "} ";
        else if (cargoPtr->getCargoType() == 'N') cout << "[" << *cargoPtr << "] ";
        else if (cargoPtr->getCargoType() == 'S') cout << "(" << *cargoPtr << ") ";
        CompanyPtr->getDeliveredCargosList()->enqueue(cargoPtr);
    }
}

void UI::OutputWindow() {
    cout << "Current Time (Day:Hour):"; CompanyPtr->getCompanyClock().displayTime();
    cout << endl << endl;

    int NTC = CompanyPtr->getNormalTrucksList()->getCount();
    int STC = CompanyPtr->getSpecialTrucksList()->getCount();
    int VTC = CompanyPtr->getVIPTrucksList()->getCount();
    int EmptyTrucksCount = NTC + STC + VTC;

    int WNC = CompanyPtr->getWaitingNormalList()->getCount();
    int WSC = CompanyPtr->getWaitingSpecialList()->getCount();
    int WVC = CompanyPtr->getWaitingVIPList()->getCount();
    int TotalCargosCount = WNC + WSC + WVC;
    //Waiting Cargos
    cout << TotalCargosCount << " Waiting Cargos: ";
    if (WNC) { cout << "["; CompanyPtr->getWaitingNormalList()->print(); cout << "] "; }
    if (WSC) { cout << "("; CompanyPtr->getWaitingSpecialList()->printQueue(); cout << ") "; }
    if (WVC) { cout << "{"; CompanyPtr->getWaitingVIPList()->printPriQueue(); cout << "} "; }
    cout << endl << endl << "-------------------------------------------------------" << endl;
    //Loading Trucks
    cout << CompanyPtr->getLoadingTrucksList()->getCount() << " Loading Trucks: ";
    CompanyPtr->getLoadingTrucksList()->printPriQueue();
    cout << endl << endl << "-------------------------------------------------------" << endl;
    // Loading Cargos-Additional
    cout << CompanyPtr->getLoadingCargosList()->getCount() << " Loading Cargos: ";
    CompanyPtr->getLoadingCargosList()->printPriQueue();
    cout << endl << endl << "-------------------------------------------------------" << endl;
    //Empty Trucks 
    cout << EmptyTrucksCount << " Empty Trucks: ";
    CompanyPtr->getNormalTrucksList()->printPriQueue(); if (NTC && (STC || VTC))cout << ",";
    CompanyPtr->getSpecialTrucksList()->printPriQueue(); if (STC && VTC)cout << ",";
    CompanyPtr->getVIPTrucksList()->printPriQueue();
    cout << endl << endl;
    cout << "-------------------------------------------------------" << endl;
    //Moving Trucks-Additional
    cout << CompanyPtr->getMovingTrucksList()->getCount() << " Moving Trucks: ";
    CompanyPtr->getMovingTrucksList()->printPriQueue();
    cout << endl << endl;
    cout << "-------------------------------------------------------" << endl;
    //Moving Cargos Remember that what is actually printed is the Moving trucks list
    cout << CompanyPtr->getMovingCargosList()->getCount() << " Moving Cargos: ";
    if (CompanyPtr->getMovingCargosList()->getCount()) CompanyPtr->getMovingTrucksList()->printPriQueue();
    cout << endl << endl;
    cout << "-------------------------------------------------------" << endl;
    // In-Checkup
// This will be needed if we do the IncheckupList separation    int IncheckupTrucksCount=CompanyPtr->getIncheckupVIPTrucksList()->getCount()+CompanyPtr->getIncheckupNormalTrucksList()->getCount()+CompanyPtr->getIncheckupSpecialTrucksList()->getCount();
    cout << CompanyPtr->getIncheckupTrucksList()->getCount() << " In-Checkup Trucks: ";
    CompanyPtr->getIncheckupTrucksList()->printPriQueue();
    cout << endl << endl;
    cout << "-------------------------------------------------------" << endl;
    //Delivered Cargos
    cout << CompanyPtr->getDeliveredCargosList()->getCount() << " Delivered Cargos: ";
    this->printDeliveredCargosList();
    cout << endl << endl;
    cout << "-------------------------------------------------------" << endl;
}

string UI::readInputFileName() {
    cout << "Enter Test File Name: " << endl;
    cin >> InputFileName;
    return InputFileName + ".txt";// .txt directory is appended automatically
}
string UI::readOutputFileName() {
    cin >> OutputFileName;
    return OutputFileName + ".txt";// .txt directory is appended automatically
}

