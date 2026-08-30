/**********|**********|**********|
Program: MadBot.cpp
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
**********|**********|**********/

#include "../Include/MadBot.h"
#include "../Include/Battlefield.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void MadBot::Look()
{
    cout << type << " is looking around from (" << x << ", " << y << ")" << endl;

    // Define the 3x3 area around the robot to look at
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            int lookX = x + dx;
            int lookY = y + dy;
            // Ensure the position is within battlefield boundaries
            if (ptrBattlefield->isValidPosition(lookX, lookY))
            {
                cout << "Checking position (" << lookX << ", " << lookY << ")" << endl;
                // Check if there's anything at (lookX, lookY)
                if (ptrBattlefield->GetPosition(lookX, lookY) != '.')
                {
                    cout << "Found something at (" << lookX << ", " << lookY << ")" << endl;
                }
            }
        }
    }
}

void MadBot::Fire()
{
    cout << type << " is firing." << endl;

    // Define the 8 immediate neighboring positions
    int directions[8][2] = {
        {0, -1}, // Left
        {1, -1}, // Bottom-Left
        {1, 0},  // Bottom
        {1, 1},  // Bottom-Right
        {0, 1},  // Right
        {-1, 1}, // Top-Right
        {-1, 0}, // Top
        {-1, -1} // Top-Left
    };

    bool validShot = false;

    while (!validShot)
    {
        // Choose a random direction to fire
        int randIndex = rand() % 8;
        int targetX = x + directions[randIndex][0];
        int targetY = y + directions[randIndex][1];

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
    }
}
