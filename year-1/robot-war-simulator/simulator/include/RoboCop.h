/**********|**********|**********|
Program: RoboCop.h
**********|**********|**********/

#ifndef ROBOCOP_H
#define ROBOCOP_H

#include "MovingRobot.h"
#include "ShootingRobot.h"
#include "SeeingRobot.h"
#include "Battlefield.h"
#include "TerminatorRoboCop.h"

class RoboCop : virtual public MovingRobot, virtual public ShootingRobot, virtual public SeeingRobot
{
protected:
    Battlefield *ptrBattlefield;
    int kills;

public:
    RoboCop(string name, int x, int y, Battlefield *ptrBattlefield)
        : Robot("RoboCop", name, x, y, ptrBattlefield),
          MovingRobot("RoboCop", name, x, y, ptrBattlefield),
          ShootingRobot("RoboCop", name, x, y, ptrBattlefield),
          SeeingRobot("RoboCop", name, x, y, ptrBattlefield),
          ptrBattlefield(ptrBattlefield), kills(0) {}

    void Look() override;
    void Move(int m, int n) override;
    void Fire() override;
    bool shouldUpgrade() const override { return kills >= 3; } // Check upgrade condition
    int getKills() const override { return kills; }
    void incrementKills() { kills++; }
};

#endif
