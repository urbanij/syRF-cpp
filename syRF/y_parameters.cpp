/***************************************************************************
**                                                                        **
**  syRF                                                                  **
**  Copyright (C) 2019 Francesco Urbani                                   **
**                                                                        **
****************************************************************************
**  Author:         Francesco Urbani <https://urbanij.github.io/>         **
**  Date:           Wed Dec 11 19:48:18 CET 2019                          **
**  File:           y_parameters.cpp                                      **
**  Description:                                                          **
****************************************************************************/

#include "y_parameters.h"

float 
compute_C(
    std::complex<float> y_i, 
    std::complex<float> y_f, 
    std::complex<float> y_o, 
    std::complex<float> y_r
)
{
    return ( abs(y_r*y_f) ) / ( 2*y_i.real()*y_o.real() - (y_r*y_f).real() );
}

