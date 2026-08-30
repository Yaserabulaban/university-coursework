/**********|**********|**********|
Program: BlueThunder.h
**********|**********|**********/

#ifndef BLUETHUNDER_H
#define BLUETHUNDER_H

#include "ShootingRobot.h"
#include "Battlefield.h"
#include "MadBot.h"

class BlueThunder : virtual public ShootingRobot
{
protected:
    Battlefield *ptrBattlefield;
    int fireDirection; // To keep track of the firing direction
    int kills;

public:
    BlueThunder(string name, int x, int y, Battlefield *ptrBattlefield)
        : Robot("BlueThunder", name, x, y, ptrBattlefield),
          ShootingRobot("BlueThunder", name, x, y, ptrBattlefield),
          ptrBattlefield(ptrBattlefield), fireDirection(0), kills(0) {}

    void Fire() override;
    bool shouldUpgrade() const override { return kills >= 3; } // Check upgrade condition
    void incrementKills() { kills++; }
    int getKills() const override { return kills; }
};

#endif
