/**********|**********|**********|
Program: ShootingRobot.h
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
**********|**********|**********/

#ifndef SHOOTINGROBOT_H
#define SHOOTINGROBOT_H

#include "Robot.h"
#include "Battlefield.h"

class ShootingRobot : virtual public Robot
{
protected:
    Battlefield *ptrBattlefield;
    int kills;

public:
    ShootingRobot(string type, string name, int x, int y, Battlefield *ptrBattlefield)
        : Robot(type, name, x, y, ptrBattlefield), kills(0) {}

    virtual void Fire() = 0;
    int getKills() const override { return kills; }
    void incrementKills() { kills++; }
};

#endif
