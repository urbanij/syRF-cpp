/*****************************************************************
**                                                              **
**  syRF                                                        **
**  Copyright (C) 2019-2020 Francesco Urbani                    **
**                                                              **
******************************************************************
**  Author:    Francesco Urbani <https://urbanij.github.io/>    **
**  Date:      Sun Apr 12 09:47:14 CEST 2020                    **
**  File:           tests.cpp                                   **
**  Description:                                                **
**          
**      g++ -Wall tests.cpp -std=c++14 -o tests && ./tests
*****************************************************************/

#include <complex>
#include <iostream>
#include <assert.h>
#include <math.h>

#include "utils.h"
#include "y_parameters.h"
#include "s_parameters.h"



/*
double trunc(double d){
    return (d>0) ? floor(d) : ceil(d) ;
}*/
/*
template<typename T>
static bool AreEqual(T f1, T f2) {
    return (std::fabs(f1 - f2) <= std::numeric_limits<T>::epsilon() * std::fmax(std::fabs(f1), std::fabs(f2)));
}*/


void test_y_param()
/*      Y PARAMETERS TESTS    */
{

    // test 1 Y PARAM
    {
        std::complex<float> y_i = 2,
                            y_f = 5,
                            y_o = 13,
                            y_r = 2;

        std::complex<float> y_s = 12,
                            y_l = 20;

        // C
        assert (CHECK_EQUALS(
                    compute_C( y_i, y_f, y_o, y_r) , 0.238095
                    ));

        // beta A
        assert (CHECK_EQUALS(
                    (MAG(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l))) , 0.021645
                    ));
        assert (CHECK_EQUALS(
                    (ARG_DEG(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l))) , 0.0
                    ));

        // y_in
        assert (CHECK_EQUALS(
                    (calculate_yin( y_i, y_f, y_o, y_r, y_l ).real()) , 1.6969
                    ));
        assert (CHECK_EQUALS(
                    (calculate_yin( y_i, y_f, y_o, y_r, y_l).imag()) , 0.0
                    ));

        // y_out
        assert (CHECK_EQUALS(
                    (calculate_yout( y_i, y_f, y_o, y_r, y_s ).real()) , 12.2857
                    ));
        assert (CHECK_EQUALS(
                    (calculate_yout( y_i, y_f, y_o, y_r, y_s).imag()) , 0.0
                    ));

        // A_V
        assert (CHECK_EQUALS(
                    (MAG(calculate_A_V( y_f, y_o, y_l))) , 0.151515
                    ));
        assert (CHECK_EQUALS(
                    (ARG_DEG(calculate_A_V( y_f, y_o, y_l))) , 180
                    ));

        // v_out over v_s
        assert (CHECK_EQUALS(
                    (MAG(calculate_vout_over_vs( y_i, y_f, y_o, y_r, y_s, y_l))) , 0.132743
                    ));

        // G_A
        assert (CHECK_EQUALS(
                    (calculate_G_A(y_i, y_f, y_o, y_r, y_s)) , 0.124585
                    ));
        // G_A (dB)
        assert (CHECK_EQUALS(
                    (linear_2_dB(calculate_G_A(y_i, y_f, y_o, y_r, y_s))) , -9.04535
                    ));

        // G_P
        assert (CHECK_EQUALS(
                    (calculate_G_P(y_i, y_f, y_o, y_r, y_l)) , 0.270563
                    ));
        // G_P (dB)
        assert (CHECK_EQUALS(
                    (linear_2_dB(calculate_G_P(y_i, y_f, y_o, y_r, y_l))) , -5.67732
                    ));

        // G_T
        assert (CHECK_EQUALS(
                    (calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l)) , 0.117472
                    ));
        // G_T (dB)
        assert (CHECK_EQUALS(
                    (linear_2_dB(calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l))) , -9.30066
                    ));

        // k
        assert (CHECK_EQUALS(
                    (calculate_k(y_i, y_f, y_o, y_r, y_s, y_l)) , 46.2
                    ));

        // g_s_opt
        assert (CHECK_EQUALS(
                    (calculate_g_s_opt( y_i, y_f, y_o, y_r)) , 1.56893
                    ));

        // y_s_opt
        assert (CHECK_EQUALS(
                    (calculate_y_s_opt( y_i, y_f, y_o, y_r).real()) , 1.56893
                    ));
        assert (CHECK_EQUALS(
                    (calculate_y_s_opt( y_i, y_f, y_o, y_r).imag()) , 0.0
                    ));

        // y_l_opt
        assert (CHECK_EQUALS(
                    (calculate_y_l_opt( y_i, y_f, y_o, y_r).real()) , 10.198
                    ));
        assert (CHECK_EQUALS(
                    (calculate_y_l_opt( y_i, y_f, y_o, y_r).imag()) , 0.0
                    ));

    }



    // test 2 Y PARAM
    {
        std::complex<float> y_i = 0.32,
                            y_f = 10,
                            y_o = 54,
                            y_r = 10.43;

        std::complex<float> y_s = 124,
                            y_l = 201;

        // C
        assert (CHECK_EQUALS(
                    compute_C( y_i, y_f, y_o, y_r) , -1.49555
                    ));

        // beta A
        assert (CHECK_EQUALS(
                    (MAG(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l))) , 0.00329005
                    ));
        assert (CHECK_EQUALS(
                    (ARG_DEG(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l))) , 0.0
                    ));

        // y_in
        assert (CHECK_EQUALS(
                    (calculate_yin( y_i, y_f, y_o, y_r, y_l ).real()) , -0.0890196
                    ));
        assert (CHECK_EQUALS(
                    (calculate_yin( y_i, y_f, y_o, y_r, y_l).imag()) , 0.0
                    ));

        // y_out
        assert (CHECK_EQUALS(
                    (calculate_yout( y_i, y_f, y_o, y_r, y_s ).real()) , 53.161
                    ));
        assert (CHECK_EQUALS(
                    (calculate_yout( y_i, y_f, y_o, y_r, y_s).imag()) , 0.0
                    ));

        // A_V
        assert (CHECK_EQUALS(
                    (MAG(calculate_A_V( y_f, y_o, y_l))) , 0.0392157
                    ));
        assert (CHECK_EQUALS(
                    (ARG_DEG(calculate_A_V( y_f, y_o, y_l))) , 180
                    ));

        // v_out over v_s
        assert (CHECK_EQUALS(
                    (MAG(calculate_vout_over_vs( y_i, y_f, y_o, y_r, y_s, y_l))) , 0.0392439
                    ));

        // G_A
        assert (CHECK_EQUALS(
                    (calculate_G_A(y_i, y_f, y_o, y_r, y_s)) , 0.015092
                    ));
        // G_A (dB)
        assert (CHECK_EQUALS(
                    (linear_2_dB(calculate_G_A(y_i, y_f, y_o, y_r, y_s))) , -18.2125
                    ));

        // G_P
        assert (CHECK_EQUALS(
                    (calculate_G_P(y_i, y_f, y_o, y_r, y_l)) ,-3.4724
                    ));
        // G_P (dB)
        assert (CHECK_EQUALS(
                    (linear_2_dB(calculate_G_P(y_i, y_f, y_o, y_r, y_l))) , 5.4063
                    ));

        // G_T
        assert (CHECK_EQUALS(
                    (calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l)) , 0.00998568
                    ));
        // G_T (dB)
        assert (CHECK_EQUALS(
                    (linear_2_dB(calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l))) , -20.0062
                    ));

        // k
        assert (CHECK_EQUALS(
                    (calculate_k(y_i, y_f, y_o, y_r, y_s, y_l)) , 303.946
                    ));

        // g_s_opt
        assert (CHECK_EQUALS(
                    (isnan(calculate_g_s_opt( y_i, y_f, y_o, y_r))) , 1
                    ));


        // y_s_opt
        assert (CHECK_EQUALS(
                    (isnan(calculate_y_s_opt( y_i, y_f, y_o, y_r).real())) ,1
                    ));
        assert (CHECK_EQUALS(
                    (calculate_y_s_opt( y_i, y_f, y_o, y_r).imag()) , 0.0
                    ));

        // y_l_opt
        assert (CHECK_EQUALS(
                    (isnan(calculate_y_l_opt( y_i, y_f, y_o, y_r).real())) , 1
                    ));
        assert (CHECK_EQUALS(
                    (calculate_y_l_opt( y_i, y_f, y_o, y_r).imag()) , 0.0
                    ));
    }

    // test 3 Y PARAM
    {
        std::complex<float> y_i = std::complex<float>(2.67904088,      6.52135987),
                            y_f = std::complex<float>(53.74139389,    -21.87243834),
                            y_o = std::complex<float>(0.20842061,      1.48452191),
                            y_r = std::complex<float>(-0.00829180973, -0.47646611);

        std::complex<float> y_s = std::complex<float>(10, 0),
                            y_l = std::complex<float>(20, -28);

        // C
        assert (CHECK_EQUALS(
                    compute_C( y_i, y_f, y_o, y_r) , 2.30725
                    ));


        // beta A
        assert (CHECK_EQUALS(
                    (MAG(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l))) , 0.0581689
                    ));
        assert (CHECK_EQUALS(
                    (ARG_DEG(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l))) , -87.6741
                    ));


        // y_in
        assert (CHECK_EQUALS(
                    (calculate_yin( y_i, y_f, y_o, y_r, y_l ).real()) , 2.27008
                    ));
        assert (CHECK_EQUALS(
                    (calculate_yin( y_i, y_f, y_o, y_r, y_l).imag()) , 7.24288
                    ));


        // y_out
        assert (CHECK_EQUALS(
                    (calculate_yout( y_i, y_f, y_o, y_r, y_s ).real()) , 1.70182
                    ));
        assert (CHECK_EQUALS(
                    (calculate_yout( y_i, y_f, y_o, y_r, y_s).imag()) , 2.72165
                    ));

        // A_V
        assert (CHECK_EQUALS(
                    (MAG(calculate_A_V( y_f, y_o, y_l))) , 1.74039
                    ));


        // v_out over v_s
        assert (CHECK_EQUALS(
                    (MAG(calculate_vout_over_vs( y_i, y_f, y_o, y_r, y_s, y_l))) , 1.22147
                    ));


        // G_A
        assert (CHECK_EQUALS(
                    (calculate_G_A(y_i, y_f, y_o, y_r, y_s)) , 97.3112
                    ));
        // G_A (dB)
        assert (CHECK_EQUALS(
                    (linear_2_dB(calculate_G_A(y_i, y_f, y_o, y_r, y_s))) , 19.8816
                    ));
 
        // G_P
        assert (CHECK_EQUALS(
                    (calculate_G_P(y_i, y_f, y_o, y_r, y_l)) , 26.6859
                    ));
        // G_P (dB)
        assert (CHECK_EQUALS(
                    (linear_2_dB(calculate_G_P(y_i, y_f, y_o, y_r, y_l))) , 14.2628
                    ));

        // G_T
        assert (CHECK_EQUALS(
                    (calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l)) , 11.936
                    ));
        // G_T (dB)
        assert (CHECK_EQUALS(
                    (linear_2_dB(calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l))) , 10.7686
                    ));

        // k
        assert (CHECK_EQUALS(
                    (calculate_k(y_i, y_f, y_o, y_r, y_s, y_l)) , 30.5345
                    ));

        // g_s_opt
        assert (CHECK_EQUALS(
                    (isnan(calculate_g_s_opt( y_i, y_f, y_o, y_r))) , 1
                    ));

        // y_s_opt
        assert (CHECK_EQUALS(
                    (isnan(calculate_y_s_opt( y_i, y_f, y_o, y_r).real())) ,1
                    ));
        assert (CHECK_EQUALS(
                    (calculate_y_s_opt( y_i, y_f, y_o, y_r).imag()) , -67.5148
                    ));

        // y_l_opt
        assert (CHECK_EQUALS(
                    (isnan(calculate_y_l_opt( y_i, y_f, y_o, y_r).real())) , 1
                    ));
        assert (CHECK_EQUALS(
                    (calculate_y_l_opt( y_i, y_f, y_o, y_r).imag()) ,-6.22961
                    ));
    }

    // test 4 Y PARAM
    {
        std::complex<float> y_i = std::complex<float>(21.47901761,      -3.57313491),
                            y_f = std::complex<float>(56.58412233,      -118),
                            y_o = std::complex<float>(0.16518299,       -711),
                            y_r = std::complex<float>(-0.00199532767,   -0.24835084);

        std::complex<float> y_s = std::complex<float>(20, -43),
                            y_l = 100;

        // C
        assert (CHECK_EQUALS(
                    compute_C( y_i, y_f, y_o, y_r) , 0.890107
                    ));


        // beta A
        assert (CHECK_EQUALS(
                    (MAG(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l))) , 0.0007258
                    ));
        assert (CHECK_EQUALS(
                    (ARG_DEG(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l))) , -24.5493
                    ));


        // y_in
        assert (CHECK_EQUALS(
                    (calculate_yin( y_i, y_f, y_o, y_r, y_l ).real()) , 21.4657
                    ));
        assert (CHECK_EQUALS(
                    (calculate_yin( y_i, y_f, y_o, y_r, y_l).imag()) , -3.52988
                    ));


        // y_out
        assert (CHECK_EQUALS(
                    (calculate_yout( y_i, y_f, y_o, y_r, y_s ).real()) , 0.313459
                    ));
        assert (CHECK_EQUALS(
                    (calculate_yout( y_i, y_f, y_o, y_r, y_s).imag()) ,-710.5
                    ));

        // A_V
        assert (CHECK_EQUALS(
                    (MAG(calculate_A_V( y_f, y_o, y_l))) , 0.182259
                    ));


        // v_out over v_s
        assert (CHECK_EQUALS(
                    (MAG(calculate_vout_over_vs( y_i, y_f, y_o, y_r, y_s, y_l))) , 0.138682
                    ));

        //PRINT(calculate_G_A(y_i, y_f, y_o, y_r, y_s));
    
        // G_A
        assert (CHECK_EQUALS(
                    (calculate_G_A(y_i, y_f, y_o, y_r, y_s)) , 280.98
                    ));
        // G_A (dB)
        assert (CHECK_EQUALS(
                    (linear_2_dB(calculate_G_A(y_i, y_f, y_o, y_r, y_s))) ,24.486
                    ));
 
        // G_P
        assert (CHECK_EQUALS(
                    (calculate_G_P(y_i, y_f, y_o, y_r, y_l)) , 0.15475
                    ));
        // G_P (dB)
        assert (CHECK_EQUALS(
                    (linear_2_dB(calculate_G_P(y_i, y_f, y_o, y_r, y_l))) , -8.10369
                    ));

        // G_T
        assert (CHECK_EQUALS(
                    (calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l)) , 0.0684129
                    ));
        // G_T (dB)
        assert (CHECK_EQUALS(
                    (linear_2_dB(calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l))) , -11.6486
                    ));

        // k
        assert (CHECK_EQUALS(
                    (calculate_k(y_i, y_f, y_o, y_r, y_s, y_l)) , 2695.02
                    ));

        // g_s_opt
        assert (CHECK_EQUALS(
                    (isnan(calculate_g_s_opt( y_i, y_f, y_o, y_r))) , 0
                    ));

        // y_s_opt
        assert (CHECK_EQUALS(
                    (calculate_y_s_opt( y_i, y_f, y_o, y_r).real()) , 50.3726
                    ));
        assert (CHECK_EQUALS(
                    (calculate_y_s_opt( y_i, y_f, y_o, y_r).imag()) , -38.251
                    ));

        // y_l_opt
        assert (CHECK_EQUALS(
                    (calculate_y_l_opt( y_i, y_f, y_o, y_r).real()) , 0.387387
                    ));
        assert (CHECK_EQUALS(
                    (calculate_y_l_opt( y_i, y_f, y_o, y_r).imag()) ,710.678
                    ));
    }
}


