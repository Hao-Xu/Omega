#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include<iostream>
#include<vector>

#ifdef HAVE_MPI
#include "mpi.h"
#endif
#include "tinyxml2/tinyxml2.h"
#include "elementManager.h"
#include "solverManager.h"

class taskManager {

public:
    taskManager() { std::cout << " Constructor " << std::endl; }
    taskManager(int m): mm(m) { std::cout << " Constructor 2: rank = " << mm << std::endl; }
    void print();
    void initialize(int & argc, char ** &argv);
    void assemble();
    void run();
    void postProcess();
    ~taskManager() { std::cout << " Deconstructor " << std::endl; } 

private:
    int mm;    
    int  numtasks, rank, len, rc; 
    char hostname[MPI_MAX_PROCESSOR_NAME];
    //std::vector<int> elementList;
    std::vector<elementManager *> elementList;
};


#endif

