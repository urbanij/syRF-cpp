/*****************************************************************
**                                                              **
**  syRF                                                        **
**  Copyright (C) 2019-2020 Francesco Urbani                    **
**                                                              **
******************************************************************
**  Author:    Francesco Urbani <https://urbanij.github.io/>    **
**  Date:      Sun Apr 12 19:02:02 CEST 2020                    **
**  File:           utils.h                                     **
**  Description:    various utils and functions used throghout
                    the project
******************************************************************/

#ifndef UTILS_H
#define UTILS_H

#include <map>
#include <complex>
#include <cmath>

#define USE_QT_REGEX 0
#if USE_QT_REGEX
    #include <QRegularExpression>
#else
    #include <regex>
#endif
#include <string>

typedef std::complex<float>     complex_t;
#define ONE_COMPLEX             complex_t(1.0, 0.0)





#define URL_2N4957 "https://urbanij.github.io/syRF/src/main/python/2N4957/2N4957.pdf"
#define URL_MRF571 "https://urbanij.github.io/syRF/src/main/python/MRF57/MRF57.pdf"






/* ANSI colors and stuff */
#define ANSI_COLOR_RED          "\x1b[31m"
#define ANSI_COLOR_GREEN        "\x1b[32m"
#define ANSI_COLOR_YELLOW       "\x1b[33m"
#define ANSI_COLOR_GREY         "\x1b[90m"
#define ANSI_BOLD               "\033[1m"
#define ANSI_COLOR_RESET        "\x1b[0m"
#define ANSI_COLOR_YELLOW       "\x1b[33m"
/* end colors */



/* displays output */
#define ORANGE          "#cf9936"
#define RED             "#db3309"
#define GREEN           "#23ad2e"





#define MAG(x)                  std::abs((x))
#define ARG_DEG(x)              std::arg((x))/3.14159265 * 180  // radians to degrees
#define ARG_RAD(x)              std::arg((x))
#define DEG_2_RAD(x)            (((x))/180)*3.14159265          // degrees to radians


//#define CHECK_EQUALS(x,y)       ( std::abs( (x)-(y) ) < 0.01)

#define PRINT(x)                std::cout << x << "\n"
#define WATCH(x)                std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << (#x) << " = " << x << "\n"




float
linear_2_dB(float x);

float
dB_2_linear(float x);


complex_t 
polar_2_rect(float mag,
             float phase);

float
get_value_from_dictionary(std::map<float, float>* m,
                          float                   target_k);

void 
filter_S_transistor_bias_settings(const std::string s,
                                  std::string&      transistor_name, 
                                  int&              Vce, 
                                  int&              Ic, 
                                  int&              f0);











#endif // UTILS_H
