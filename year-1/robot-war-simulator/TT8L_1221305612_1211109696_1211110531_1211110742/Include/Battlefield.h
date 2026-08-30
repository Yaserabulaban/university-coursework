/**********|**********|**********|
Program: Battlefield.h
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
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
