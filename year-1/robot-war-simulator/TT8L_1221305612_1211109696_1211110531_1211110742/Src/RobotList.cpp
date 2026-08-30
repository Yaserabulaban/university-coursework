/**********|**********|**********|
Program: RobotList.cpp
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
**********|**********|**********/

#include "../Include/RobotList.h"
#include "../Include/Robot.h"
#include <iostream>
#include <cassert>

RobotList::RobotList() : head(nullptr), tail(nullptr) {}

RobotList::~RobotList()
{
    RobotNode *current = head;
    while (current)
    {
        RobotNode *next = current->next;
        delete current->robot;
        delete current;
        current = next;
    }
}

void RobotList::AddRobot(Robot *robot)
{
    RobotNode *newNode = new RobotNode{robot, nullptr};
    if (tail == nullptr)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}

void RobotList::RemoveRobot(Robot *robot)
{
    RobotNode *current = head;
    RobotNode *prev = nullptr;
    while (current != nullptr && current->robot != robot)
    {
        prev = current;
        current = current->next;
    }
    if (current != nullptr)
    {
        if (prev == nullptr)
        {
            head = current->next;
        }
        else
        {
            prev->next = current->next;
        }
        if (current == tail)
        {
            tail = prev;
        }
        delete current;
    }
}

Robot *RobotList::GetNextRobot()
{
    if (head == nullptr)
        return nullptr;
    Robot *robot = head->robot;
    RobotNode *temp = head;
    head = head->next;
    if (head == nullptr)
    {
        tail = nullptr;
    }
    delete temp;
    return robot;
}

bool RobotList::IsEmpty() const
{
    return head == nullptr;
}

int RobotList::size() const
{
    int size = 0;
    RobotNode *current = head;
    while (current != nullptr)
    {
        ++size;
        current = current->next;
    }
    return size;
}

void RobotList::resetUpgradeFlags()
{
    RobotNode *current = head;
    while (current != nullptr)
    {
        current->robot->resetUpgradedThisTurn();
        current = current->next;
    }
}