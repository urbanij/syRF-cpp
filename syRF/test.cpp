/***************************************************************************
**                                                                        **
**  syRF                                                                  **
**  Copyright (C) 2019 Francesco Urbani                                   **
**                                                                        **
****************************************************************************
**  Author:         Francesco Urbani <https://urbanij.github.io/>         **
**  Date:           Sun Apr 12 09:47:14 CEST 2020                         **
**  File:           tests.cpp                                             **
**  Description:                                                          **
**                  g++ test.cpp -std=c++14 -o test && ./test
****************************************************************************/

#include <complex>
#include <iostream>
#include <assert.h>
#include <limits>


#include "y_parameters.cpp"

#define NUM_DIGITS              pow(10, 6) // i.e. 6 decimal digits
#define CHECK_EQUALS(x,y)       ( (trunc(NUM_DIGITS * (x))) == (trunc(NUM_DIGITS * (y))) )


double trunc(double d){
    return (d>0) ? floor(d) : ceil(d) ;
}



int main(){

    // test 1
    {
        std::complex<float> y_i = 2,
                            y_f = 5,
                            y_o = 13,
                            y_r = 2;

        std::complex<float> y_s = 12,
                            y_l = 20;


        assert (CHECK_EQUALS(
                    compute_C( y_i, y_f, y_o, y_r) , 0.238095
                    ));

        assert (CHECK_EQUALS(
                    (std::abs(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l))) , 0.021645
                    ));
        assert (CHECK_EQUALS(
                    (std::arg(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l))) , 0.0
                    ));

    }

    return 0;
}
