/**********|**********|**********|
Program: Terminator.h
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
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
