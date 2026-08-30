/**********|**********|**********|
Program: RobotQueue.h
**********|**********|**********/

#ifndef ROBOTQUEUE_H
#define ROBOTQUEUE_H

class Robot; // Forward declaration

class RobotQueue {
private:
    struct Node {
        Robot* robot;
        Node* next;
        Node(Robot* robot) : robot(robot), next(nullptr) {}
    };
    Node* front;
    Node* rear;

public:
    RobotQueue() : front(nullptr), rear(nullptr) {}
    ~RobotQueue();
    void enqueue(Robot* robot);
    Robot* dequeue();
    bool isEmpty() const;
    int size() const;  // Function to get the size of the queue

};

#endif
