/**********|**********|**********|
Program: Terminator.h
**********|**********|**********/

#ifndef TERMINATOR_H
#define TERMINATOR_H

#include "SeeingRobot.h"
#include "SteppingRobot.h"
#include "MovingRobot.h"
#include "Battlefield.h"
#include "TerminatorRoboCop.h"

class Terminator : virtual public SeeingRobot, virtual public SteppingRobot, virtual public MovingRobot
{

protected:
    Battlefield *ptrBattlefield;
    int kills;

public:
    Terminator(string name, int x, int y, Battlefield *ptrBattlefield)
        : Robot("Terminator", name, x, y, ptrBattlefield),
          SeeingRobot("Terminator", name, x, y, ptrBattlefield),
          SteppingRobot("Terminator", name, x, y, ptrBattlefield),
          MovingRobot("Terminator", name, x, y, ptrBattlefield),
          ptrBattlefield(ptrBattlefield), kills(0) {}

    void Look() override;
    void Step() override;
    void Move(int m, int n) override;
    bool shouldUpgrade() const override { return kills >= 3; } // Check upgrade condition
    int getKills() const override { return kills; }
    void incrementKills() { kills++; }
};

#endif
