/***************************************************************************
**                                                                        **
**  syRF                                                                  **
**  Copyright (C) 2019 Francesco Urbani                                   **
**                                                                        **
****************************************************************************
**  Author:         Francesco Urbani <https://urbanij.github.io/>         **
**  Date:           Wed Dec 11 19:48:18 CET 2019                          **
**  File:           y_parameters.h                                        **
**  Description:                                                          **
****************************************************************************/

#ifndef Y_PARAMETERS_H
#define Y_PARAMETERS_H

#include <complex>
#include "y_parameters.cpp"


float
compute_C(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r
);


std::complex<float>
calculate_betaA(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

     std::complex<float> y_s,
     std::complex<float> y_l
);


std::complex<float>
calculate_yin(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

//     std::complex<float> y_s,
     std::complex<float> y_l
);


std::complex<float>
calculate_yout(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

     std::complex<float> y_s,
     std::complex<float> y_l
);


std::complex<float>
calculate_A_V(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

     std::complex<float> y_s
//     std::complex<float> y_l
);

std::complex<float>
calculate_vout_over_vs(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

     std::complex<float> y_s,
     std::complex<float> y_l
);

float
calculate_G_A(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

     std::complex<float> y_s,
     std::complex<float> y_l
);

float
calculate_G_P(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

//     std::complex<float> y_s,
     std::complex<float> y_l
);

float
calculate_G_T(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

     std::complex<float> y_s,
     std::complex<float> y_l
);


float
calculate_k(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

     std::complex<float> y_s,
     std::complex<float> y_l
);

float
calculate_g_s_opt(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

     std::complex<float> y_s,
     std::complex<float> y_l
);

std::complex<float>
calculate_y_s_opt(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

     std::complex<float> y_s,
     std::complex<float> y_l
);

std::complex<float>
calculate_y_l_opt(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

     std::complex<float> y_s,
     std::complex<float> y_l
);


#endif // Y_PARAMETERS_H
