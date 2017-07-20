#ifndef ELEMENTMANAGER_H
#define ELEMENTMANAGER_H

#include<iostream>
#include<string>

class elementManager {

public:
    elementManager() { std::cout << " Element Constructor " << std::endl; }
    elementManager(int m): mm(m) { std::cout << " Element Constructor 2: rank = " << mm << std::endl; }
    elementManager(std::string n): name(n) { std::cout << " Element Constructor 2: name = " << name << std::endl; }
    void assign();
    void update();
    ~elementManager() { std::cout << " Element Deconstructor " << std::endl; } 
private:
    int mm;
    std::string name;    
};


#endif    /* End of ELEMENTMANAGER_H */


