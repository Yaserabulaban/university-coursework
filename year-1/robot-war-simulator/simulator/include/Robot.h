/**********|**********|**********|
Program: Robot.h
**********|**********|**********/

#ifndef ROBOT_H
#define ROBOT_H

#include <string>
using namespace std;
class Battlefield;

class Robot
{
protected:
    string name;
    string type;
    int x, y, lives;
    Battlefield *ptrBattlefield;
    bool status = true; // Add status attribute
    bool upgradedThisTurn;

public:
    Robot(string type, string name, int x, int y, Battlefield *ptrBattlefield);
    virtual ~Robot() = default;

    string getName() const { return name; }
    string getType() const { return type; }
    int getX() const { return x; }
    int getY() const { return y; }
    int getLives() const { return lives; }
    void decreaseLife();
    void respawn();
    void markDead() { status = false; }     // Add method to mark as dead
    void markAlive() { status = true; }     // Add method to mark as alive
    virtual bool shouldUpgrade() const = 0; // Pure virtual function for upgrade check
    bool isAlive() const;
    virtual int getKills() const { return 0; } // Default implementation
    bool isUpgradedThisTurn() const { return upgradedThisTurn; }
    void setUpgradedThisTurn(bool status) { upgradedThisTurn = status; }
    void resetUpgradedThisTurn() { upgradedThisTurn = false; }
};

#endif
