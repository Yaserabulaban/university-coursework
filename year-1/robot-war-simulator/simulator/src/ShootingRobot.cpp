/**********|**********|**********|
Program: ShootingRobot.cpp
**********|**********|**********/

#include "../include/ShootingRobot.h"
#include "../include/Battlefield.h"
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
