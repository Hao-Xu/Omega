#ifndef ISOTROPICELASTIC_H
#define ISOTROPICELASTIC_H

#include <iostream>
//#include <unordered_map>
//#include <functional>
//#include <vector>
#include "lib/mathLib/r1Tensor.h"
#include "lib/mathLib/r2Tensor.h"
//#include "lib/mathLib/r3Tensor.h"
#include "constitutive/material.h"
#include "constitutive/materialFactory.h"

class isotropicElastic : public material {
  public:
      isotropicElastic(): youngsModulus(0.), poissonsRatio(0.),
                         stiffness(6, 6, 0.) {}
      isotropicElastic(double E, double nu):
                      youngsModulus(E), poissonsRatio(nu) {}
      virtual ~isotropicElastic() {}     
      void initialize() {}
      void assignParameter(std::string parameterName) {}
      void update(r1Tensor<double> & strainInc, r1Tensor<double> & stressInc, 
                  r1Tensor<double> & Stress); 
      void printVariables() { std::cout << "isotropic elastic model" << std::endl; }
      void draw() {}
      
  private:
      int mm, nn, dimension;
      double bulkModulus, shearModulus, youngsModulus, poissonsRatio;
      r1Tensor<double> dStran, Stress, dSig;
      r2Tensor<double> stiffness; 
      void assembleStiffness();
      static materialFactoryRegister<isotropicElastic> AddToFactory_;
};

#endif


