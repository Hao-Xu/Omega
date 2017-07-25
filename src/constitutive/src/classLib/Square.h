
#include <iostream>
//#include <unordered_map>
//#include <functional>
//#include <vector>
#include "material.h"
#include "materialFactory.h"


class Square : public material {
  public:
    void draw() {  std::cout << "drawing a square " <<std::endl;  }
  private:
    static materialFactoryRegister<Square> AddToFactory_;
};

materialFactoryRegister<Square> Square::AddToFactory_("Square" );


