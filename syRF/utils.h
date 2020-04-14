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


/* ANSI colors and stuff */
#define ANSI_COLOR_RED          "\x1b[31m"
#define ANSI_COLOR_GREEN        "\x1b[32m"
#define ANSI_COLOR_YELLOW       "\x1b[33m"
#define ANSI_COLOR_GREY         "\x1b[90m"
#define ANSI_BOLD               "\033[1m"
#define ANSI_COLOR_RESET        "\x1b[0m"
#define ANSI_COLOR_YELLOW       "\x1b[33m"
/* end colors */


#define MAG(x)                  std::abs((x))
#define ARG_DEG(x)              std::arg((x))/3.14159265 * 180
#define ARG_RAD(x)              std::arg((x))

#define CHECK_EQUALS(x,y)       ( std::abs( (x)-(y) ) < 0.01)

#define PRINT(x)                std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ANSI_COLOR_RESET << ": " << x << "\n"
#define WATCH(x)                std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ANSI_COLOR_RESET << ": " << (#x) << "= " << x << "\n"



#include <map>
#include <complex>


float linear_2_dB(float x){
    return 10*log10(abs(x));
}

float dB_2_linear(float x){
    return pow(10, (x/10));
}



float
get_value_from_dictionary(
    std::map<float, float>* m,
    float                   target_k
){
    /* Use two iterators pointing the elements one next to the other and traverse the map.
    Once one becomes bigger than the target while the other is still smaller I do a
    linear interpolation and return the value.
    */
    std::map<float, float>::iterator it_slow = m->begin();
    std::map<float, float>::iterator it_fast = m->begin();
    ++it_fast; // initializing it_fast 1 step ahead of it_slow

    while (it_fast != m->end()){
        if (target_k - it_fast->first < 0 && target_k - it_slow->first > 0){

            // interpolate the target point and renaming the variables for convenience.

            float a  = it_slow->first;
            float fa = it_slow->second;
            float b  = it_fast->first;
            float fb = it_fast->second;
            float c  = target_k;

            return fa + ((fb-fa)/(b-a) * (c-a));

            // return abs(target_k - it_fast->first) < abs(target_k - it_slow->first) ?
            //         std::make_pair(it_fast->first,it_fast->second) : std::make_pair(it_slow->first,it_slow->second);
        }
        it_fast++;
        it_slow++;

    }
    return it_fast->second; // technically you should never reach this
}






#endif // UTILS_H
