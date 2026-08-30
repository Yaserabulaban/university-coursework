/**********|**********|**********|
Program: UltimateRobot.cpp
**********|**********|**********/

#include "../include/UltimateRobot.h"
#include "../include/Battlefield.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void UltimateRobot::Look()
{
    cout << type << " is looking around from (" << x << ", " << y << ")" << endl;
    // Define the 3x3 area around the robot to look at
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; ++dy <= 1;)
        {
            int lookX = x + dx;
            int lookY = y + dy;
            // Ensure the position is within battlefield boundaries
            if (x != lookX || y != lookY)
            {
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
}

void UltimateRobot::Move(int m, int n)
{
    cout << type << " is moving from (" << x << ", " << y << ")" << endl;
    bool moved = false;
    while (!moved)
    {
        int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
        int randIndex = rand() % 8;
        int newX = x + directions[randIndex][0];
        int newY = y + directions[randIndex][1];
        if (ptrBattlefield->isValidPosition(newX, newY) && ptrBattlefield->CheckSurrounding(newX, newY))
        {
            moved = true;
            ptrBattlefield->UpdatePosition(x, y, '.');
            x = newX;
            y = newY;
            ptrBattlefield->UpdatePosition(x, y, getName()[0]);
            cout << type << " moved to (" << x << ", " << y << ")" << endl;
        }
    }
}

void UltimateRobot::Fire()
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

void UltimateRobot::Step()
{
    int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    bool foundRobot = false;

    for (auto &direction : directions)
    {
        int newX = x + direction[0];
        int newY = y + direction[1];

        if (ptrBattlefield->isValidPosition(newX, newY) && !ptrBattlefield->CheckSurrounding(newX, newY))
        {
            Robot *targetRobot = ptrBattlefield->getRobotAt(newX, newY);
            if (targetRobot)
            {
                cout << type << " steps on " << targetRobot->getType() << " at (" << newX << ", " << newY << ")" << endl;
                targetRobot->decreaseLife();
                cout << targetRobot->getType() << " has " << targetRobot->getLives() << " lives left" << endl;
                ptrBattlefield->removeRobot(targetRobot); // Remove the stepped-on robot
                ptrBattlefield->UpdatePosition(x, y, '.');
                x = newX;
                y = newY;
                ptrBattlefield->UpdatePosition(x, y, getName()[0]);
                ptrBattlefield->Display();
                incrementKills();
                foundRobot = true;
                break;
            }
        }
    }
    if (!foundRobot)
    {
        Move(ptrBattlefield->getRows(), ptrBattlefield->getCols());
    }
}