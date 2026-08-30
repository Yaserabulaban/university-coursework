/**********|**********|**********|
Program: Simulation.h
**********|**********|**********/

#ifndef SIMULATION_H
#define SIMULATION_H

#include "Battlefield.h"
#include "RobotList.h"
#include "RobotQueue.h"
#include <string>
#include <fstream>

using namespace std;

class Simulation
{
private:
    Battlefield *ptr_battlefield;
    RobotList *ptr_robots;
    RobotQueue *ptr_reEntryQueue;
    int steps;
    ofstream logFile; // File output stream for logging
    void LogStats();  // Function to log the final stats

public:
    Simulation();
    ~Simulation(); // Destructor to close the log file
    void InitializeRobots(const string &filename);
    void Run();
    void UpgradeRobot(Robot *oldRobot);
    void DisplayStats();
};

#endif // SIMULATION_H
