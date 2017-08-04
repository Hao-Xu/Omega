#ifndef ISOTROPICELASTIC_H
#define ISOTROPICELASTIC_H

#include <iostream>
//#include <unordered_map>
//#include <functional>
//#include <vector>
//#include "lib/mathLib/r1Tensor.h"
#include "../../../../lib/mathLib/r1Tensor.h"
//#include "lib/mathLib/r2Tensor.h"
//#include "lib/mathLib/r3Tensor.h"
#include "material.h"
#include "materialFactory.h"

class isotropicElastic : public material {
  public:
      isotropicElastic() { std::cout << "initial isotropic elastic material " <<std::endl; }
      virtual ~isotropicElastic() {std::cout << "destroy isotropic elastic material " <<std::endl; }     
      void initialize() {}
      void assignParameter(std::string parameterName, )
      void update(); 
      void printVariables() { std::cout << "isotropic elastic model" << std::endl; }
      void draw() { 
	  test(1,2);
	  //std::cout << "drawing a circle " <<std::endl; 
      }
  private:
      int mm, nn;
      static materialFactoryRegister<isotropicElastic> AddToFactory_;
      void test(int m, int n) {
              mm = m;
              nn = n;  
	      std::cout << " mm = " << mm << std::endl; 
	      std::cout << " nn = " << nn << std::endl; 
      }
};

#endif


