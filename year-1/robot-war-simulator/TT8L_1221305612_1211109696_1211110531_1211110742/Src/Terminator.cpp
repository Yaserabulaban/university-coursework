/**********|**********|**********|
Program: Terminator.cpp
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
**********|**********|**********/

#include "../Include/Terminator.h"
#include "../Include/Battlefield.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Terminator::Look()
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

void Terminator::Move(int m, int n)
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

void Terminator::Step()
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