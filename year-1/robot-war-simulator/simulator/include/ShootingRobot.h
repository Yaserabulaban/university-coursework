/**********|**********|**********|
Program: ShootingRobot.h
**********|**********|**********/

#ifndef SHOOTINGROBOT_H
#define SHOOTINGROBOT_H

#include "Robot.h"
#include "Battlefield.h"

class ShootingRobot : virtual public Robot
{
protected:
    Battlefield *ptrBattlefield;
    int kills;

public:
    ShootingRobot(string type, string name, int x, int y, Battlefield *ptrBattlefield)
        : Robot(type, name, x, y, ptrBattlefield), kills(0) {}

    virtual void Fire() = 0;
    int getKills() const override { return kills; }
    void incrementKills() { kills++; }
};

#endif
