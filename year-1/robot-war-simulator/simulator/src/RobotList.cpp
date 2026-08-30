/**********|**********|**********|
Program: RobotList.cpp
**********|**********|**********/

#include "../include/RobotList.h"
#include "../include/Robot.h"
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