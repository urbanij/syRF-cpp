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
#include "utils.h"


complex_t compute_D(complex_t s11,
                    complex_t s12,
                    complex_t s21,
                    complex_t s22)
{
    return (s11*s22 - s12*s21);
}


double calculate_K(complex_t s11,
                complex_t s12,
                complex_t s21,
                complex_t s22 )
{
    complex_t D = compute_D(s11, s12, s21, s22);
    return (1-pow(abs(s11),2) - pow(abs(s22),2) + pow(abs(D),2)) / (2*abs(s12*s21));
}

complex_t z2gamma(complex_t zl, complex_t z0) {
    complex_t gamma = (zl-z0)/(zl+z0);
    return gamma;
}


complex_t gamma2z(complex_t gamma, complex_t z0) {
    complex_t z;
    if (gamma != ONE_COMPLEX){
        z = z0 * ((ONE_COMPLEX + gamma)/(ONE_COMPLEX - gamma));
    } else {
        z = complex_t(INFINITY, INFINITY); // maybe unnecessary
    }
    return z;
}

complex_t calculate_gamma_in(complex_t s11,
                            complex_t s12,
                            complex_t s21,
                            complex_t s22,
                            complex_t zl,
                            complex_t z0)
{
    complex_t gamma_L = z2gamma(zl, z0);
    return ( s11 + (s12*s21*gamma_L)/(ONE_COMPLEX - s22*gamma_L) );
}

complex_t calculate_gamma_out(complex_t s11,
                            complex_t s12,
                            complex_t s21,
                            complex_t s22,
                            complex_t zs,
                            complex_t z0)
{
    complex_t gamma_S = z2gamma(zs, z0);
    return ( s22 + (s21*s12*gamma_S)/(ONE_COMPLEX - s11*gamma_S) );
}

std::pair<complex_t, double> calculate_ISC(complex_t s11,
                                        complex_t s12,
                                        complex_t s21,
                                        complex_t s22)
{
    complex_t D = compute_D(s11, s12, s21, s22);

    complex_t numerator_cs = std::conj(s11 - D*std::conj(s22));
    complex_t denumerator_cs = pow(abs(s11),2) - pow(abs(D),2);
    complex_t Cs = numerator_cs / denumerator_cs;

    double numerator_rs = abs(s12 * s21);
    double denumerator_rs = abs( pow(abs(D),2) - pow(abs(s11),2) );
    double rs = numerator_rs / denumerator_rs;

    return std::make_pair(Cs, rs);
}

std::pair<complex_t, double> calculate_OSC(complex_t s11,
                                        complex_t s12,
                                        complex_t s21,
                                        complex_t s22)
{

    complex_t D = compute_D(s11, s12, s21, s22);

    complex_t numerator_cl = std::conj(s22 - D*std::conj(s11));
    complex_t denumerator_cl = pow(abs(s22),2) - pow(abs(D),2);
    complex_t Cl = numerator_cl / denumerator_cl;

    double numerator_rl = abs(s12 * s21);
    double denumerator_rl = abs( pow(abs(D),2) - pow(abs(s22),2) );
    double rl = numerator_rl / denumerator_rl;

    return std::make_pair(Cl, rl);
}

double calculate_GP(complex_t s11,
                complex_t s12,
                complex_t s21,
                complex_t s22,
                complex_t zl,
                complex_t z0)
{
    complex_t gamma_L = z2gamma(zl, z0);
    complex_t gamma_in = calculate_gamma_in(s11, s12, s21, s22, zl, z0);
    // page 51 ETLC disp
    return pow(abs( (s21)/(ONE_COMPLEX - s22*gamma_L) ),2) * ( (1.0 - pow(abs(gamma_L),2))/(1.0 - pow(abs(gamma_in),2)) );
}


double calculate_GT(complex_t s11,
                complex_t s12,
                complex_t s21,
                complex_t s22,
                complex_t zs,
                complex_t zl,
                complex_t z0)
{
    complex_t gamma_S = z2gamma(zs, z0);
    complex_t gamma_L = z2gamma(zl, z0);
    complex_t gamma_out = calculate_gamma_out(s11, s12, s21, s22, zs, z0);

    double num = ( pow(abs(s21),2) ) * (1.0 - pow(abs(gamma_S),2)) * (1.0 - pow(abs(gamma_L),2));
    double denum = ( pow(abs( ONE_COMPLEX - gamma_out*gamma_L ) ,2) ) * ( pow(abs( ONE_COMPLEX - s11*gamma_S ),2) );

    return num/denum;
}

