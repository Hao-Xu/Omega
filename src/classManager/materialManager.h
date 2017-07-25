#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include<iostream>
#include<string>

/**
 * @file materialManager.h
 * @author Hao Xu
 * @date created on 2017/07/21
 */

class materialManager {

public:
    materialManager() { std::cout << " Material Constructor " << std::endl; }
    materialManager(int m): mm(m) { std::cout << " Material Constructor 2: rank = " << mm << std::endl; }
    materialManager(std::string n): name(n) { std::cout << " Material Constructor 2: name = " << name << std::endl; }
    void assign();
    virtual void update();
    virtual ~materialManager() { std::cout << " Material Deconstructor " << std::endl; } 
private:
    int mm;
    std::string name;    
};


#endif    /* End of MATERIALMANAGER_H */


