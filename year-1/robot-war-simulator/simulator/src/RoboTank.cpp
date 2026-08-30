/**********|**********|**********|
Program: RoboTank.cpp
**********|**********|**********/

#include "../include/RoboTank.h"
#include "../include/Battlefield.h"
#include <iostream>
#include <cstdlib>

using namespace std;

#include "../include/RoboTank.h"
#include "../include/Battlefield.h"
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
