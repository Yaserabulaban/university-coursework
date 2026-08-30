/**********|**********|**********|
Program: RobotQueue.h
Course: OOPDS
Trimester: 2410
Name: Yaser E H Abulaban, Chua Xin Lin, Chiew Shuye, How Wen Ting
ID: 1221305612, 1211110742, 1211110531, 1211109696
Lecture Section: TC2L
Tutorial Section: TT8L
Email: 12213056@student.mmu.edu.my - 1211110742@student.mmu.edu.my - 1211110531@student.mmu.edu.my -  1211109696@student.mu.edu.my
Phone: 017-7039024 , 018-9779813, 011-20502377, 019-6572791
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
