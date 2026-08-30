/**********|**********|**********|
Program: Battlefield.h
**********|**********|**********/

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "Robot.h"
#include "RobotList.h"
#include "RobotQueue.h"
#include <iostream>

class Robot;

class Battlefield
{
    int rows, cols;
    char **grid;
    RobotList robots;
    RobotQueue reEntryQueue; // Queue to manage robot removal and respawn

public:
    Battlefield(int m, int n);
    ~Battlefield();
    void Display() const;
    void UpdatePosition(int x, int y, char symbol);
    void addRobot(Robot *robot);
    void removeRobot(Robot *robot);
    void respawnRobot(Robot *robot);
    void printSizes();
    bool CheckSurrounding(int x, int y) const;
    bool isValidPosition(int x, int y) const;
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    int countRobotsWithLives() const;
    char GetPosition(int x, int y) const;
    RobotList &getRobots() { return robots; }
    RobotQueue &getReEntryQueue() { return reEntryQueue; }
    Robot *getRobotWithLives() const;
    Robot *getRobotAt(int x, int y);
};

#endif
