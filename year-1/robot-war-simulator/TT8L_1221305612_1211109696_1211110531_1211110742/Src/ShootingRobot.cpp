/**********|**********|**********|
Program: ShootingRobot.cpp
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
**********|**********|**********/

#include "../Include/ShootingRobot.h"
#include "../Include/Battlefield.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void ShootingRobot::Fire()
{
    int targetX = rand() % ptrBattlefield->getRows();
    int targetY = rand() % ptrBattlefield->getCols();

    if (targetX == x && targetY == y)
    {
        cout << type << " attempted to shoot itself at (" << targetX << ", " << targetY << "). Skipping fire action." << endl;
        return; // Skip firing if the target is the same as the robot's position
    }

    if (ptrBattlefield->isValidPosition(targetX, targetY))
    {
        if (ptrBattlefield->GetPosition(targetX, targetY) != '.')
        {
            cout << type << " is firing at (" << targetX << ", " << targetY << ")" << endl;

            Robot *target = ptrBattlefield->getRobotAt(targetX, targetY);
            if (target)
            {
                cout << "Hit target at (" << targetX << ", " << targetY << ")" << endl;

                target->decreaseLife();
                cout << target->getType() << " has " << target->getLives() << " lives left" << endl;
                ptrBattlefield->UpdatePosition(targetX, targetY, '.');
                cout << target->getType() << " is killed by " << type << endl;
                ptrBattlefield->removeRobot(target);
                ptrBattlefield->Display(); // Display battlefield after kill
                incrementKills();
            }
        }
        else
        {
            cout << "Missed, no target at (" << targetX << ", " << targetY << ")" << endl;
        }
    }
    else
    {
        cout << "Invalid target position (" << targetX << ", " << targetY << ")" << endl;
    }
}
