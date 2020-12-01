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


complex_t compute_D(complex_t s11,
                    complex_t s12,
                    complex_t s21,
                    complex_t s22);

double calculate_K(complex_t s11,
                    complex_t s12,
                    complex_t s21,
                    complex_t s22);


/////// GAMMAS ///////
complex_t
z2gamma(complex_t zl,
        complex_t z0);

complex_t
gamma2z(complex_t gamma,
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



std::pair<complex_t, double>
calculate_ISC(complex_t s11,
                complex_t s12,
                complex_t s21,
                complex_t s22);

std::pair<complex_t, double>
calculate_OSC(complex_t s11,
                complex_t s12,
                complex_t s21,
                complex_t s22);

/////// GAINS ///////
double
calculate_GP(complex_t s11,
                complex_t s12,
                complex_t s21,
                complex_t s22,
                complex_t zl,
                complex_t z0);
                
double
calculate_GT(complex_t s11,
                complex_t s12,
                complex_t s21,
                complex_t s22,
                complex_t zs,
                complex_t zl,
                complex_t z0);

double
calculate_GA(complex_t s11,
                complex_t s12,
                complex_t s21,
                complex_t s22,
                complex_t zs,
                complex_t z0);


double
calculate_NF(double      NFmin_db,
            double       Rn,
            complex_t   gamma_s_on,
            complex_t   zs,
            double       z0);


std::pair<complex_t, double>
calculate_NF_circle(complex_t s11,
                    complex_t s12,
                    complex_t s21,
                    complex_t s22,
                    double   z0,
                    double   NF_circle_dB,
                    complex_t gamma_s_on,
                    double NF_opt_dB,
                    double Rn);

std::pair<complex_t, double>
calculate_GA_circle(complex_t s11,
                    complex_t s12,
                    complex_t s21,
                    complex_t s22,
                    double     Ga_circle_dB);


std::pair<complex_t, double>
calculate_GP_circle(complex_t s11,
                    complex_t s12,
                    complex_t s21,
                    complex_t s22,
                    double     Gp_circle_dB);



std::pair<complex_t, double>
calculate_GT_circle(complex_t s11,
                    complex_t s12,
                    complex_t s21,
                    complex_t s22,
                    complex_t zs,
                    complex_t zl,
                    double z0,
                    double Gt_circle_dB);

complex_t
calculate_gamma_S_opt(complex_t s11,
                    complex_t s12,
                    complex_t s21,
                    complex_t s22);

complex_t
calculate_gamma_L_opt(complex_t s11,
                    complex_t s12,
                    complex_t s21,
                    complex_t s22);





#endif // S_PARAMETERS_H
