/*****************************************************************
**                                                              **
**  syRF                                                        **
**  Copyright (C) 2019-2020 Francesco Urbani                    **
**                                                              **
******************************************************************
**  Author:    Francesco Urbani <https://urbanij.github.io/>    **
**  Date:      Mon Apr 13 12:20:20 CEST 2020                    **
**  File:           s_parameters.cpp                            **
**  Description:                                                **
******************************************************************/

#include "s_parameters.h"



complex_t
compute_D(complex_t s11,
        complex_t s12,
        complex_t s21,
        complex_t s22
){
    return (s11*s22 - s12*s21);
}


float 
calculate_K(complex_t s11,
            complex_t s12,
            complex_t s21,
            complex_t s22
            )
{
    complex_t D = compute_D(s11, s12, s21, s22);
    return (1-pow(abs(s11),2) - pow(abs(s22),2) + pow(abs(D),2)) / (2*abs(s12*s21));
}

complex_t
calculate_gamma(complex_t zl, 
                complex_t z0
){
    return (zl-z0)/(zl+z0);
}


complex_t 
calculate_gamma_in(complex_t s11, 
                complex_t s12, 
                complex_t s21, 
                complex_t s22, 
                complex_t zl, 
                complex_t z0
                )
{
    complex_t gamma_L = calculate_gamma(zl, z0);
    return ( s11 + (s12*s21*gamma_L)/(ONE_COMPLEX - s22*gamma_L) );
}

complex_t 
calculate_gamma_out(complex_t s11, 
                complex_t s12, 
                complex_t s21, 
                complex_t s22, 
                complex_t zs, 
                complex_t z0
                )
{
    complex_t gamma_S = calculate_gamma(zs, z0);
    return ( s22 + (s21*s12*gamma_S)/(ONE_COMPLEX - s11*gamma_S) );
}

std::pair<complex_t, float>
calculate_ISC(complex_t s11, 
                complex_t s12, 
                complex_t s21, 
                complex_t s22)
{
    complex_t D = compute_D(s11, s12, s21, s22);

    complex_t numerator_cs = std::conj(s11 - D*std::conj(s22));
    complex_t denumerator_cs = pow(abs(s11),2) - pow(abs(D),2);
    complex_t Cs = numerator_cs / denumerator_cs;

    float numerator_rs = abs(s12 * s21);
    float denumerator_rs = abs( pow(abs(D),2) - pow(abs(s11),2) );
    float rs = numerator_rs / denumerator_rs;

    return std::make_pair(Cs, rs);
}

std::pair<complex_t, float>
calculate_OSC(complex_t s11, 
                complex_t s12, 
                complex_t s21, 
                complex_t s22)
{

    complex_t D = compute_D(s11, s12, s21, s22);

    complex_t numerator_cl = std::conj(s22 - D*std::conj(s11));
    complex_t denumerator_cl = pow(abs(s22),2) - pow(abs(D),2);
    complex_t Cl = numerator_cl / denumerator_cl;

    float numerator_rl = abs(s12 * s21);
    float denumerator_rl = abs( pow(abs(D),2) - pow(abs(s22),2) );
    float rl = numerator_rl / denumerator_rl;

    return std::make_pair(Cl, rl);
}

float
calculate_GP(complex_t s11, 
                complex_t s12, 
                complex_t s21, 
                complex_t s22, 
                complex_t zl, 
                complex_t z0
                )
{
    complex_t gamma_L = calculate_gamma(zl, z0);
    complex_t gamma_in = calculate_gamma_in(s11, s12, s21, s22, zl, z0);
    // page 51 ETLC disp
    return pow(abs( (s21)/(ONE_COMPLEX - s22*gamma_L) ),2) * ( (1.0 - pow(abs(gamma_L),2))/(1.0 - pow(abs(gamma_in),2)) );
}


float
calculate_GT(complex_t s11, 
                complex_t s12, 
                complex_t s21, 
                complex_t s22, 
                complex_t zs, 
                complex_t zl, 
                complex_t z0
                )
{
    complex_t gamma_S = calculate_gamma(zs, z0);
    complex_t gamma_L = calculate_gamma(zl, z0);
    complex_t gamma_out = calculate_gamma_out(s11, s12, s21, s22, zs, z0);

    float num = ( pow(abs(s21),2) ) * (1.0 - pow(abs(gamma_S),2)) * (1.0 - pow(abs(gamma_L),2));
    float denum = ( pow(abs( ONE_COMPLEX - gamma_out*gamma_L ) ,2) ) * ( pow(abs( ONE_COMPLEX - s11*gamma_S ),2) );

    return num/denum;
}

float
calculate_GA(complex_t s11, 
                complex_t s12, 
                complex_t s21, 
                complex_t s22, 
                complex_t zs, 
                complex_t z0
                )
{
    complex_t gamma_S = calculate_gamma(zs, z0);
    complex_t gamma_out = calculate_gamma_out(s11, s12, s21, s22, zs, z0);
    
    float num = (pow(abs(s21),2)) * ( 1.0 - pow(abs(gamma_S),2) );
    float denum = ( 1.0 - pow(abs(gamma_out),2) ) * ( pow( abs(ONE_COMPLEX - s11*gamma_S),2) );

    return num/denum;
}



