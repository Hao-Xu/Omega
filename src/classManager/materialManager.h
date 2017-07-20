#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include<iostream>
#include<string>

class materialManager {

public:
    materialManager() { std::cout << " Material Constructor " << std::endl; }
    materialManager(int m): mm(m) { std::cout << " Material Constructor 2: rank = " << mm << std::endl; }
    materialManager(std::string n): name(n) { std::cout << " Material Constructor 2: name = " << name << std::endl; }
    void assign();
    void update();
    ~materialManager() { std::cout << " Material Deconstructor " << std::endl; } 
private:
    int mm;
    std::string name;    
};


#endif    /* End of MATERIALMANAGER_H */


