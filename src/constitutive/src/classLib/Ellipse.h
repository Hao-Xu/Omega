
#include <iostream>
//#include <unordered_map>
//#include <functional>
//#include <vector>
#include "material.h"
#include "materialFactory.h"

class Ellipse : public material {
  public:
        virtual ~Ellipse() { std::cout << "delete ellipse" <<std::endl; }	  
    void draw() {  std::cout << "drawing an ellipse " <<std::endl;  }
  private:
    static materialFactoryRegister<Ellipse> AddToFactory_;
};

materialFactoryRegister<Ellipse> Ellipse::AddToFactory_("Ellipse" );

