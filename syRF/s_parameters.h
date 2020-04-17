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


complex_t
compute_D(complex_t s11,
        complex_t s12,
        complex_t s21,
        complex_t s22);

float
calculate_K(complex_t s11,
            complex_t s12,
            complex_t s21,
            complex_t s22);


/////// GAMMAS ///////
complex_t
calculate_gamma(complex_t zl,
                complex_t z0);

complex_t
calculate_gamma_in(complex_t s11,
                complex_t s12,
                complex_t s21,
                complex_t s22,
                complex_t zl,
                complex_t z0);

complex_t
calculate_gamma_out(complex_t s11,
                complex_t s12,
                complex_t s21,
                complex_t s22,
                complex_t zs,
                complex_t z0);

/////// INPUT AND OUTPUT STABILITY CIRCLES  ///////



std::pair<complex_t, float>
calculate_ISC(complex_t s11,
                complex_t s12,
                complex_t s21,
                complex_t s22);

std::pair<complex_t, float>
calculate_OSC(complex_t s11,
                complex_t s12,
                complex_t s21,
                complex_t s22);

/////// GAINS ///////
float
calculate_GP(complex_t s11,
                complex_t s12,
                complex_t s21,
                complex_t s22,
                complex_t zl,
                complex_t z0
                );
float
calculate_GT(complex_t s11,
                complex_t s12,
                complex_t s21,
                complex_t s22,
                complex_t zs,
                complex_t zl,
                complex_t z0
                );
float
calculate_GA(complex_t s11,
                complex_t s12,
                complex_t s21,
                complex_t s22,
                complex_t zs,
                complex_t z0
                );


float
calculate_NF(float      NFmin_db,
            float       Rn,
            complex_t   gamma_s_on,
            float       zs,
            float       z0);


float
calculate_Ni(float NF_dB,
            float NFmin_db,
            complex_t gamma_s_on,
            float Rn,
            float z0);

std::pair<complex_t, float>
calculate_NF_circle(complex_t s11,
                    complex_t s12,
                    complex_t s21,
                    complex_t s22,
                    float   z0,
                    float   NF_circle_dB,
                    complex_t gamma_s_on,
                    float NF_opt_dB,
                    float Rn);

std::pair<complex_t, float>
calculate_GA_circle(complex_t s11,
                    complex_t s12,
                    complex_t s21,
                    complex_t s22,
                    float     Ga_circle_dB);


std::pair<complex_t, float>
calculate_GP_circle(complex_t s11,
                    complex_t s12,
                    complex_t s21,
                    complex_t s22,
                    float     Gp_circle_dB);


float
calculate_GTi(float Gt_circle_dB,
                    complex_t s11,
                    complex_t s21,
                    complex_t zs,
                    float z0);

std::pair<complex_t, float>
calculate_GT_circle(complex_t s11,
                    complex_t s12,
                    complex_t s21,
                    complex_t s22,
                    complex_t zs,
                    complex_t zl,
                    float z0,
                    float Gt_circle_dB);









#endif // S_PARAMETERS_H
