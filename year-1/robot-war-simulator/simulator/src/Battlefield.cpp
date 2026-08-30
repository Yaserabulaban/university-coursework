/**********|**********|**********|
Program: Battlefield.cpp
**********|**********|**********/

#include "../include/Battlefield.h"
#include "../include/Robot.h"
#include <iostream>
#include <algorithm>

using namespace std;

Battlefield::Battlefield(int m, int n) : rows(m), cols(n)
{
    grid = new char *[rows];
    for (int i = 0; i < rows; ++i)
    {
        grid[i] = new char[cols];
        for (int j = 0; j < cols; ++j)
        {
            grid[i][j] = '.';
        }
    }
}

Battlefield::~Battlefield()
{
    for (int i = 0; i < rows; ++i)
    {
        delete[] grid[i];
    }
    delete[] grid;
}

void Battlefield::Display() const
{
    cout << "Current battlefield state:" << endl;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }
}

void Battlefield::UpdatePosition(int x, int y, char symbol)
{
    if (isValidPosition(x, y))
    {
        grid[x][y] = symbol;
    }
}

char Battlefield::GetPosition(int x, int y) const
{
    if (isValidPosition(x, y))
    {
        return grid[x][y];
    }
    return '.';
}

bool Battlefield::isValidPosition(int x, int y) const
{
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

bool Battlefield::CheckSurrounding(int x, int y) const
{
    return grid[x][y] == '.';
}

Robot *Battlefield::getRobotAt(int x, int y)
{
    RobotNode *current = robots.getHead(); // Use RobotList's head node
    while (current != nullptr)
    {
        cout << "Checking robot " << current->robot->getType() << " at (" << current->robot->getX() << ", " << current->robot->getY() << ")" << endl;
        if (current->robot->getX() == x && current->robot->getY() == y)
        {
            cout << "Found robot: " << current->robot->getType() << " at (" << x << ", " << y << ")" << endl;
            return current->robot;
        }
        current = current->next;
    }
    cout << "No robot found at (" << x << ", " << y << ")" << endl;
    return nullptr;
}

void Battlefield::addRobot(Robot *robot)
{
    robots.AddRobot(robot);                                            // Add to RobotList
    UpdatePosition(robot->getX(), robot->getY(), robot->getName()[0]); // Update battlefield
}

void Battlefield::removeRobot(Robot *robot)
{
    if (robot == nullptr)
        return;
    robots.RemoveRobot(robot);
    UpdatePosition(robot->getX(), robot->getY(), '.');
    robot->markDead();
    if (robot->getLives() > 0 && !robot->shouldUpgrade())
    {
        reEntryQueue.enqueue(robot);
    }
}

void Battlefield::respawnRobot(Robot *robot)
{
    robot->respawn();
    robot->markAlive();     // Mark the robot as alive
    robots.AddRobot(robot); // Add back to the RobotList
    UpdatePosition(robot->getX(), robot->getY(), robot->getName()[0]);
    cout << robot->getType() << " has respawned at (" << robot->getX() << ", " << robot->getY() << ")" << endl;
}

void Battlefield::printSizes()
{
    cout << "Size of robots list: " << robots.size() << endl;
    cout << "Size of re-entry queue: " << reEntryQueue.size() << endl;
}

int Battlefield::countRobotsWithLives() const
{
    int count = 0;
    RobotNode *current = robots.getHead();
    while (current != nullptr)
    {
        if (current->robot->getLives() > 0) // Count only robots with lives greater than 0
        {
            ++count;
        }
        current = current->next;
    }
    return count;
}

Robot *Battlefield::getRobotWithLives() const
{
    RobotNode *current = robots.getHead();
    while (current != nullptr)
    {
        if (current->robot->getLives() > 0) // Find the robot with lives greater than 0
        {
            return current->robot;
        }
        current = current->next;
    }
    return nullptr;
}