double calculate_GA(complex_t s11,
                complex_t s12,
                complex_t s21,
                complex_t s22,
                complex_t zs,
                complex_t z0)
{
    complex_t gamma_S = z2gamma(zs, z0);
    complex_t gamma_out = calculate_gamma_out(s11, s12, s21, s22, zs, z0);

    double num = (pow(abs(s21),2)) * ( 1.0 - pow(abs(gamma_S),2) );
    double denum = ( 1.0 - pow(abs(gamma_out),2) ) * ( pow( abs(ONE_COMPLEX - s11*gamma_S),2) );

    return num/denum;
}



double calculate_NF(double NFmin_db,
                    double Rn,
                    complex_t gamma_s_on,
                    complex_t zs,
                    double z0)
{
    double NFmin = dB_2_linear(NFmin_db);
    double rn = Rn/z0;
    complex_t gamma_S = z2gamma(zs, z0);

#if 0
    if (abs(gamma_S) != 1){
        // from page 60 ETLC disp
        return ( NFmin + (4 * rn * (pow( (abs(gamma_S - gamma_s_on)) ,2)) )/( (1.0 - pow(abs(gamma_S),2))*(pow(abs(ONE_COMPLEX+gamma_s_on),2)) ) );
    }
    return INFINITY;
#endif
    return ( NFmin + (4 * rn * (pow( (abs(gamma_S - gamma_s_on)) ,2)) )/( (1.0 - pow(abs(gamma_S),2))*(pow(abs(ONE_COMPLEX+gamma_s_on),2)) ) );
}


/// internal function (only `calculate_NF_circle` uses it)
double calculate_Ni(double NF_dB,
                    double NFmin_db,
                    complex_t gamma_s_on,
                    double Rn,
                    double z0)
{
    // Note: NF_circle_dB is in dB
    double noise_fig = dB_2_linear(NF_dB);
    double noise_fig_min = dB_2_linear(NFmin_db);
    double rn = Rn/z0;

    return ( ( (noise_fig-noise_fig_min)*pow(abs(ONE_COMPLEX+gamma_s_on),2) )/(4*rn) );
}


std::pair<complex_t, double> calculate_NF_circle(complex_t   s11,
                                                complex_t   s12,
                                                complex_t   s21,
                                                complex_t   s22,
                                                double       z0,
                                                double       NF_circle_dB,
                                                complex_t   gamma_s_on,
                                                double       NF_opt_dB,
                                                double       Rn)
{
    double Ni = calculate_Ni(NF_circle_dB, NF_opt_dB, gamma_s_on, Rn, z0);
    complex_t Cnf = gamma_s_on / complex_t(1.0+Ni, 0);

    // double rnf = sqrt( ( (Ni-pow(abs(gamma_s_on),2))/(1.0+Ni) ) - ( (pow(abs(gamma_s_on),2))/(1.0+Ni) ) ); // WRONG (also on my notes)

    double rnf = sqrt( ( Ni*(1.0+Ni) - Ni*pow(abs(gamma_s_on),2) )/(pow((1.0+Ni),2)) );

    return std::make_pair(Cnf, rnf);

}

std::pair<complex_t, double> calculate_GA_circle(complex_t s11,
                                                complex_t s12,
                                                complex_t s21,
                                                complex_t s22,
                                                double     Ga_circle_dB)
{
    double ga = dB_2_linear(Ga_circle_dB)/pow(abs(s21),2);
    complex_t D = compute_D(s11, s12, s21, s22);
    double K = calculate_K(s11, s12, s21, s22);

    complex_t Ca_num = ga * std::conj(s11 - D*std::conj(s22));
    double Ca_denom = 1.0 + ga*(pow(abs(s11),2) - pow(abs(D),2));
    complex_t Ca = Ca_num/Ca_denom;

    double ra_num = sqrt( 1.0 - 2*K*ga*abs(s12*s21) + pow((ga*abs(s12*s21)),2) );
    double ra_denom = abs(1.0 + ga*( pow(abs(s11),2) - pow(abs(D),2) ));
    double ra = ra_num/ra_denom;

    return std::make_pair(Ca, ra);
}


