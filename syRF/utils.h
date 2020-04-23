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

#define USE_QT_REGEX 1
#if USE_QT_REGEX
    #include <QRegularExpression>
#else
    #include <regex>
#endif
#include <string>





/* ANSI colors and stuff */
#define ANSI_COLOR_RED          "\x1b[31m"
#define ANSI_COLOR_GREEN        "\x1b[32m"
#define ANSI_COLOR_YELLOW       "\x1b[33m"
#define ANSI_COLOR_GREY         "\x1b[90m"
#define ANSI_BOLD               "\033[1m"
#define ANSI_COLOR_RESET        "\x1b[0m"
#define ANSI_COLOR_YELLOW       "\x1b[33m"
/* end colors */


/* type definitions */
// #define complex_t               std::complex<float>
typedef std::complex<float>     complex_t;
#define ONE_COMPLEX             complex_t(1.0, 0.0)




#define MAG(x)                  std::abs((x))
#define ARG_DEG(x)              std::arg((x))/3.14159265 * 180  // radians to degrees
#define ARG_RAD(x)              std::arg((x))
#define DEG_2_RAD(x)            (((x))/180)*3.14159265          // degrees to radians


//#define CHECK_EQUALS(x,y)       ( std::abs( (x)-(y) ) < 0.01)

#define PRINT(x)                std::cout << x << "\n"
#define WATCH(x)                std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << (#x) << " = " << x << "\n"




float linear_2_dB(float x){
    return 10*log10(abs(x));
}

float dB_2_linear(float x){
    return pow(10, (x/10));
}

complex_t 
polar_2_rect(float mag,
             float phase)
{
    return complex_t(mag*cos(phase), mag*sin(phase));
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



void 
filter_S_transistor_bias_settings(const std::string s,
                                  std::string&      transistor_name, 
                                  int&              Vce, 
                                  int&              Ic, 
                                  int&              f0)
{

#define REGEX_MATCHING_PATTERN      "(^MRF57[1-2]), Vce=(\\d+) V, Ic=(\\d+) mA, f=(\\d+) MHz"

#if USE_QT_REGEX
    QRegularExpression re(REGEX_MATCHING_PATTERN);
    QString s_qstr = QString::fromStdString(s); // casting s from std::string to QString because that's what re.match wants.
    QRegularExpressionMatch match = re.match(s_qstr);
    if (match.hasMatch()) {
        // QString matched_entire_string = match.captured(0); 
        QString matched_transistor_name = match.captured(1); 
        QString matched_Vce             = match.captured(2); 
        QString matched_Ic              = match.captured(3); 
        QString matched_f0              = match.captured(4); 

        transistor_name = matched_transistor_name.toStdString();
        Vce = matched_Vce.toInt();
        Ic  = matched_Ic.toInt();
        f0  = matched_f0.toInt();
    }

#else
    std::regex rgx(REGEX_MATCHING_PATTERN);
    std::smatch match;

    if (std::regex_search(s.begin(), s.end(), match, rgx)){
        for (auto i: match){
            std::cout << i << '\n';
        }
    }
#endif

    
#if USE_QT_REGEX
    // nothing, values already assigned.    
#else
    /* match[0] is the whole line, e.g.: MRF572, Vce=6 V, Ic=50 mA, f=1500 MHz */
    transistor_name = match[1];
    Vce             = std::stoi(match[2]);
    Ic              = std::stoi(match[3]);
    f0              = std::stoi(match[4]);
#endif
    return;
}










#endif // UTILS_H
