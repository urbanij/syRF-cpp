/***************************************************************************
**                                                                        **
**  syRF                                                                  **
**  Copyright (C) 2019-2020 Francesco Urbani                              **
**                                                                        **
****************************************************************************
**  Author:         Francesco Urbani <https://urbanij.github.io/>         **
**  Date:           Mon Apr 13 12:20:20 CEST 2020                         **
**  File:           s_parameters.h                                        **
**  Description:                                                          **
****************************************************************************/

#ifndef S_PARAMETERS_H
#define S_PARAMETERS_H


#include <complex>
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


std::complex<float>
calculate_gamma(
    std::complex<float> zl, 
    std::complex<float> z0
);



#endif // S_PARAMETERS_H