std::pair<complex_t, double> calculate_GP_circle(complex_t s11,
                                                complex_t s12,
                                                complex_t s21,
                                                complex_t s22,
                                                double     Gp_circle_dB)
{
    double gp = dB_2_linear(Gp_circle_dB)/pow(abs(s21),2);
    complex_t D = compute_D(s11, s12, s21, s22);
    double K = calculate_K(s11, s12, s21, s22);

    complex_t Cp_num = gp * std::conj(s22 - D*std::conj(s11));
    double Cp_denom = 1.0 + gp*(pow(abs(s22),2) - pow(abs(D),2));
    complex_t Cp = Cp_num/Cp_denom;

    double rp_num = sqrt( 1.0 - 2*K*gp*abs(s12*s21) + pow((gp*abs(s12*s21)),2) );
    double rp_denom = abs(1.0 + gp*( pow(abs(s22),2) - pow(abs(D),2) ));
    double rp = rp_num/rp_denom;

    return std::make_pair(Cp, rp);
}


/// internal function (only `calculate_GT_circle` uses it)
double calculate_GTi(double Gt_circle_dB,
                    complex_t s11,
                    complex_t s21,
                    complex_t zs,
                    double z0)
{
    complex_t gamma_S = z2gamma(zs, z0);
    double Gt_circle = dB_2_linear(Gt_circle_dB);
    return ( (Gt_circle * pow(abs(ONE_COMPLEX - s11*gamma_S),2))/((1.0-pow(abs(gamma_S),2))*pow(abs(s21),2)) );
}


std::pair<complex_t, double>
calculate_GT_circle(complex_t s11,
                    complex_t s12,
                    complex_t s21,
                    complex_t s22,
                    complex_t zs,
                    complex_t zl,
                    double z0,
                    double Gt_circle_dB)
{

    double GTi = calculate_GTi(Gt_circle_dB, s11, s21, zs, z0);
    complex_t gamma_out = calculate_gamma_out(s11, s12, s21, s22, zs, z0);
    complex_t Ct = std::conj(gamma_out) * complex_t(((GTi)/(GTi * pow(abs(gamma_out),2) + 1.0)),0) ;

    // rt from page 58
    double rt_first_term = ( pow( GTi*abs(gamma_out),2) )/(pow((1.0 + GTi*pow(abs(gamma_out),2)),2));

    double rt_second_term = (1.0 - GTi)/(1.0 + GTi*pow(abs(gamma_out),2));

    double rt = sqrt(rt_first_term + rt_second_term);

    return std::make_pair(Ct, rt);

}


complex_t calculate_gamma_S_opt(complex_t s11,
                                complex_t s12,
                                complex_t s21,
                                complex_t s22)
{
    complex_t D  = compute_D(s11, s12, s21, s22);
    double B1 = 1.0 - pow(abs(s22),2) + pow(abs(s11),2) - pow(abs(D),2);
    complex_t C1 = s11 - D*std::conj(s22);
    double abs_gamma_S_opt = B1/(2*abs(C1)) - sqrt( (pow(B1,2) - 4*pow(abs(C1),2))/(4*pow(abs(C1),2)) );
    double phase_gamma_S_opt = std::arg(std::conj(C1));

    complex_t gamma_S_opt = polar_2_rect(abs_gamma_S_opt, phase_gamma_S_opt);
    return gamma_S_opt;
}



complex_t calculate_gamma_L_opt(complex_t s11,
                                complex_t s12,
                                complex_t s21,
                                complex_t s22)
{
    complex_t D  = compute_D(s11, s12, s21, s22);
    double B1 = 1.0 - pow(abs(s11),2) + pow(abs(s22),2) - pow(abs(D),2);
    complex_t C1 = s22 - D*std::conj(s11);
    double abs_gamma_L_opt = B1/(2*abs(C1)) - sqrt( (pow(B1,2) - 4*pow(abs(C1),2))/(4*pow(abs(C1),2)) );
    double phase_gamma_L_opt = std::arg(std::conj(C1));

    complex_t gamma_L_opt = polar_2_rect(abs_gamma_L_opt, phase_gamma_L_opt);
    return gamma_L_opt;
}
