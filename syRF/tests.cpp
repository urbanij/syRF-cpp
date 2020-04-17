/*****************************************************************
**                                                              **
**  syRF                                                        **
**  Copyright (C) 2019-2020 Francesco Urbani                    **
**                                                              **
******************************************************************
**  Author:    Francesco Urbani <https://urbanij.github.io/>    **
**  Date:      Fri Apr 17 13:06:38 CEST 2020                    **
**  File:           tests.cpp                                   **
**  Description:                                                **
**
**  g++ -std=c++14 tests.cpp -lgtest -lgtest_main -pthread -o tests && ./tests
*****************************************************************/
#include <gtest/gtest.h>

#include <complex>
#include <iostream>
#include <assert.h>
#include <math.h>

#include "utils.h"
#include "y_parameters.h"
#include "s_parameters.h"

// #define ERROR 0.01
#define ERROR 0.01


TEST(y_parameters, Test1){

    complex_t   y_i = 2,
                y_f = 5,
                y_o = 13,
                y_r = 2;
    complex_t   y_s = 12,
                y_l = 20;

    // C
    EXPECT_NEAR(compute_C(2, 5, 13, 2), 0.238095, ERROR);

    // beta A
    EXPECT_NEAR(MAG(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l)) , 0.021645 , ERROR);
    EXPECT_NEAR(ARG_DEG(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l)) , 0 , ERROR);

    // y_in
    EXPECT_NEAR(calculate_yin( y_i, y_f, y_o, y_r, y_l ).real() , 1.6969, ERROR);
    EXPECT_NEAR(calculate_yin( y_i, y_f, y_o, y_r, y_l).imag() , 0.0, ERROR);

    // y_out
    EXPECT_NEAR(calculate_yout( y_i, y_f, y_o, y_r, y_s ).real() , 12.2857, ERROR);
    EXPECT_NEAR(calculate_yout( y_i, y_f, y_o, y_r, y_s).imag() , 0.0, ERROR);

    // A_V
    EXPECT_NEAR(MAG(calculate_A_V( y_f, y_o, y_l)) , 0.151515, ERROR);
    EXPECT_NEAR(ARG_DEG(calculate_A_V( y_f, y_o, y_l)) , 180, ERROR);

    // v_out over v_s
    EXPECT_NEAR(MAG(calculate_vout_over_vs( y_i, y_f, y_o, y_r, y_s, y_l)) , 0.132743, ERROR);

    // G_A
    EXPECT_NEAR(calculate_G_A(y_i, y_f, y_o, y_r, y_s) , 0.124585, ERROR);
    // G_A (dB)
    EXPECT_NEAR(linear_2_dB(calculate_G_A(y_i, y_f, y_o, y_r, y_s)) , -9.04535, ERROR);

    // G_P
    EXPECT_NEAR(calculate_G_P(y_i, y_f, y_o, y_r, y_l) , 0.270563, ERROR);
    // G_P (dB)
    EXPECT_NEAR(linear_2_dB(calculate_G_P(y_i, y_f, y_o, y_r, y_l)) , -5.67732, ERROR);

    // G_T
    EXPECT_NEAR(calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l) , 0.117472, ERROR);
    // G_T (dB)
    EXPECT_NEAR(linear_2_dB(calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l)) , -9.30066, ERROR);

    // k
    EXPECT_NEAR(calculate_k(y_i, y_f, y_o, y_r, y_s, y_l) , 46.2, ERROR);

    // g_s_opt
    EXPECT_NEAR(calculate_g_s_opt( y_i, y_f, y_o, y_r) , 1.56893, ERROR);

    // y_s_opt
    EXPECT_NEAR(calculate_y_s_opt( y_i, y_f, y_o, y_r).real() , 1.56893, ERROR);
    EXPECT_NEAR(calculate_y_s_opt( y_i, y_f, y_o, y_r).imag() , 0.0, ERROR);

    // y_l_opt
    EXPECT_NEAR(calculate_y_l_opt( y_i, y_f, y_o, y_r).real() , 10.198, ERROR);
    EXPECT_NEAR(calculate_y_l_opt( y_i, y_f, y_o, y_r).imag() , 0.0, ERROR);


}


