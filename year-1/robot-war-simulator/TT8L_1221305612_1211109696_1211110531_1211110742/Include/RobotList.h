/**********|**********|**********|
Program: RobotList.h
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
**********|**********|**********/

#ifndef ROBOTLIST_H
#define ROBOTLIST_H

#include "Robot.h"

struct RobotNode
{
    Robot *robot;
    RobotNode *next;
};

class RobotList
{
    RobotNode *head;
    RobotNode *tail;

public:
    RobotList();
    ~RobotList();
    void AddRobot(Robot *robot);
    void RemoveRobot(Robot *robot);
    void resetUpgradeFlags();
    bool IsEmpty() const;
    int size() const;
    Robot *GetNextRobot();
    RobotNode *getHead() const { return head; } // Added this method
};

#endif
