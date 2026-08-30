/**********|**********|**********|
Program: RobotQueue.cpp
**********|**********|**********/

#include "../include/RobotQueue.h"
#include "../include/Robot.h"
#include <iostream>

using namespace std;

RobotQueue::~RobotQueue()
{
    while (!isEmpty())
    {
        dequeue();
    }
}

void RobotQueue::enqueue(Robot *robot)
{
    Node *newNode = new Node(robot);
    if (isEmpty())
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
    cout << "Enqueued robot: " << robot->getType() << " for re-entry" << endl;
}

Robot *RobotQueue::dequeue()
{
    if (isEmpty())
    {
        return nullptr;
    }
    Node *temp = front;
    Robot *robot = temp->robot;
    front = front->next;
    if (front == nullptr)
    {
        rear = nullptr;
    }
    delete temp;
    cout << "Dequeued robot: " << robot->getType() << " for respawn" << endl;
    return robot;
}

bool RobotQueue::isEmpty() const
{
    return front == nullptr;
}

int RobotQueue::size() const
{
    int count = 0;
    Node *current = front;
    while (current != nullptr)
    {
        count++;
        current = current->next;
    }
    return count;
}