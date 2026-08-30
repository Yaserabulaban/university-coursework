/**********|**********|**********|
Program: BlueThunder.h
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
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
