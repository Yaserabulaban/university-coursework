/**********|**********|**********|
Program: Main.cpp
**********|**********|**********/

#include "include/Simulation.h"

int main()
{
    Simulation simulation;          // Example initialization
    simulation.InitializeRobots("robots.txt"); // Example robot file
    simulation.Run();
    return 0;
}