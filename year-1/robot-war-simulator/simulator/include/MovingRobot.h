/**********|**********|**********|
Program: MovingRobot.h
**********|**********|**********/

#ifndef MOVINGROBOT_H
#define MOVINGROBOT_H

#include "Robot.h"
#include<string>

class MovingRobot : virtual public Robot{
public:
    MovingRobot(string type, string name, int x, int y, Battlefield *ptrbattlefield);
    virtual void Move(int m,int n) ;
};
#endif