TEST(y_parameters, Test2){

    complex_t   y_i = 0.32,
                y_f = 10,
                y_o = 54,
                y_r = 10.43;
    complex_t   y_s = 124,
                y_l = 201;

    // C
    EXPECT_NEAR(compute_C( y_i, y_f, y_o, y_r) , -1.49555, ERROR);

    // beta A
    EXPECT_NEAR(MAG(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l)) , 0.00329005, ERROR);
    EXPECT_NEAR(ARG_DEG(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l)) , 0.0, ERROR);

    // y_in
    EXPECT_NEAR(calculate_yin( y_i, y_f, y_o, y_r, y_l ).real() , -0.0890196, ERROR);
    EXPECT_NEAR(calculate_yin( y_i, y_f, y_o, y_r, y_l).imag() , 0.0, ERROR);

    // y_out
    EXPECT_NEAR(calculate_yout( y_i, y_f, y_o, y_r, y_s ).real() , 53.161, ERROR);
    EXPECT_NEAR(calculate_yout( y_i, y_f, y_o, y_r, y_s).imag() , 0.0, ERROR);

    // A_V
    EXPECT_NEAR(MAG(calculate_A_V( y_f, y_o, y_l)) , 0.0392157, ERROR);
    EXPECT_NEAR(ARG_DEG(calculate_A_V( y_f, y_o, y_l)) , 180, ERROR);

    // v_out over v_s
    EXPECT_NEAR(MAG(calculate_vout_over_vs( y_i, y_f, y_o, y_r, y_s, y_l)) , 0.0392439, ERROR);

    // G_A
    EXPECT_NEAR(calculate_G_A(y_i, y_f, y_o, y_r, y_s) , 0.015092, ERROR);
    // G_A (dB)
    EXPECT_NEAR(linear_2_dB(calculate_G_A(y_i, y_f, y_o, y_r, y_s)) , -18.2125, ERROR);

    // G_P
    EXPECT_NEAR(calculate_G_P(y_i, y_f, y_o, y_r, y_l) ,-3.4724, ERROR);
    // G_P (dB)
    EXPECT_NEAR(linear_2_dB(calculate_G_P(y_i, y_f, y_o, y_r, y_l)) , 5.4063, ERROR);

    // G_T
    EXPECT_NEAR(calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l) , 0.00998568, ERROR);
    // G_T (dB)
    EXPECT_NEAR(linear_2_dB(calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l)) , -20.0062, ERROR);

    // k
    EXPECT_NEAR(calculate_k(y_i, y_f, y_o, y_r, y_s, y_l) , 303.946, ERROR);

    // g_s_opt
    EXPECT_NEAR(isnan(calculate_g_s_opt( y_i, y_f, y_o, y_r)) , 1, ERROR);


    // y_s_opt
    EXPECT_NEAR(isnan(calculate_y_s_opt( y_i, y_f, y_o, y_r).real()) ,1, ERROR);
    EXPECT_NEAR(calculate_y_s_opt( y_i, y_f, y_o, y_r).imag() , 0.0, ERROR);

    // y_l_opt
    EXPECT_NEAR(isnan(calculate_y_l_opt( y_i, y_f, y_o, y_r).real()) , 1, ERROR);
    EXPECT_NEAR(calculate_y_l_opt( y_i, y_f, y_o, y_r).imag() , 0.0, ERROR);

}


