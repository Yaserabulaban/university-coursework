/**********|**********|**********|
Program: BlueThunder.cpp
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
**********|**********|**********/

#include "../Include/BlueThunder.h"
#include "../Include/Battlefield.h"
#include "../Include/Madbot.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void BlueThunder::Fire()
{
    // Define the 8 immediate neighboring positions in clockwise order starting from up
    int directions[8][2] = {
        {-1, 0}, // Up
        {-1, 1}, // Top-Right
        {0, 1},  // Right
        {1, 1},  // Bottom-Right
        {1, 0},  // Bottom
        {1, -1}, // Bottom-Left
        {0, -1}, // Left
        {-1, -1} // Top-Left
    };

    bool validShot = false;

    while (!validShot)
    {
        // Determine the target position based on the current firing direction
        int targetX = x + directions[fireDirection][0];
        int targetY = y + directions[fireDirection][1];

        if (ptrBattlefield->isValidPosition(targetX, targetY))
        {
            validShot = true;
            cout << type << " fires at (" << targetX << ", " << targetY << ")" << endl;
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
            else
            {
                cout << "Missed, no target at (" << targetX << ", " << targetY << ")" << endl;
            }
        }
        // Update the firing direction for the next turn
        fireDirection = (fireDirection + 1) % 8;
    }
}
