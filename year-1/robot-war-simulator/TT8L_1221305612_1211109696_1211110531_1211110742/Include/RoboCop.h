/**********|**********|**********|
Program: RoboCop.h
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
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
