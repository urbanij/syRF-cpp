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


float 
compute_C(
    complex_t y_i, 
    complex_t y_f, 
    complex_t y_o, 
    complex_t y_r
)
{
    return ( abs(y_r*y_f) ) / ( 2*y_i.real()*y_o.real() - (y_r*y_f).real() );
}


complex_t
calculate_betaA(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r,

     complex_t y_s,
     complex_t y_l
){
    return ( (y_f*y_r)/( (y_i+y_s)*(y_o+y_l) ) );
}


complex_t
calculate_yin(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r,

     // complex_t y_s,
     complex_t y_l
        ){
    return ( y_i - (y_r*y_f)/(y_o + y_l) );
}


complex_t
calculate_yout(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r,

     complex_t y_s
){
    return ( y_o - (y_f*y_r)/(y_i+y_s) );
}


complex_t
calculate_A_V(
     complex_t y_f,
     complex_t y_o,
     complex_t y_l
){
    return ( -y_f/(y_o + y_l) );
}

complex_t
calculate_vout_over_vs(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r,

     complex_t y_s,
     complex_t y_l
        ){
    //change y from mS to S
    y_i *= 1e-3;
    y_f *= 1e-3;
    y_o *= 1e-3;
    y_r *= 1e-3;
    y_s *= 1e-3;
    y_l *= 1e-3;

    complex_t v1_over_vs;
    complex_t rs;
    complex_t rl;

    if (y_s == complex_t(0.0,0.0)){
        // rs -> infty
        v1_over_vs = 0.0;
    }
    else if (y_l == complex_t(0.0,0.0) && abs(y_s)>0) {
        // rl -> infty
        rs = complex_t(1.0,0)/y_s;
        v1_over_vs = complex_t(1.0,0.0) / ( complex_t(1.0,0.0) + rs*y_i - rs*y_f*y_r*(complex_t(1.0,0.0)/y_o));
    }
    else{
        rs = complex_t(1.0, 0.0)/y_s; // ohm
        rl = complex_t(1.0,0.0)/y_l; // ohm
        v1_over_vs = ( complex_t(1.0,0.0)+rl*y_o )/( (complex_t(1.0,0.0)+rs*y_i)*(complex_t(1.0,0.0)+rl*y_o) - y_f*y_r*rl*rs);
    }

    complex_t vout_over_vs;
    vout_over_vs = calculate_A_V(y_f, y_o, y_l) * v1_over_vs;
    return vout_over_vs;
}


float
calculate_G_A(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r,

     complex_t y_s
        )
{
    return ( pow(abs(y_f),2) * y_s.real() ) / ( (y_o*y_s + y_o*y_i - y_r*y_f)*std::conj(y_i+y_s) ).real();
}

float
calculate_G_P(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r,

     complex_t y_l
)
{
    complex_t y_in = calculate_yin(y_i, y_f, y_o, y_r, y_l);
    return ( pow(abs(y_f),2) / (pow(abs(y_o+y_l),2) ) * (y_l.real()))/(y_in.real());
}

float
calculate_G_T(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r,

     complex_t y_s,
     complex_t y_l
        )
{
    return ( 4*y_s.real()*y_l.real()* pow(abs(y_f),2))/ pow(abs((y_s+y_i)*(y_o+y_l)-y_r*y_f),2);
}


float
calculate_k(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r,

     complex_t y_s,
     complex_t y_l
        )
{
    return ( 2*(y_i.real()+y_s.real())*(y_o.real()+y_l.real()) )/ ( (y_r*y_f).real() + abs(y_r*y_f) );
}

float
calculate_g_s_opt(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r
)
{

    float gi = y_i.real();
    float go = y_o.real();

    return (pow(( pow(( 2*gi*go - (y_r*y_f).real() ),2) - pow((abs(y_r*y_f)),2) ),0.5))/(2*go);
}

complex_t
calculate_y_s_opt(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r
)
{

    float g_s_opt = calculate_g_s_opt(y_i, y_f, y_o, y_r);
    float b_s_opt = -y_i.imag() + (y_r*y_f).imag()/(2*y_o.real());

    return complex_t ( g_s_opt, b_s_opt);
}

complex_t
calculate_y_l_opt(
     complex_t y_i,
     complex_t y_f,
     complex_t y_o,
     complex_t y_r
)
{
    float g_s_opt = calculate_g_s_opt(y_i, y_f, y_o, y_r);
    float g_L_opt = (g_s_opt*y_o.real())/(y_i.real());
    float b_L_opt = -y_o.imag() + (y_r*y_f).imag()/(2*y_i.real());

    return complex_t (g_L_opt , b_L_opt);
}




