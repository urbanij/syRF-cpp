/*****************************************************************
**                                                              **
**  syRF                                                        **
**  Copyright (C) 2019-2020 Francesco Urbani                    **
**                                                              **
******************************************************************
**  Author:    Francesco Urbani <https://urbanij.github.io/>    **
**  Date:      Sun Apr 12 19:02:02 CEST 2020                    **
**  File:           utils.cpp                                   **
**  Description:    various utils and functions used throghout
                    the project
******************************************************************/


#include "utils.h"
#include <cmath>
#include <complex>
#include <map>
#include <regex>
#include <iostream>




/* type definitions */
// #define complex_t               std::complex<double>
typedef std::complex<double>    complex_t;
#define ONE_COMPLEX             complex_t(1.0, 0.0)




double linear_2_dB(double x) {
    return 10*log10(abs(x));
}

double dB_2_linear(double x) {
    return pow(10, (x/10));
}

complex_t polar_2_rect(double mag,
                       double phase) // phase in radians!
{
    return complex_t(mag*cos(phase), mag*sin(phase));
}


double get_value_from_dictionary(std::map<double, double>& m,
                                double                   target_k)
{
    /* Use two iterators pointing the elements one next to the other and traverse the map.
    Once one becomes bigger than the target while the other is still smaller I do a
    linear interpolation and return the value.
    */
    std::map<double, double>::iterator it_slow = m.begin();
    std::map<double, double>::iterator it_fast = m.begin();
    ++it_fast; // initializing it_fast 1 step ahead of it_slow

    while (it_fast != m.end()){
        if (target_k - it_fast->first < 0 && target_k - it_slow->first > 0){

            // interpolate the target point and renaming the variables for convenience.

            double a  = it_slow->first;
            double fa = it_slow->second;
            double b  = it_fast->first;
            double fb = it_fast->second;
            double c  = target_k;

            return fa + ((fb-fa)/(b-a) * (c-a));

            // return abs(target_k - it_fast->first) < abs(target_k - it_slow->first) ?
            //         std::make_pair(it_fast->first,it_fast->second) : std::make_pair(it_slow->first,it_slow->second);
        }
        it_fast++;
        it_slow++;

    }
    return it_fast->second; // technically you should never reach this
}



void filter_S_transistor_bias_settings(const std::string s,
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
        // for (auto i: match){
        //     std::cout << i << '\n';
        // }
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

