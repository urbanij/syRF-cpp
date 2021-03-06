/*****************************************************************
**                                                              **
**  syRF                                                        **
**  Copyright (C) 2019-2020 Francesco Urbani                    **
**                                                              **
******************************************************************
**  Author:    Francesco Urbani <https://urbanij.github.io/>    **
**  Date:      Wed Dec 11 19:48:18 CET 2019                     **
**  File:           y_parameters.h                              **
**  Description:                                                **
******************************************************************/

#ifndef Y_PARAMETERS_H
#define Y_PARAMETERS_H

#include <complex>
#include "utils.h"

double
linear_2_dB(double x);


double
compute_C(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r
);


complex_t
calculate_betaA(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r,

     complex_t y_s,
     complex_t y_l
);


complex_t
calculate_yin(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r,

     complex_t y_l
);


complex_t
calculate_yout(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r,

     complex_t y_s
);


complex_t
calculate_A_V(
     complex_t y_f,
     complex_t y_o,
     complex_t y_l
);

complex_t
calculate_vout_over_vs(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r,

     complex_t y_s,
     complex_t y_l
);

double
calculate_G_A(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r,

     complex_t y_s
);

double
calculate_G_P(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r,

     complex_t y_l
);

double
calculate_G_T(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r,

     complex_t y_s,
     complex_t y_l
);


double
calculate_k(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r,

     complex_t y_s,
     complex_t y_l
);

double
calculate_g_s_opt(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r
);

complex_t
calculate_y_s_opt(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r
);

complex_t
calculate_y_l_opt(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r
);


#endif // Y_PARAMETERS_H
