/*****************************************************************
**                                                              **
**  syRF                                                        **
**  Copyright (C) 2019-2020 Francesco Urbani                    **
**                                                              **
******************************************************************
**  Author:    Francesco Urbani <https://urbanij.github.io/>    **
**  Date:      Mon Apr 13 12:20:20 CEST 2020                    **
**  File:           s_parameters.h                              **
**  Description:                                                **
******************************************************************/

#ifndef S_PARAMETERS_H
#define S_PARAMETERS_H


#include <complex>
#include "utils.h"
#include "s_parameters.cpp"


std::complex<float>
compute_D(
    std::complex<float> s11,
    std::complex<float> s12,
    std::complex<float> s21,
    std::complex<float> s22
);

float 
calculate_K(std::complex<float> s11,
            std::complex<float> s12,
            std::complex<float> s21,
            std::complex<float> s22
            );


/////// GAMMAS ///////
std::complex<float>
calculate_gamma(std::complex<float> zl, 
                std::complex<float> z0
);

std::complex<float> 
calculate_gamma_in(std::complex<float> s11, 
                std::complex<float> s12, 
                std::complex<float> s21, 
                std::complex<float> s22, 
                std::complex<float> zl, 
                std::complex<float> z0
                );

std::complex<float> 
calculate_gamma_out(std::complex<float> s11, 
                std::complex<float> s12, 
                std::complex<float> s21, 
                std::complex<float> s22, 
                std::complex<float> zs, 
                std::complex<float> z0
                );

/////// INPUT AND OUTPUT STABILITY CIRCLES  ///////
std::pair<std::complex<float>, float>
calculate_ISC(std::complex<float> s11, 
                std::complex<float> s12, 
                std::complex<float> s21, 
                std::complex<float> s22);

std::pair<std::complex<float>, float>
calculate_OSC(std::complex<float> s11, 
                std::complex<float> s12, 
                std::complex<float> s21, 
                std::complex<float> s22);


/////// GAINS ///////
float
calculate_GP(std::complex<float> s11, 
                std::complex<float> s12, 
                std::complex<float> s21, 
                std::complex<float> s22, 
                std::complex<float> zl, 
                std::complex<float> z0
                );
float
calculate_GT(std::complex<float> s11, 
                std::complex<float> s12, 
                std::complex<float> s21, 
                std::complex<float> s22, 
                std::complex<float> zs, 
                std::complex<float> zl, 
                std::complex<float> z0
                );
float
calculate_GA(std::complex<float> s11, 
                std::complex<float> s12, 
                std::complex<float> s21, 
                std::complex<float> s22, 
                std::complex<float> zs, 
                std::complex<float> z0
                );


float
calculate_NF(float              NFmin_db, 
            float               Rn, 
            std::complex<float> gamma_s_on, 
            float               zs, 
            float               z0);








#endif // S_PARAMETERS_H
