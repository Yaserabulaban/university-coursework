/**********|**********|**********|
Program: RoboCop.cpp
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
**********|**********|**********/

#include "../Include/RoboCop.h"
#include "../Include/Battlefield.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void RoboCop::Look()
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

void RoboCop::Move(int m, int n)
{
    cout << type << " is moving from (" << x << ", " << y << ")" << endl;

    bool moved = false;
    while (!moved)
    {
        int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

        // Attempt to move in a random direction
        int randIndex = rand() % 8;
        int newX = x + directions[randIndex][0];
        int newY = y + directions[randIndex][1];

        // Ensure the new position is within battlefield boundaries
        if (ptrBattlefield->isValidPosition(newX, newY) && ptrBattlefield->CheckSurrounding(newX, newY))
        {
            // Clear the old position
            ptrBattlefield->UpdatePosition(x, y, '.');
            // Move to the new position
            x = newX;
            y = newY;
            // Update the battlefield with the new position
            ptrBattlefield->UpdatePosition(x, y, getName()[0]);
            cout << type << " moved to (" << x << ", " << y << ")" << endl;
            moved = true;
        }
    }
}

void RoboCop::Fire()
{
    for (int i = 0; i < 3; ++i)
    {
        int targetX, targetY;
        do
        {
            targetX = x + (rand() % 21) - 10; // Random position within city block distance of 10
            targetY = y + (rand() % 21) - 10;
        } while (abs(targetX - x) + abs(targetY - y) > 10 || !ptrBattlefield->isValidPosition(targetX, targetY)); // Ensure city block distance <= 10 and position is valid
        
        cout << type << " fires at (" << targetX << ", " << targetY << ")" << endl;
        
        if (targetX == x && targetY == y)
        {
            cout << type << " attempted to shoot itself at (" << targetX << ", " << targetY << "). Skipping fire action." << endl;
            continue; // Skip firing if the target is the same as the robot's position
        }

        if (ptrBattlefield->GetPosition(targetX, targetY) != '.')
        {
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
        }

        else
        {
            cout << "Missed, no target at (" << targetX << ", " << targetY << ")" << endl;
        }
    }
}