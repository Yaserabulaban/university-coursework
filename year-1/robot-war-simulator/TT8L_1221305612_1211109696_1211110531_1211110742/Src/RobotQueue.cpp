/**********|**********|**********|
Program: RobotQueue.cpp
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
**********|**********|**********/

#include "../Include/RobotQueue.h"
#include "../Include/Robot.h"
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