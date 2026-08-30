/**********|**********|**********|
Program: SteppingRobot.h
**********|**********|**********/

#ifndef STEPPINGROBOT_H
#define STEPPINGROBOT_H

#include "Robot.h"
#include "Battlefield.h"

class SteppingRobot : virtual public Robot
{
protected:
    Battlefield *ptrBattlefield;
    int kills;

public:
    SteppingRobot(string type, string name, int x, int y, Battlefield *battlefield);
    virtual void Step();
    void incrementKills() { kills++; }
    int getKills() const override { return kills; }
};

#endif