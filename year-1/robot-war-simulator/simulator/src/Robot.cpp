/**********|**********|**********|
Program: Robot.cpp
**********|**********|**********/

#include "../include/Robot.h"
#include "../include/Battlefield.h"

Robot::Robot(string type, string name, int x, int y, Battlefield *ptrBattlefield)
    : type(type), name(name), x(x), y(y), ptrBattlefield(ptrBattlefield), lives(3), status(true) {}

bool Robot::isAlive() const
{
    return status;
}

void Robot::decreaseLife()
{
    --lives;
    if (lives == 0)
    {
        status = false;
    }
}

void Robot::respawn()
{
    while (true)
    {
        int newX = rand() % ptrBattlefield->getRows();
        int newY = rand() % ptrBattlefield->getCols();
        if (ptrBattlefield->CheckSurrounding(newX, newY))
        {
            x = newX;
            y = newY;
            ptrBattlefield->UpdatePosition(x, y, getName()[0]);
            break;
        }
    }
}