TEST(y_parameters, Test3){
    complex_t       y_i = complex_t(2.67904088,      6.52135987),
                    y_f = complex_t(53.74139389,    -21.87243834),
                    y_o = complex_t(0.20842061,      1.48452191),
                    y_r = complex_t(-0.00829180973, -0.47646611);
    complex_t       y_s = complex_t(10, 0),
                    y_l = complex_t(20, -28);

    // C
    EXPECT_NEAR(compute_C( y_i, y_f, y_o, y_r) , 2.30725, ERROR);


    // beta A
    EXPECT_NEAR((MAG(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l))) , 0.0581689, ERROR);
    EXPECT_NEAR((ARG_DEG(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l))) , -87.6741, ERROR);


    // y_in
    EXPECT_NEAR((calculate_yin( y_i, y_f, y_o, y_r, y_l ).real()) , 2.27008, ERROR);
    EXPECT_NEAR((calculate_yin( y_i, y_f, y_o, y_r, y_l).imag()) , 7.24288, ERROR);


    // y_out
    EXPECT_NEAR((calculate_yout( y_i, y_f, y_o, y_r, y_s ).real()) , 1.70182, ERROR);
    EXPECT_NEAR((calculate_yout( y_i, y_f, y_o, y_r, y_s).imag()) , 2.72165, ERROR);

    // A_V
    EXPECT_NEAR((MAG(calculate_A_V( y_f, y_o, y_l))) , 1.74039, ERROR);


    // v_out over v_s
    EXPECT_NEAR((MAG(calculate_vout_over_vs( y_i, y_f, y_o, y_r, y_s, y_l))) , 1.22147, ERROR);


    // G_A
    EXPECT_NEAR((calculate_G_A(y_i, y_f, y_o, y_r, y_s)) , 97.3112, ERROR);
    // G_A (dB)
    EXPECT_NEAR((linear_2_dB(calculate_G_A(y_i, y_f, y_o, y_r, y_s))) , 19.8816, ERROR);

    // G_P
    EXPECT_NEAR((calculate_G_P(y_i, y_f, y_o, y_r, y_l)) , 26.6859, ERROR);
    // G_P (dB)
    EXPECT_NEAR((linear_2_dB(calculate_G_P(y_i, y_f, y_o, y_r, y_l))) , 14.2628, ERROR);

    // G_T
    EXPECT_NEAR((calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l)) , 11.936, ERROR);
    // G_T (dB)
    EXPECT_NEAR((linear_2_dB(calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l))) , 10.7686, ERROR);

    // k
    EXPECT_NEAR((calculate_k(y_i, y_f, y_o, y_r, y_s, y_l)) , 30.5345, ERROR);

    // g_s_opt
    EXPECT_NEAR((isnan(calculate_g_s_opt( y_i, y_f, y_o, y_r))) , 1, ERROR);

    // y_s_opt
    EXPECT_NEAR((isnan(calculate_y_s_opt( y_i, y_f, y_o, y_r).real())) ,1, ERROR);
    EXPECT_NEAR((calculate_y_s_opt( y_i, y_f, y_o, y_r).imag()) , -67.5148, ERROR);

    // y_l_opt
    EXPECT_NEAR((isnan(calculate_y_l_opt( y_i, y_f, y_o, y_r).real())) , 1, ERROR);
    EXPECT_NEAR((calculate_y_l_opt( y_i, y_f, y_o, y_r).imag()) ,-6.22961, ERROR);
}


