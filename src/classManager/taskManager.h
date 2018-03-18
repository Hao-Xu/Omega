/**
 * \file taskManager.h
 * \author Hao Xu
 * \date created on 2017/07/21
 */

//
//  taskManager handles the problem.
//
#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <iostream>
#include <vector>
#include <getopt.h>
#include "mpi.h"
#include "tinyxml2/tinyxml2.h"
#include "elementManager.h"
#include "constitutive/material.h"
#include "constitutive/materialFactory.h"
#include "materialManager.h"
#include "solverManager.h"

class taskManager {

public:
    taskManager() {}
    taskManager(int m): mm(m) {}
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
    //std::string inputFile;
    const char * inputFile;
    std::string materialName;
    //std::vector<int> elementList;
    std::vector<material*> materialList;
    std::vector<elementManager *> elementList;
    void MPISetup(int &argc, char ** &argv);
    int readXML(int &argc, char ** &argv);
};


#endif

