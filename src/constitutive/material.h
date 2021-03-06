#ifndef MATERIAL_H
#define MATERIAL_H
#include <iostream>
//#include <unordered_map>
//#include <functional>
//#include <vector>
#include <string>

// Base class
class material {
    public:
        material() { std::cout << " construct material " << std::endl; }
        virtual ~material() { std::cout << " delete material " << std::endl; }
        virtual void initialize() {}
        virtual void update() {}
        virtual void printVariables() { 
            std::cout << " material base " << std::endl; }
        virtual void draw() = 0;
    private:
        std::string name;
	int mm, nn;
    protected:
	std::string protected_name;
	int protected_mm, protected_nn;
	bool elastic;
};

#endif
