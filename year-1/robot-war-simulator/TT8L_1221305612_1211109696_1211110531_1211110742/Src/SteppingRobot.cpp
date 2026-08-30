/**********|**********|**********|
Program: SteppingRobot.cpp
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
**********|**********|**********/

#include "../Include/SteppingRobot.h"
#include "../Include/Battlefield.h"
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