/**********|**********|**********|
Program: Robot.cpp
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
**********|**********|**********/

#include "../Include/Robot.h"
#include "../Include/Battlefield.h"

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
