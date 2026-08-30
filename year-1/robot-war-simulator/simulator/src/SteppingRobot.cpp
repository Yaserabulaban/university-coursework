/**********|**********|**********|
Program: SteppingRobot.cpp
**********|**********|**********/

#include "../include/SteppingRobot.h"
#include "../include/Battlefield.h"
#include <iostream>
#include <cstdlib>

using namespace std;

SteppingRobot::SteppingRobot(string name, string type, int x, int y, Battlefield *battlefield)
    : Robot(name, type, x, y, ptrBattlefield), ptrBattlefield(battlefield) {}

void SteppingRobot::Step()
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
}