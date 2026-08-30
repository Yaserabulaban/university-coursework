/**********|**********|**********|
Program: SeeingRobot.cpp
**********|**********|**********/

#include "../include/SeeingRobot.h"
#include "../include/Battlefield.h"
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
