/**********|**********|**********|
Program: Simulation.cpp
**********|**********|**********/

#include "../include/Simulation.h"
#include "../include/RoboCop.h"
#include "../include/Terminator.h"
#include "../include/TerminatorRoboCop.h"
#include "../include/BlueThunder.h"
#include "../include/MadBot.h"
#include "../include/RoboTank.h"
#include "../include/UltimateRobot.h"
#include "../include/Battlefield.h"
#include "../include/RobotList.h"
#include "../include/RobotQueue.h"
#include "../include/Robot.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set> // To track processed robots

using namespace std;

Simulation::Simulation()
    : ptr_battlefield(nullptr), ptr_robots(new RobotList()), ptr_reEntryQueue(new RobotQueue()), steps(0)
{
    logFile.open("Simulationlog.txt");
    if (logFile.is_open())
    {
        logFile << "Simulation Log\n";
    }
    else
    {
        cerr << "Unable to open log file." << endl;
    }
}

Simulation::~Simulation()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}

void Simulation::InitializeRobots(const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    string line;
    // Read the battlefield dimensions
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        istringstream iss(line);
        int m, n;
        if (iss >> m >> n)
        {
            ptr_battlefield = new Battlefield(m, n);
            break;
        }
    }

    if (!ptr_battlefield)
    { // Check if ptr_battlefield is initialized
        cerr << "Error: Battlefield not initialized." << endl;
        return;
    }

    // Read the number of steps
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        istringstream iss(line);
        if (iss >> steps)
        {
            break;
        }
    }

    // Read the robot details
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        istringstream iss(line);
        string type, name;
        string startX, startY;
        if (!(iss >> type >> name >> startX >> startY))
            continue;
        int x, y;

        if (startX == "random" || startY == "random")
        {
            x = rand() % ptr_battlefield->getCols();
            y = rand() % ptr_battlefield->getRows();
        }
        else
        {
            x = stoi(startX);
            y = stoi(startY);
        }

        if (ptr_battlefield->GetPosition(x, y) != '.')
        {
            cerr << "Position (" << x << ", " << y << ") is already occupied. Skipping robot: " << name << endl;
            continue;
        }

        Robot *robot = nullptr;
        if (type == "RoboCop")
        {
            robot = new RoboCop(name, x, y, ptr_battlefield);
        }
        else if (type == "Terminator")
        {
            robot = new Terminator(name, x, y, ptr_battlefield);
        }
        else if (type == "TerminatorRoboCop")
        {
            robot = new TerminatorRoboCop(name, x, y, ptr_battlefield);
        }
        else if (type == "BlueThunder")
        {
            robot = new BlueThunder(name, x, y, ptr_battlefield);
        }
        else if (type == "Madbot")
        {
            robot = new MadBot(name, x, y, ptr_battlefield);
        }
        else if (type == "RoboTank")
        {
            robot = new RoboTank(name, x, y, ptr_battlefield);
        }
        else if (type == "UltimateRobot")
        {
            robot = new UltimateRobot(name, x, y, ptr_battlefield);
        }

        if (robot)
        {
            ptr_robots->AddRobot(robot);
            ptr_battlefield->addRobot(robot); // Add robot to battlefield's linked list
            ptr_battlefield->UpdatePosition(x, y, robot->getName()[0]);
        }
    }
    file.close();
}

