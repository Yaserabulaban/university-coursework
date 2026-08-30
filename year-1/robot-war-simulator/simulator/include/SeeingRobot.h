/**********|**********|**********|
Program: SeeingRobot.h
**********|**********|**********/

#ifndef SEEINGROBOT_H
#define SEEINGROBOT_H

#include "Robot.h"

class SeeingRobot : virtual public Robot {
public:
    SeeingRobot(string type, string name, int x, int y, Battlefield *ptrBattlefield);
    virtual void Look();
};

#endif 