TEST(y_parameters, Test4){
    complex_t   y_i = complex_t(21.47901761,      -3.57313491),
                y_f = complex_t(56.58412233,      -118),
                y_o = complex_t(0.16518299,       -711),
                y_r = complex_t(-0.00199532767,   -0.24835084);
    complex_t   y_s = complex_t(20, -43),
                y_l = 100;

    // C
    EXPECT_NEAR(compute_C( y_i, y_f, y_o, y_r) , 0.890107, ERROR);


    // beta A
    EXPECT_NEAR((MAG(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l))) , 0.0007258, ERROR);
    EXPECT_NEAR((ARG_DEG(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l))) , -24.5493, ERROR);


    // y_in
    EXPECT_NEAR((calculate_yin( y_i, y_f, y_o, y_r, y_l ).real()) , 21.4657, ERROR);
    EXPECT_NEAR((calculate_yin( y_i, y_f, y_o, y_r, y_l).imag()) , -3.52988, ERROR);


    // y_out
    EXPECT_NEAR((calculate_yout( y_i, y_f, y_o, y_r, y_s ).real()) , 0.313459, ERROR);
    EXPECT_NEAR((calculate_yout( y_i, y_f, y_o, y_r, y_s).imag()) ,-710.5, ERROR);

    // A_V
    EXPECT_NEAR((MAG(calculate_A_V( y_f, y_o, y_l))) , 0.182259, ERROR);


    // v_out over v_s
    EXPECT_NEAR((MAG(calculate_vout_over_vs( y_i, y_f, y_o, y_r, y_s, y_l))) , 0.138682, ERROR);

    //PRINT(calculate_G_A(y_i, y_f, y_o, y_r, y_s));

    // G_A
    EXPECT_NEAR((calculate_G_A(y_i, y_f, y_o, y_r, y_s)) , 280.98, ERROR);
    // G_A (dB)
    EXPECT_NEAR((linear_2_dB(calculate_G_A(y_i, y_f, y_o, y_r, y_s))) ,24.486, ERROR);

    // G_P
    EXPECT_NEAR((calculate_G_P(y_i, y_f, y_o, y_r, y_l)) , 0.15475, ERROR);
    // G_P (dB)
    EXPECT_NEAR((linear_2_dB(calculate_G_P(y_i, y_f, y_o, y_r, y_l))) , -8.10369, ERROR);

    // G_T
    EXPECT_NEAR((calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l)) , 0.0684129, ERROR);
    // G_T (dB)
    EXPECT_NEAR((linear_2_dB(calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l))) , -11.6486, ERROR);

    // k
    EXPECT_NEAR((calculate_k(y_i, y_f, y_o, y_r, y_s, y_l)) , 2695.02, ERROR);

    // g_s_opt
    EXPECT_NEAR((isnan(calculate_g_s_opt( y_i, y_f, y_o, y_r))) , 0, ERROR);

    // y_s_opt
    EXPECT_NEAR((calculate_y_s_opt( y_i, y_f, y_o, y_r).real()) , 50.3726, ERROR);
    EXPECT_NEAR((calculate_y_s_opt( y_i, y_f, y_o, y_r).imag()) , -38.251, ERROR);

    // y_l_opt
    EXPECT_NEAR((calculate_y_l_opt( y_i, y_f, y_o, y_r).real()) , 0.387387, ERROR);
    EXPECT_NEAR((calculate_y_l_opt( y_i, y_f, y_o, y_r).imag()) ,710.678, ERROR);
}