void Simulation::Run()
{
    if (!logFile.is_open())
    {
        cerr << "Log file is not open." << endl;
        return;
    }

    for (int step = 0; step < steps; ++step)
    {
        cout << "Step " << step + 1 << " of " << steps << endl;
        logFile << "Step " << step + 1 << " of " << steps << endl;
        ptr_battlefield->Display();
        logFile << "Current battlefield state:\n";
        for (int i = 0; i < ptr_battlefield->getRows(); ++i)
        {
            for (int j = 0; j < ptr_battlefield->getCols(); ++j)
            {
                logFile << ptr_battlefield->GetPosition(i, j) << ' ';
            }
            logFile << '\n';
        }

        RobotList tempRobots;
        RobotList toRemoveRobots;
        RobotList respawnedRobots; // List to track respawned robots in the same step
        bool respawnedThisStep = false;
        unordered_set<Robot *> upgradedRobots; // To track robots upgraded this step

        while (!ptr_robots->IsEmpty() || !respawnedRobots.IsEmpty())
        {
            Robot *ptr_robot = !respawnedRobots.IsEmpty() ? respawnedRobots.GetNextRobot() : ptr_robots->GetNextRobot();
            if (!ptr_robot)
            {
                cerr << "Error: ptr_robot is nullptr!" << endl;
                break;
            }
            if (upgradedRobots.find(ptr_robot) != upgradedRobots.end())
            {
                cout << "Skipping robot because it just got upgraded: " << ptr_robot->getType() << endl;
                continue;
            }

            cout << endl
                 << "Processing robot: " << ptr_robot->getType() << " (" << ptr_robot->getName() << ") at position (" << ptr_robot->getX() << ", " << ptr_robot->getY() << ")" << endl;

            logFile << "Processing robot: " << ptr_robot->getType() << " (" << ptr_robot->getName() << ") at position (" << ptr_robot->getX() << ", " << ptr_robot->getY() << ")" << endl;

            // Skip dead robots
            if (!ptr_robot->isAlive())
            {
                cout << "Skipping dead robot: " << ptr_robot->getType() << endl;
                continue;
            }

            // Perform actions
            if (SeeingRobot *seeingRobot = dynamic_cast<SeeingRobot *>(ptr_robot))
            {
                logFile << "Robot " << ptr_robot->getType() << " is looking.\n";
                seeingRobot->Look();
            }
            if (MovingRobot *movingRobot = dynamic_cast<MovingRobot *>(ptr_robot))
            {
                if (SteppingRobot *steppingRobot = dynamic_cast<SteppingRobot *>(ptr_robot))
                {
                    logFile << "Robot " << ptr_robot->getType() << " is stepping.\n";
                    steppingRobot->Step();
                }
                else
                {
                    logFile << "Robot " << ptr_robot->getType() << " is moving.\n";
                    movingRobot->Move(ptr_battlefield->getRows(), ptr_battlefield->getCols());
                }
            }
            if (ShootingRobot *shootingRobot = dynamic_cast<ShootingRobot *>(ptr_robot))
            {
                logFile << "Robot " << ptr_robot->getType() << " is firing.\n";
                shootingRobot->Fire();
            }

            cout << "Updating position for robot: " << ptr_robot->getType() << endl;
            logFile << "Updating position for robot: " << ptr_robot->getType() << '\n';
            ptr_battlefield->UpdatePosition(ptr_robot->getX(), ptr_robot->getY(), ptr_robot->getName()[0]);

            // Check for upgrade
            if (ptr_robot->shouldUpgrade())
            {
                upgradedRobots.insert(ptr_robot);
                UpgradeRobot(ptr_robot);
                tempRobots.RemoveRobot(ptr_robot); // delete current old robot
            }
            else
            {
                tempRobots.AddRobot(ptr_robot); // Add robot to temporary list after actions
            }
        }

        // Clean up dead robots
        while (!toRemoveRobots.IsEmpty())
        {
            Robot *dead_robot = toRemoveRobots.GetNextRobot();
            if (dead_robot)
            {
                ptr_battlefield->removeRobot(dead_robot);
            }
        }

        // Re-add live robots back to the main list
        while (!tempRobots.IsEmpty())
        {
            Robot *temp_robot = tempRobots.GetNextRobot();
            if (!temp_robot)
            {
                cerr << "Error: temp_robot is nullptr!" << endl;
                break;
            }

            if (temp_robot->isAlive())
            {
                ptr_robots->AddRobot(temp_robot);
            }
        }

        // Handle robot removal and respawn
        if (!ptr_battlefield->getReEntryQueue().isEmpty() && !respawnedThisStep)
        {
            Robot *robot = ptr_battlefield->getReEntryQueue().dequeue();
            if (robot && robot->getLives() > 0) // Check if the robot still has lives left
            {
                cout << "Dequeued robot: " << robot->getType() << " for respawn" << endl;
                logFile << "Dequeued robot: " << robot->getType() << " for respawn" << endl;
                ptr_battlefield->respawnRobot(robot);
                ptr_robots->AddRobot(robot); // Ensure the respawned robot is added back to the active list
                respawnedThisStep = true;    // Only allow one respawn per step
            }
        }

        cout << "End of step " << step + 1 << endl;
        logFile << "End of step " << step + 1 << endl;
        logFile.flush();
        // Print sizes of the lists
        ptr_battlefield->printSizes();

        // Display current stats
        DisplayStats();

        cout << endl
             << endl;

        // Check if only one robot has lives greater than 0
        if (ptr_battlefield->countRobotsWithLives() == 1)
        {
            Robot *winner = ptr_battlefield->getRobotWithLives();
            if (winner)
            {
                cout << "Winner: " << winner->getType() << " (" << winner->getName() << ")" << endl;
                logFile << "Winner: " << winner->getType() << " (" << winner->getName() << ")" << endl;
                break;
            }
        }
        LogStats();

        // Reset the upgraded_this_turn flag for all robots
        ptr_robots->resetUpgradeFlags();
    }
}

