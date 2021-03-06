//
//  shapeFunctionManager.
//
#ifndef SHAPEFUNCTIONMANAGER_H
#define SHAPEFUNCTIONMANAGER_H

#include <iostream>
#include <vector>
#include <getopt.h>
//#include "mpi.h"
//#include "tinyxml2/tinyxml2.h"
//#include "elementManager.h"
//#include "constitutive/material.h"
//#include "constitutive/materialFactory.h"
//#include "materialManager.h"
//#include "solverManager.h"

/**
 * \file shapeFunctionManager.h
 * \author Hao Xu
 * \date created on 2018/02/09
 */

class shapeFunctionManager {

public:
    shapeFunctionManager() {}
    taskManager(int m): mm(m) { std::cout << " Task Constructor 2: rank = " << mm << std::endl; }
    void print();
    void initialize(int &argc, char ** &argv);
    void getOptions(int &argc, char ** &argv);
    void assemble();
    void run();
    void postProcess();
    ~taskManager() {} 

private:
    int mm;    
    int  numtasks, rank, len, rc; 
    char hostname[MPI_MAX_PROCESSOR_NAME];
    std::string inputFile;
    //std::vector<int> elementList;
    std::vector<material*> materialList;
    std::vector<elementManager *> elementList;
    void MPISetup(int &argc, char ** &argv);
    void readXML(int &argc, char ** &argv);
};


#endif

