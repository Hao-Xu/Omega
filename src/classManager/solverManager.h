#ifndef SOLVERMANAGER_H
#define SOLVERMANAGER_H

#include<iostream>
#include<string>

/**
 * @file solverManager.h
 * @author Hao Xu
 * @date created on 2017/07/21
 */

class solverManager {

public:
    solverManager() { std::cout << " Solver Constructor " << std::endl; }
    solverManager(int m): mm(m) { std::cout << " Solver Constructor 2: rank = " << mm << std::endl; }
    solverManager(std::string n): name(n) { std::cout << " Solver Constructor 2: name = " << name << std::endl; }
    void assign();
    void update();
    ~solverManager() { std::cout << " Solver Deconstructor " << std::endl; } 
private:
    int mm;
    std::string name;    
};


#endif    /* End of SOLVERMANAGER_H */