void test_s_param(){

    // test 1 S PARAM (MRF571 -- Vce = 6V, Ic = 5 mA, f = 200 MHz)
    {
        std::complex<float> s11 = std::complex<float>(0.05161979057065267, -0.7381973971922698),
                            s12 = std::complex<float>(0.04014783638153149,  0.04458868952864365),
                            s21 = std::complex<float>(-6.607864106023292 ,  8.160032595298198),
                            s22 = std::complex<float>(0.512769929579402  , -0.46170011838761216);
        std::complex<float> zs = std::complex<float>(20, 5.34),
                            zl = std::complex<float>(43, -5);
        float               z0 = 50.0;
        float               NFmin_db = 0;
        float               Rn = 0;
        std::complex<float> gamma_s_on = std::complex<float>(0.0, 0.0);



        // D
        assert (CHECK_EQUALS(
                    (MAG(compute_D(s11, s12, s21, s22))) , 0.537214
                    ));
        assert (CHECK_EQUALS(
                    (ARG_DEG(compute_D(s11, s12, s21, s22))) , -54.1299
                    ));

        // K
        assert (CHECK_EQUALS(
                    (calculate_K(s11, s12, s21, s22)),  0.21024
                    ));
        
        // Gamma S
        assert (CHECK_EQUALS(
                    (MAG(calculate_gamma(zs, z0))),  0.43405
                    ));
        assert (CHECK_EQUALS(
                    (ARG_DEG(calculate_gamma(zs, z0))),  165.54
                    )); 

        // Gamma L
        assert (CHECK_EQUALS(
                    (MAG(calculate_gamma(zl, z0))),  0.092365
                    ));
        assert (CHECK_EQUALS(
                    (ARG_DEG(calculate_gamma(zl, z0))),  -141.38
                    ));        

        // Gamma in
        assert (CHECK_EQUALS(
                    (MAG(calculate_gamma_in(s11, s12, s21, s22, zl, z0))),  0.71267
                    ));
        assert (CHECK_EQUALS(
                    (ARG_DEG(calculate_gamma_in(s11, s12, s21, s22, zl, z0))),  -82.26
                    ));

        // Gamma out    
        assert (CHECK_EQUALS(
                    (MAG(calculate_gamma_out(s11, s12, s21, s22, zs, z0))),  0.91069
                    ));
        assert (CHECK_EQUALS(
                    (ARG_DEG(calculate_gamma_out(s11, s12, s21, s22, zs, z0))),  -30.083
                    ));

        // ISC (input stability circle) center fisrst and radius second
        assert (CHECK_EQUALS(
                    (MAG(calculate_ISC(s11, s12, s21, s22).first)) ,2.8177
                    ));
        assert (CHECK_EQUALS(
                    (ARG_DEG(calculate_ISC(s11, s12, s21, s22).first)) , 115.2
                    ));
        assert (CHECK_EQUALS(
                    (calculate_ISC(s11, s12, s21, s22).second),  2.43242
                    ));

        // OSC (output stability circle) center fisrst and radius second
        assert (CHECK_EQUALS(
                    (MAG(calculate_OSC(s11, s12, s21, s22).first)) , 3.7016
                    ));
        assert (CHECK_EQUALS(
                    (ARG_DEG(calculate_OSC(s11, s12, s21, s22).first)) , 75.382
                    ));
        assert (CHECK_EQUALS(
                    (calculate_OSC(s11, s12, s21, s22).second), 3.36
                    ));

        // G_P
        assert (CHECK_EQUALS(
                    (calculate_GP(s11, s12, s21, s22, zl, z0)),  196.349
                    ));
        // G_T
        assert (CHECK_EQUALS(
                    (calculate_GT(s11, s12, s21, s22, zs, zl, z0)),  76.6305
                    ));
        // G_A
        assert (CHECK_EQUALS(
                    (calculate_GA(s11, s12, s21, s22, zs, z0)), 531.473
                    ));

        // NF
        assert (CHECK_EQUALS(
                    (calculate_NF(NFmin_db, Rn, gamma_s_on, zs, z0)), 1
                    ));
        assert (CHECK_EQUALS(
                    (linear_2_dB(calculate_NF(NFmin_db, Rn, gamma_s_on, zs, z0))), 0
                    ));


        
        




    }

}

void test_frequency_y_param(){
    #include "y_parameters_data.h"
    #include "utils.h"

    // WATCH(find_closest_key(&y_ie, 300));
    // WATCH(y_ie[find_closest_key(&y_ie, 300)]);

}

int main(){


    test_y_param();
    test_s_param();
    test_frequency_y_param();

    PRINT(ANSI_COLOR_GREEN ANSI_BOLD "tests passed" ANSI_COLOR_RESET " 👌");
    return 0;

}







