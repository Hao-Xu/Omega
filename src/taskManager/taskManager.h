#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include<iostream>

class taskManager {

public:
    taskManager() {std::cout << " Constructor " << std::endl; }
    void print();
    void initialize();
    void assemble();
    void run();
    void postProcess();
    ~taskManager(){std::cout << " Deconstructor " << std::endl; } 

private:
    int mm;    
};


#endif