float
calculate_NF(float              NFmin_db, 
            float               Rn, 
            complex_t gamma_s_on, 
            complex_t zs, 
            float               z0)
{
    float NFmin = dB_2_linear(NFmin_db);
    float rn = Rn/z0;
    complex_t gamma_S = calculate_gamma(zs, z0);
    
    if (abs(gamma_S) != 1){
        // from page 60 ETLC disp
        return ( NFmin + (4 * rn * (pow( (abs(gamma_S - gamma_s_on)) ,2)) )/( (1.0 - pow(abs(gamma_S),2))*(pow(abs(ONE_COMPLEX+gamma_s_on),2)) ) );
    }
    return INFINITY;
}






// def calculate_Ni(NF_dB, NFmin_db, gamma_s_on, Rn, z0):
//     # Note: NF_circle_dB is in dB
//     NF = un_db(NF_dB)
//     NFmin = un_db(NFmin_db)
//     rn = Rn/z0
//     return ( ((NF-NFmin)*abs(1+gamma_s_on)**2)/(4*rn) )

// def calculate_NF_circle(s11, s12, s21, s22, z0, NF_circle_dB, gamma_s_on, NF_opt_dB, Rn):
//     Ni = calculate_Ni(NF_circle_dB, NF_opt_dB, gamma_s_on, Rn, z0)
//     Cnf = gamma_s_on/(1+Ni)
//     rnf = ( (Ni*(1+Ni-abs(gamma_s_on)**2))/(1+Ni)**2 )**0.5
//     return Cnf, rnf



// def calculate_GA_circle(s11, s12, s21, s22, Ga_circle_dB):
//     ga = un_db(Ga_circle_dB)/abs(s21)**2
//     D = calculate_D(s11, s12, s21, s22)
//     K = calculate_K(s11, s12, s21, s22)
//     Ca = (ga*(s11-s22.conjugate()*D).conjugate())/(1+ga*(abs(s11)**2-abs(D)**2))
//     ra = ((1-2*K*abs(s12*s21)*ga + ga**2*abs(s12*s21)**2)**0.5)/(abs(1+ga*(abs(s11)**2 - abs(D)**2)))
//     return Ca, ra



// def calculate_GP_circle(s11, s12, s21, s22, Gp_circle_dB):
//     gp = un_db(Gp_circle_dB)/abs(s21)**2
//     D = calculate_D(s11, s12, s21, s22)
//     K = calculate_K(s11, s12, s21, s22)
//     Cp = (gp*(s22-s11.conjugate()*D).conjugate())/(1+gp*(abs(s22)**2-abs(D)**2))
//     rp = ((1-2*K*abs(s12*s21)*gp + gp**2*abs(s12*s21)**2)**0.5)/(abs(1+gp*(abs(s22)**2 - abs(D)**2)))
//     return Cp, rp


// def calculate_GTi(Gt_circle_dB, s11, s21, zs, z0):
//     gamma_S = calculate_gamma(zs, z0)
//     Gt_circle = un_db(Gt_circle_dB)
//     return (Gt_circle*abs(1-s11*gamma_S)**2)/((1-abs(gamma_S)**2)*abs(s21)**2)


// def calculate_GT_circle(s11, s12, s21, s22, zs, zl, z0, Gt_circle_dB):
//     GTi = calculate_GTi(Gt_circle_dB, s11, s21, zs, z0)
//     gamma_out = calculate_gamma_out(s11, s12, s21, s22, zs, z0)
//     Ct = ( GTi * gamma_out.conjugate() )/(GTi*abs(gamma_out)**2 + 1)
//     rt = ( (GTi**2 * abs(gamma_out)**2)/(GTi*abs(gamma_out)**2 + 1)**2 + (1-GTi)/(GTi*abs(gamma_out)**2 + 1) )**0.5
//     return Ct, rt


// def calculate_gamma_S_opt(s11, s12, s21, s22):
//     D  = calculate_D(s11, s12, s21, s22)
//     B1 = 1 - abs(s22)**2 + abs(s11)**2 - abs(D)**2
//     C1 = s11 - s22.conjugate() * D
//     abs_gamma_S_opt   = B1/(2*abs(C1)) - ((B1**2 - 4*abs(C1)**2)/(4*abs(C1)**2))**0.5
//     phase_gamma_S_opt = cmath.phase( C1.conjugate() )
//     gamma_S_opt = cmath.rect(abs_gamma_S_opt, phase_gamma_S_opt)
//     return gamma_S_opt



// def calculate_gamma_L_opt(s11, s12, s21, s22):
//     D  = calculate_D(s11, s12, s21, s22)
//     B2 = 1 - abs(s11)**2 + abs(s22)**2 - abs(D)**2
//     C2 = s22 - s11.conjugate() * D
//     abs_gamma_L_opt   = B2/(2*abs(C2)) - ((B2**2 - 4*abs(C2)**2)/(4*abs(C2)**2))**0.5
//     phase_gamma_L_opt = cmath.phase( C2.conjugate() )
//     gamma_L_opt = cmath.rect(abs_gamma_L_opt, phase_gamma_L_opt)
//     return gamma_L_opt
