/**********|**********|**********|
Program: MadBot.h
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
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
