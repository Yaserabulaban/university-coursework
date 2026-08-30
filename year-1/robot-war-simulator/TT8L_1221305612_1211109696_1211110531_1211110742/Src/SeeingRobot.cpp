/**********|**********|**********|
Program: SeeingRobot.cpp
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
**********|**********|**********/

#include "../Include/SeeingRobot.h"
#include "../Include/Battlefield.h"
#include <iostream>

using namespace std;

SeeingRobot::SeeingRobot(string name, string type, int x, int y, Battlefield *ptrBattlefield)
    : Robot(name, type, x, y, ptrBattlefield) {}

void SeeingRobot::Look()
{
    cout << type << " is looking around from (" << x << ", " << y << ")" << endl;

    // Define the 3x3 area around the robot to look at
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            int lookX = x + dx;
            int lookY = y + dy;

            cout << "Checking position (" << lookX << ", " << lookY << ")" << endl;

            // Ensure the position is within battlefield boundaries
            if (ptrBattlefield->isValidPosition(lookX, lookY))
            {
                cout << "Position (" << lookX << ", " << lookY << ") is valid." << endl;
                // Check if there's anything at (lookX, lookY)
                char positionContent = ptrBattlefield->GetPosition(lookX, lookY);
                cout << "Position (" << lookX << ", " << lookY << ") contains: " << positionContent << endl;
                if (positionContent != '.')
                {
                    cout << "Found something at (" << lookX << ", " << lookY << ")" << endl;
                }
            }
            else
            {
                cout << "Position (" << lookX << ", " << lookY << ") is invalid." << endl;
            }
        }
    }
}
