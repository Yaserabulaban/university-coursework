/**********|**********|**********|
Program: RobotList.h
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
