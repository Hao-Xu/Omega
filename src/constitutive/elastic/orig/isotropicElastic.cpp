// isotropicElastic.cpp
// subroutine:
//   An isotropic elastic model.
// History:
// 2017/07/21  Hao Xu   First release 

#include "isotropicElastic.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <complex>
#include <assert.h>
#include "lib/mathLib/arithmetic.h"
#include "lib/mathLib/r1Tensor.h"
#include "lib/mathLib/r2Tensor.h"
#include "lib/mathLib/errInfo.h"



void assembleStiffness(r2Tensor<double> &stiffness, const double & E0_, const double & Poisson0_);

//--------------------------------------------------------------------------

isotropicElastic::isotropicElastic(double E0, double Poisson0):
               youngsModulus(E0),poissonsRatio(Poisson0),
               stiffness(6,6,0.),
               dstran(6,0.),Stress(6,0.),dSig(6,0.) {}


void isotropicElastic::run(r1Tensor<double> & strainInc) {

    int ntens = Omega.size();
        
    assembleStiffness(stiffness, youngsModulus, poissonsRatio);

    for (int i = 0; i < ntens; i++) {
        dSig[i] = 0.;
        for (int j = 0; j < ntens; j++) {
                
            if (j < 3) {
                dSig[i] += stiffness[i][j] * strainInc[j];
             
            } else {
                dSig[i] += 2. * stiffness[i][j] * strainInc[j];
            }
        }
   }

   for (int i = 0; i < ntens; i++) {
       Stress[i] += dSig[i];
   }

}

void isotropicElastic::printVariables() {
    cout << " E0       = " << youngsModulus << endl;
    cout << " Poisson0 = " << poissonsRatio << endl;
}

void assembleStiffness(r2Tensor<double> &stiffness, const double & E0_,
                        const double & Poisson0_){
                       
    int ntens = stiffness.dim1();
    double b1;
    
    b1 = youngsModulus / (1. + poissonsRatio) / (1. - 2. * poissonsRatio);

    stiffness[0][0] = b1 * (1. - poissonsRatio);
    stiffness[0][1] = b1 * poissonsRatio;
    stiffness[0][2] = stiffness[0][1];

    stiffness[1][0] = stiffness[0][1];
    stiffness[1][1] = stiffness[0][0];
    stiffness[1][2] = stiffness[0][1];

    stiffness[2][0] = stiffness[0][1];
    stiffness[2][1] = stiffness[0][1];
    stiffness[2][2] = stiffness[0][0];

    stiffness[3][3] = b1 * (1. - 2. * poissonsRatio) / 2.;
    stiffness[4][4] = stiffness[3][3];
    stiffness[5][5] = stiffness[4][4];
     
}

