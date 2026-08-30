/**********|**********|**********|
Program: MadBot.h
**********|**********|**********/

#ifndef MADBOT_H
#define MADBOT_H

#include "ShootingRobot.h"
#include "SeeingRobot.h"
#include "Battlefield.h"
#include "RoboTank.h"

using namespace std;

class MadBot : virtual public ShootingRobot, virtual public SeeingRobot
{
protected:
    Battlefield *ptrBattlefield;
    int kills;

public:
    MadBot(string name, int x, int y, Battlefield *ptrBattlefield)
        : Robot("MadBot", name, x, y, ptrBattlefield),
          ShootingRobot("MadBot", name, x, y, ptrBattlefield),
          SeeingRobot("MadBot", name, x, y, ptrBattlefield),
          ptrBattlefield(ptrBattlefield), kills(0) {}

    void Fire() override;
    void Look() override;
    bool shouldUpgrade() const override { return kills >= 3; } // Check upgrade condition
    void incrementKills() { kills++; }
    int getKills() const override { return kills; }
};

#endif
