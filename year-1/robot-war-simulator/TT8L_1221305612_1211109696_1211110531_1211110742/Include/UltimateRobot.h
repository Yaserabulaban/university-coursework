/**********|**********|**********|
Program: UltimateRobot.h
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
**********|**********|**********/

#ifndef ULTIMATEROBOT_H
#define ULTIMATEROBOT_H

#include "MovingRobot.h"
#include "ShootingRobot.h"
#include "SeeingRobot.h"
#include "SteppingRobot.h"
#include "Battlefield.h"

using namespace std;

class UltimateRobot : virtual public MovingRobot, virtual public ShootingRobot, virtual public SeeingRobot, virtual public SteppingRobot
{
protected:
    Battlefield *ptrBattlefield;
    int kills;

public:
    UltimateRobot(string name, int x, int y, Battlefield *ptrBattlefield)
        : Robot("UltimateRobot", name, x, y, ptrBattlefield),
          MovingRobot("UltimateRobot", name, x, y, ptrBattlefield),
          ShootingRobot("UltimateRobot", name, x, y, ptrBattlefield),
          SeeingRobot("UltimateRobot", name, x, y, ptrBattlefield),
          SteppingRobot("UltimateRobot", name, x, y, ptrBattlefield), kills (0),
          ptrBattlefield(ptrBattlefield) {}

    void Look() override;
    void Move(int m, int n) override;
    void Fire() override;
    void Step() override;
    bool shouldUpgrade() const override { return false; } // UltimateRobot does not upgrade
    int getKills() const override { return kills; }
    void incrementKills() { kills++; }
};

#endif
