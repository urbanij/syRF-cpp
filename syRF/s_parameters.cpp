/***************************************************************************
**                                                                        **
**  syRF                                                                  **
**  Copyright (C) 2019-2020 Francesco Urbani                              **
**                                                                        **
****************************************************************************
**  Author:         Francesco Urbani <https://urbanij.github.io/>         **
**  Date:           Mon Apr 13 12:20:20 CEST 2020                         **
**  File:           s_parameters.cpp                                      **
**  Description:                                                          **
****************************************************************************/

#include "s_parameters.h"

std::complex<float>
compute_D(std::complex<float> s11,
        std::complex<float> s12,
        std::complex<float> s21,
        std::complex<float> s22
){
    return (s11*s22 - s12*s21);
}


float 
calculate_K(std::complex<float> s11,
            std::complex<float> s12,
            std::complex<float> s21,
            std::complex<float> s22
            )
{
    std::complex<float> D = compute_D(s11, s12, s21, s22);
    return (1-pow(abs(s11),2) - pow(abs(s22),2) + pow(abs(D),2)) / (2*abs(s12*s21));
}

std::complex<float>
calculate_gamma(std::complex<float> zl, 
                std::complex<float> z0
){
    return (zl-z0)/(zl+z0);
}

