#include "isotropicElastic.h"

// public method
void isotropicElastic::update(r1Tensor<double> & strainInc, 
		r1Tensor<double> & stressInc, r1Tensor<double> & Stress) {
              
    int ntens = stiffness.dim1();
    for (int i = 0; i < ntens; i++) {
        dSig[i] = 0.;
        for (int j = 0; j < ntens; j++) {
            if (j < 3) {
                dSig[i] += stiffness[i][j] * dStran[j];
            } else {
                dSig[i] += 2. * stiffness[i][j] * dStran[j];
            }
        }
    }
    for (int i = 0; i < ntens; i++) {
        Stress[i] += dSig[i];
    }
}

// private method
void isotropicElastic::assembleStiffness() {
    double temp;
    temp = youngsModulus / (1. + poissonsRatio) / (1. - 2. * poissonsRatio);

    stiffness[0][0] = temp * (1. - poissonsRatio);
    stiffness[0][1] = temp * poissonsRatio;
    stiffness[0][2] = stiffness[0][1];

    stiffness[1][0] = stiffness[0][1];
    stiffness[1][1] = stiffness[0][0];
    stiffness[1][2] = stiffness[0][1];

    stiffness[2][0] = stiffness[0][1];
    stiffness[2][1] = stiffness[0][1];
    stiffness[2][2] = stiffness[0][0];

    stiffness[3][3] = temp * (1. - 2. * poissonsRatio) / 2.;
    stiffness[4][4] = stiffness[3][3];
    stiffness[5][5] = stiffness[4][4];
}

materialFactoryRegister<isotropicElastic> isotropicElastic::AddToFactory_("isotropicElastic" );
