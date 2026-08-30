/**********|**********|**********|
Program: MovingRobot.cpp
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
**********|**********|**********/

#include "../Include/MovingRobot.h"
#include "../Include/Battlefield.h"
#include <iostream>
#include <cstdlib>

using namespace std;

MovingRobot::MovingRobot(string name, string type, int x, int y, Battlefield *ptrBattlefield)
    : Robot(name, type, x, y, ptrBattlefield) {}

void MovingRobot::Move(int m, int n)
{
    // Define possible move directions: up, down, left, right, and diagonals
    int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
    int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};

    // Choose a random direction to move
    int moveDirection = rand() % 8;

    // Calculate new position based on the move direction
    int newX = x + dx[moveDirection];
    int newY = y + dy[moveDirection];

    // Ensure the new position is within battlefield boundaries
    if (newX >= 0 && newX < m && newY >= 0 && newY < n && ptrBattlefield->CheckSurrounding(newX, newY))
    {
        ptrBattlefield->UpdatePosition(x, y, '.'); // Clear the old position
        x = newX;
        y = newY;
        ptrBattlefield->UpdatePosition(x, y, getName()[0]); // Set the new position
        cout << type << " moved to (" << x << ", " << y << ")" << endl;
    }
    else
    {
        cout << type << " tried to move out of bounds and stayed at (" << x << ", " << y << ")" << endl;
    }
}