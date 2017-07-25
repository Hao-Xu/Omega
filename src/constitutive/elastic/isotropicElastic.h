// isotropicElastic.h
//   An isotropic elastic model.
// History:
// 2017/07/21  Hao Xu   First release 

#ifndef ISOTROPICELASTIC_H
#define ISOTROPICELASTIC_H

//#include "../mathLib/arithmetic.h"
#include "lib/mathLib/r1Tensor.h"
#include "lib/mathLib/r2Tensor.h"
#include "lib/mathLib/r3Tensor.h"
//#include "../mathLib/errInfo.h"
//#include "../mathLib/gaussj.h"
//#include "../mathLib/eigen.h"

/**
 * @file isotropicElastic.h
 * @author Hao Xu
 * @date created on 2017/07/21
 */

class isotropicElastic : public materialManager {
    public:
      // Creators
      isotropicElastic(double youngsModulus, double poissonsRatio);
      void update(r1Tensor<double> & strainInc, r1Tensor<double> & stressInc); 
      void printVariables(); 

    private:
      double bulkModulus,shearModulus,youngsModulus,poissonsRatio;

      r2Tensor<double> stiffness;
      r1Tensor<double> dstran,Stress,dSig;
};

#endif 
