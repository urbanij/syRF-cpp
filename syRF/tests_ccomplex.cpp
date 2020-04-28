/*****************************************************************
**                                                              **
**  syRF                                                        **
**  Copyright (C) 2019-2020 Francesco Urbani                    **
**                                                              **
******************************************************************
**  Author:    Francesco Urbani <https://urbanij.github.io/>    **
**  Date:      Tue Apr 28 13:25:31 CEST 2020                    **
**  File:           tests_ccomplex.cpp                          **
**  Description:                                                **
**
**  g++ -std=c++17 tests_ccomplex.cpp ccomplex.cpp -lgtest -lgtest_main -pthread -o tests_ccomplex && ./tests_ccomplex
*****************************************************************/
#include <gtest/gtest.h>

#include <iostream>      
#include <complex>  
#include <string>

#include "ccomplex.h"



TEST(y_parameters, Test0){

    /* CASTING IS MANDATORY IF YOU WANT TO USE FLOAT, OTHERWISE USE DOUBLE */
    EXPECT_NE(typeid(float), typeid(12.2));

    EXPECT_EQ(typeid(double), typeid(12.2));
    
    EXPECT_EQ(typeid(float), typeid((float) 12.2));
}


TEST(y_parameters, Test1){
    
    const std::string y_i_from_lineedit = "12.423+94.1j";

    std::complex<float> y_i = std::complex<float>(
                                (float) ccomplex( y_i_from_lineedit ).Re(),
                                (float) ccomplex( y_i_from_lineedit ).Im()
                            );


    EXPECT_EQ(typeid(double), typeid( ccomplex( y_i_from_lineedit ).Re()) );
    EXPECT_EQ(typeid(double), typeid( ccomplex( y_i_from_lineedit ).Im()) );

    EXPECT_EQ(y_i.real(), (float) 12.423);
    EXPECT_EQ(y_i.imag(), (float) 94.1);
    
}

TEST(y_parameters, Test2){
    
    const std::string y_i_from_lineedit = "64.53423-1.5465454j";

    std::complex<float> y_i = std::complex<float>(
                                (float) ccomplex( y_i_from_lineedit ).Re(),
                                (float) ccomplex( y_i_from_lineedit ).Im()
                            );

    EXPECT_EQ(y_i.real(), (float) 64.53423);
    EXPECT_EQ(y_i.imag(), (float) -1.5465454);
    
}



int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
