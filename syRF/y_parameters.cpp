/*****************************************************************
**                                                              **
**  syRF                                                        **
**  Copyright (C) 2019-2020 Francesco Urbani                    **
**                                                              **
******************************************************************
**  Author:    Francesco Urbani <https://urbanij.github.io/>    **
**  Date:      Wed Dec 11 19:48:18 CET 2019                     **
**  File:           y_parameters.cpp                            **
**  Description:                                                **
******************************************************************/

#include "y_parameters.h"

float linear_2_dB(float x){
    return 10*log10(abs(x));
}

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


std::complex<float>
calculate_betaA(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

     std::complex<float> y_s,
     std::complex<float> y_l
){
    return ( (y_f*y_r)/( (y_i+y_s)*(y_o+y_l) ) );
}


std::complex<float>
calculate_yin(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

     // std::complex<float> y_s,
     std::complex<float> y_l
        ){
    return ( y_i - (y_r*y_f)/(y_o + y_l) );
}


std::complex<float>
calculate_yout(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

     std::complex<float> y_s
){
    return ( y_o - (y_f*y_r)/(y_i+y_s) );
}


std::complex<float>
calculate_A_V(
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_l
){
    return ( -y_f/(y_o + y_l) );
}

std::complex<float>
calculate_vout_over_vs(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

     std::complex<float> y_s,
     std::complex<float> y_l
        ){
    //change y from mS to S
    y_i *= 1e-3;
    y_f *= 1e-3;
    y_o *= 1e-3;
    y_r *= 1e-3;
    y_s *= 1e-3;
    y_l *= 1e-3;

    std::complex<float> v1_over_vs;
    std::complex<float> rs;
    std::complex<float> rl;

    if (y_s == std::complex<float>(0.0,0.0)){
        // rs -> infty
        v1_over_vs = 0.0;
    }
    else if (y_l == std::complex<float>(0.0,0.0) && abs(y_s)>0) {
        // rl -> infty
        rs = std::complex<float>(1.0,0)/y_s;
        v1_over_vs = std::complex<float>(1.0,0.0) / ( std::complex<float>(1.0,0.0) + rs*y_i - rs*y_f*y_r*(std::complex<float>(1.0,0.0)/y_o));
    }
    else{
        rs = std::complex<float>(1.0, 0.0)/y_s; // ohm
        rl = std::complex<float>(1.0,0.0)/y_l; // ohm
        v1_over_vs = ( std::complex<float>(1.0,0.0)+rl*y_o )/( (std::complex<float>(1.0,0.0)+rs*y_i)*(std::complex<float>(1.0,0.0)+rl*y_o) - y_f*y_r*rl*rs);
    }

    std::complex<float> vout_over_vs;
    vout_over_vs = calculate_A_V(y_f, y_o, y_l) * v1_over_vs;
    return vout_over_vs;
}


float
calculate_G_A(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

     std::complex<float> y_s
        )
{
    return ( pow(abs(y_f),2) * y_s.real() ) / ( (y_o*y_s + y_o*y_i - y_r*y_f)*std::conj(y_i+y_s) ).real();
}

float
calculate_G_P(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

     std::complex<float> y_l
)
{
    std::complex<float> y_in = calculate_yin(y_i, y_f, y_o, y_r, y_l);
    return ( pow(abs(y_f),2) / (pow(abs(y_o+y_l),2) ) * (y_l.real()))/(y_in.real());
}

float
calculate_G_T(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

     std::complex<float> y_s,
     std::complex<float> y_l
        )
{
    return ( 4*y_s.real()*y_l.real()* pow(abs(y_f),2))/ pow(abs((y_s+y_i)*(y_o+y_l)-y_r*y_f),2);
}


float
calculate_k(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r,

     std::complex<float> y_s,
     std::complex<float> y_l
        )
{
    return ( 2*(y_i.real()+y_s.real())*(y_o.real()+y_l.real()) )/ ( (y_r*y_f).real() + abs(y_r*y_f) );
}

float
calculate_g_s_opt(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r
)
{

    float gi = y_i.real();
    float go = y_o.real();

    return (pow(( pow(( 2*gi*go - (y_r*y_f).real() ),2) - pow((abs(y_r*y_f)),2) ),0.5))/(2*go);
}

std::complex<float>
calculate_y_s_opt(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r
)
{

    float g_s_opt = calculate_g_s_opt(y_i, y_f, y_o, y_r);
    float b_s_opt = -y_i.imag() + (y_r*y_f).imag()/(2*y_o.real());

    return std::complex<float> ( g_s_opt, b_s_opt);
}

std::complex<float>
calculate_y_l_opt(
     std::complex<float> y_i,
     std::complex<float> y_f,
     std::complex<float> y_o,
     std::complex<float> y_r
)
{
    float g_s_opt = calculate_g_s_opt(y_i, y_f, y_o, y_r);
    float g_L_opt = (g_s_opt*y_o.real())/(y_i.real());
    float b_L_opt = -y_o.imag() + (y_r*y_f).imag()/(2*y_i.real());

    return std::complex<float> (g_L_opt , b_L_opt);
}




