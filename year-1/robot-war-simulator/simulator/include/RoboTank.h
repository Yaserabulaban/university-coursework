/**********|**********|**********|
Program: RoboTank.h
**********|**********|**********/

#ifndef ROBOTANK_H
#define ROBOTANK_H

#include "ShootingRobot.h"
#include "Battlefield.h"
#include "UltimateRobot.h"

using namespace std;

class RoboTank : virtual public ShootingRobot
{
protected:
    Battlefield *ptrBattlefield;
    int kills;

public:
    RoboTank(string name, int x, int y, Battlefield *ptrBattlefield)
        : Robot("RoboTank", name, x, y, ptrBattlefield),
          ShootingRobot("RoboTank", name, x, y, ptrBattlefield),
          ptrBattlefield(ptrBattlefield), kills(0) {}

    void Fire() override;
    bool shouldUpgrade() const override { return kills >= 3; } // Check upgrade condition
    int getKills() const override { return kills; }
    void incrementKills() { kills++; }
};

#endif
