/**********|**********|**********|
Program: Simulation.h
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
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
