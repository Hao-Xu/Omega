#ifndef MATERIALFACTORY_H
#define MATERIALFACTORY_H

#include <iostream>
#include <unordered_map>
#include <functional>
#include <vector>
#include "material.h"

// Factory class
class materialFactory {
    public:
        typedef std::unordered_map<std::string, std::function<material*()>> registry_map;

    // use this to instantiate the proper Derived class
        static material * instantiate(const std::string& name) {
    
            auto it = materialFactory::registry().find(name);
            return it == materialFactory::registry().end() ? nullptr : (it->second)();
        }

        static registry_map & registry() {
            static registry_map impl;
            return impl;
        }

};

template<typename T> struct materialFactoryRegister {

    materialFactoryRegister(std::string name) {
    
        materialFactory::registry()[name] = []() { return new T; };
        std::cout << "Registering class '" << name << "'\n";
    }
};

#endif