TEST(s_parameters, Test1){
    // MRF571 -- Vce = 6V, Ic = 5 mA, f = 200 MHz

    /// ==== INPUTS ===== ///
    complex_t   s11 = complex_t(0.05161979057065267, -0.7381973971922698),
                s12 = complex_t(0.04014783638153149,  0.04458868952864365),
                s21 = complex_t(-6.607864106023292 ,  8.160032595298198),
                s22 = complex_t(0.512769929579402  , -0.46170011838761216);
    complex_t   zs  = complex_t(20, 5.34),
                zl  = complex_t(43, -5);
    float       z0  = 50.0;
    float       NFmin_db = 0;
    float       Rn  = 0;
    complex_t   gamma_s_on = complex_t(0.0, 0.0);

    /// ==== END INPUTS ===== ///


    // D
    EXPECT_NEAR((MAG(compute_D(s11, s12, s21, s22))) , 0.537214, ERROR);
    EXPECT_NEAR((ARG_DEG(compute_D(s11, s12, s21, s22))) , -54.1299, ERROR);

    // K
    EXPECT_NEAR((calculate_K(s11, s12, s21, s22)),  0.21024, ERROR);

    // Gamma S
    EXPECT_NEAR((MAG(calculate_gamma(zs, z0))),  0.43405, ERROR);
    EXPECT_NEAR((ARG_DEG(calculate_gamma(zs, z0))),  165.54, ERROR);

    // Gamma L
    EXPECT_NEAR((MAG(calculate_gamma(zl, z0))),  0.092365, ERROR);
    EXPECT_NEAR((ARG_DEG(calculate_gamma(zl, z0))),  -141.38, ERROR);

    // Gamma in
    EXPECT_NEAR((MAG(calculate_gamma_in(s11, s12, s21, s22, zl, z0))),  0.71267, ERROR);
    EXPECT_NEAR((ARG_DEG(calculate_gamma_in(s11, s12, s21, s22, zl, z0))),  -82.26, ERROR);

    // Gamma out
    EXPECT_NEAR((MAG(calculate_gamma_out(s11, s12, s21, s22, zs, z0))),  0.91069, ERROR);
    EXPECT_NEAR((ARG_DEG(calculate_gamma_out(s11, s12, s21, s22, zs, z0))),  -30.083, ERROR);

    // ISC (input stability circle) center fisrst and radius second
    EXPECT_NEAR((MAG(calculate_ISC(s11, s12, s21, s22).first)) ,2.8177, ERROR);
    EXPECT_NEAR((ARG_DEG(calculate_ISC(s11, s12, s21, s22).first)) , 115.2, ERROR);
    EXPECT_NEAR((calculate_ISC(s11, s12, s21, s22).second),  2.43242, ERROR);

    // OSC (output stability circle) center fisrst and radius second
    EXPECT_NEAR((MAG(calculate_OSC(s11, s12, s21, s22).first)) , 3.7016, ERROR);
    EXPECT_NEAR((ARG_DEG(calculate_OSC(s11, s12, s21, s22).first)) , 75.382, ERROR);
    EXPECT_NEAR((calculate_OSC(s11, s12, s21, s22).second), 3.36, ERROR);

    // G_P
    EXPECT_NEAR((calculate_GP(s11, s12, s21, s22, zl, z0)),  196.349, ERROR);
    // G_T
    EXPECT_NEAR((calculate_GT(s11, s12, s21, s22, zs, zl, z0)),  76.6305, ERROR);
    // G_A
    EXPECT_NEAR((calculate_GA(s11, s12, s21, s22, zs, z0)), 531.473, ERROR);

    // NF
    EXPECT_NEAR((calculate_NF(NFmin_db, Rn, gamma_s_on, zs, z0)), 1, ERROR);
    EXPECT_NEAR((linear_2_dB(calculate_NF(NFmin_db, Rn, gamma_s_on, zs, z0))), 0, ERROR);

    // Ni
#if 0
    float NF_dB = 1.2;
    EXPECT_NEAR((calculate_Ni(NF_dB, NFmin_db, gamma_s_on, Rn, z0)), INFINITY, ERROR); // edit


    // NF circle
    float NF_circle_dB = 1.5;
    float NF_opt_dB = 1.5;
    EXPECT_NEAR((MAG(calculate_NF_circle(s11, s12, s21, s22, z0, NF_circle_dB, gamma_s_on, NF_opt_dB, Rn).first)) , 3.7016, ERROR);
    EXPECT_NEAR((ARG_DEG(calculate_NF_circle(s11, s12, s21, s22, z0, NF_circle_dB, gamma_s_on, NF_opt_dB, Rn).first)) , 75.382, ERROR);
    EXPECT_NEAR((calculate_NF_circle(s11, s12, s21, s22, z0, NF_circle_dB, gamma_s_on, NF_opt_dB, Rn).second), 3.36, ERROR);
#endif

    // GA circles
    {
        float Ga_circle_dB = 12.0;
        EXPECT_NEAR((MAG(calculate_GA_circle(s11, s12, s21, s22, Ga_circle_dB).first)) , 0.10114, ERROR);
        EXPECT_NEAR((ARG_DEG(calculate_GA_circle(s11, s12, s21, s22, Ga_circle_dB).first)) , 115.2, ERROR);
        EXPECT_NEAR((calculate_GA_circle(s11, s12, s21, s22, Ga_circle_dB).second), 0.94959, ERROR);
    }
    {
        float Ga_circle_dB = 3.0;
        EXPECT_NEAR((MAG(calculate_GA_circle(s11, s12, s21, s22, Ga_circle_dB).first)) , 0.013146, ERROR);
        EXPECT_NEAR((ARG_DEG(calculate_GA_circle(s11, s12, s21, s22, Ga_circle_dB).first)) , 115.2, ERROR);
        EXPECT_NEAR((calculate_GA_circle(s11, s12, s21, s22, Ga_circle_dB).second), 0.99301, ERROR);
    }
    {
        float Ga_circle_dB = 40.5;
        EXPECT_NEAR((MAG(calculate_GA_circle(s11, s12, s21, s22, Ga_circle_dB).first)) , 2.7147, ERROR);
        EXPECT_NEAR((ARG_DEG(calculate_GA_circle(s11, s12, s21, s22, Ga_circle_dB).first)) , 115.2, ERROR);
        EXPECT_NEAR((calculate_GA_circle(s11, s12, s21, s22, Ga_circle_dB).second), 2.3361, ERROR);
    }
    // GP circles
    {
        float Gp_circle_dB = 200.32;
        EXPECT_NEAR((MAG(calculate_GP_circle(s11, s12, s21, s22, Gp_circle_dB).first)) , 3.7016, ERROR);
        EXPECT_NEAR((ARG_DEG(calculate_GP_circle(s11, s12, s21, s22, Gp_circle_dB).first)) , 75.382, ERROR);
        EXPECT_NEAR((calculate_GP_circle(s11, s12, s21, s22, Gp_circle_dB).second), 3.36, ERROR);
    }
    {
        float Gp_circle_dB = 60.0;
        EXPECT_NEAR((MAG(calculate_GP_circle(s11, s12, s21, s22, Gp_circle_dB).first)) , 3.6995, ERROR);
        EXPECT_NEAR((ARG_DEG(calculate_GP_circle(s11, s12, s21, s22, Gp_circle_dB).first)) , 75.382, ERROR);
        EXPECT_NEAR((calculate_GP_circle(s11, s12, s21, s22, Gp_circle_dB).second), 3.3579, ERROR);
    }
    {
        float Gp_circle_dB = 14.0;
        EXPECT_NEAR((MAG(calculate_GP_circle(s11, s12, s21, s22, Gp_circle_dB).first)) , 0.15165, ERROR);
        EXPECT_NEAR((ARG_DEG(calculate_GP_circle(s11, s12, s21, s22, Gp_circle_dB).first)) , 75.382, ERROR);
        EXPECT_NEAR((calculate_GP_circle(s11, s12, s21, s22, Gp_circle_dB).second), 0.93978, ERROR);
    }

    // GT circles
    {
        float Gt_circle_dB = 10.0;
        EXPECT_NEAR((MAG(calculate_GT_circle(s11, s12, s21, s22, zs, zl, z0, Gt_circle_dB).first)) , 0.091999, ERROR);
        EXPECT_NEAR((ARG_DEG(calculate_GT_circle(s11, s12, s21, s22, zs, zl, z0, Gt_circle_dB).first)) , 30.083, ERROR);
        EXPECT_NEAR((calculate_GT_circle(s11, s12, s21, s22, zs, zl, z0, Gt_circle_dB).second), 0.90756, ERROR);
    }
    {
        float Gt_circle_dB = 20.543;
        EXPECT_NEAR((MAG(calculate_GT_circle(s11, s12, s21, s22, zs, zl, z0, Gt_circle_dB).first)) , 0.5588, ERROR);
        EXPECT_NEAR((ARG_DEG(calculate_GT_circle(s11, s12, s21, s22, zs, zl, z0, Gt_circle_dB).first)) , 30.083, ERROR);
        EXPECT_NEAR((calculate_GT_circle(s11, s12, s21, s22, zs, zl, z0, Gt_circle_dB).second), 0.43561, ERROR);
    }
    {
        float Gt_circle_dB = 26.2;
        EXPECT_NEAR((MAG(calculate_GT_circle(s11, s12, s21, s22, zs, zl, z0, Gt_circle_dB).first)) , 0.86988, ERROR);
        EXPECT_NEAR((ARG_DEG(calculate_GT_circle(s11, s12, s21, s22, zs, zl, z0, Gt_circle_dB).first)) , 30.083, ERROR);
        EXPECT_NEAR((calculate_GT_circle(s11, s12, s21, s22, zs, zl, z0, Gt_circle_dB).second), 0.096501, ERROR);
    }



}



int
main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
