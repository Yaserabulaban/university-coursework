/**********|**********|**********|
Program: TerminatorRoboCop.h
**********|**********|**********/

#ifndef TERMINATORROBOCOP_H
#define TERMINATORROBOCOP_H

#include "ShootingRobot.h"
#include "SeeingRobot.h"
#include "SteppingRobot.h"
#include "MovingRobot.h"
#include "Battlefield.h"
#include "UltimateRobot.h"

using namespace std;

class TerminatorRoboCop : virtual public MovingRobot, virtual public ShootingRobot, virtual public SeeingRobot, virtual public SteppingRobot
{
protected:
    Battlefield *ptrBattlefield;
    int kills;

public:
    TerminatorRoboCop(string name, int x, int y, Battlefield *ptrBattlefield)
        : Robot("TerminatorRoboCop", name, x, y, ptrBattlefield),
          MovingRobot("TerminatorRoboCop", name, x, y, ptrBattlefield),
          ShootingRobot("TerminatorRoboCop", name, x, y, ptrBattlefield),
          SeeingRobot("TerminatorRoboCop", name, x, y, ptrBattlefield),
          SteppingRobot("TerminatorRoboCop", name, x, y, ptrBattlefield),
          ptrBattlefield(ptrBattlefield), kills(0) {}

    void Look() override;
    void Move(int m, int n) override;
    void Fire() override;
    void Step() override;
    bool shouldUpgrade() const override { return kills >= 3; } // Check upgrade condition
    int getKills() const override { return kills; }
    void incrementKills() { kills++; }
};

#endif