void Simulation::UpgradeRobot(Robot *oldRobot)
{
    Robot *newRobot = nullptr;

    // Determine the type of the old robot and create the upgraded version
    if (dynamic_cast<Terminator *>(oldRobot))
    {
        newRobot = new TerminatorRoboCop(oldRobot->getName(), oldRobot->getX(), oldRobot->getY(), ptr_battlefield);
    }
    else if (dynamic_cast<BlueThunder *>(oldRobot))
    {
        newRobot = new MadBot(oldRobot->getName(), oldRobot->getX(), oldRobot->getY(), ptr_battlefield);
    }
    else if (dynamic_cast<MadBot *>(oldRobot))
    {
        newRobot = new RoboTank(oldRobot->getName(), oldRobot->getX(), oldRobot->getY(), ptr_battlefield);
    }
    else if (dynamic_cast<RoboCop *>(oldRobot))
    {
        newRobot = new TerminatorRoboCop(oldRobot->getName(), oldRobot->getX(), oldRobot->getY(), ptr_battlefield);
    }
    else if (dynamic_cast<TerminatorRoboCop *>(oldRobot))
    {
        newRobot = new UltimateRobot(oldRobot->getName(), oldRobot->getX(), oldRobot->getY(), ptr_battlefield);
    }
    else if (dynamic_cast<RoboTank *>(oldRobot))
    {
        newRobot = new UltimateRobot(oldRobot->getName(), oldRobot->getX(), oldRobot->getY(), ptr_battlefield);
    }

    if (newRobot != nullptr)
    {
        ptr_robots->RemoveRobot(oldRobot);
        ptr_robots->AddRobot(newRobot);
        ptr_battlefield->removeRobot(oldRobot);
        ptr_battlefield->addRobot(newRobot);
        ptr_battlefield->UpdatePosition(newRobot->getX(), newRobot->getY(), newRobot->getName()[0]);
        ptr_battlefield->Display();
        cout << oldRobot->getType() << " has been upgraded to " << newRobot->getType() << "!" << endl;
        logFile << oldRobot->getType() << " has been upgraded to " << newRobot->getType() << "!" << endl;
    }
    else
    {
        std::cerr << "Error: Failed to upgrade robot " << oldRobot->getType() << std::endl;
    }
}

void Simulation::DisplayStats()
{
    RobotNode *current = ptr_battlefield->getRobots().getHead();
    cout << "\nCurrent Stats:\n";
    while (current != nullptr)
    {
        Robot *robot = current->robot;
        cout << robot->getName() << " (" << robot->getType() << ") - Lives: " << robot->getLives() << " - Kills: " << robot->getKills() << "\n";
        current = current->next;
    }
    cout << endl;
}

void Simulation::LogStats()
{
    if (!logFile.is_open())
    {
        cerr << "Log file is not open." << endl;
        return;
    }

    logFile << "\nFinal Stats:\n";
    RobotNode *current = ptr_battlefield->getRobots().getHead();
    while (current != nullptr)
    {
        Robot *robot = current->robot;
        logFile << robot->getName() << " (" << robot->getType() << ") - Lives: " << robot->getLives() << " - Kills: "
                << robot->getKills() << "\n";
        current = current->next;
    }

    logFile.flush();
}
