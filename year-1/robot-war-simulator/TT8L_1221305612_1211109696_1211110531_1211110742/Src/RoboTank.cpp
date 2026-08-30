/**********|**********|**********|
Program: RoboTank.cpp
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
**********|**********|**********/

#include "../Include/RoboTank.h"
#include "../Include/Battlefield.h"
#include <iostream>
#include <cstdlib>

using namespace std;

#include "../Include/RoboTank.h"
#include "../Include/Battlefield.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void RoboTank::Fire()
{
    bool validShot = false;

    while (!validShot)
    {
        int targetX = rand() % ptrBattlefield->getRows();
        int targetY = rand() % ptrBattlefield->getCols();

        if (ptrBattlefield->isValidPosition(targetX, targetY))
        {
            validShot = true;
            cout << type << " is firing at (" << targetX << ", " << targetY << ")" << endl;
            Robot *target = ptrBattlefield->getRobotAt(targetX, targetY);
            if (target != nullptr)
            {
                cout << "Hit target at (" << targetX << ", " << targetY << ")" << endl;
                target->decreaseLife();
                cout << target->getType() << " has " << target->getLives() << " lives left" << endl;
                ptrBattlefield->UpdatePosition(targetX, targetY, '.');
                cout << type << " killed " << target->getType() << endl;
                ptrBattlefield->removeRobot(target);
                ptrBattlefield->Display();
                incrementKills();
            }
        }
        else
        {
            cout << "Missed, no target at (" << targetX << ", " << targetY << ")" << endl;
        }
    }
}
