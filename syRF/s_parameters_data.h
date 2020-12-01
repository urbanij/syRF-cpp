/*****************************************************************
**                                                              **
**  syRF                                                        **
**  Copyright (C) 2019-2020 Francesco Urbani                    **
**                                                              **
******************************************************************
**  Author:    Francesco Urbani <https://urbanij.github.io/>    **
**  Date:      Mon Apr 20 10:22:41 CEST 2020                    **
**  File:           s_parameters_data.cpp                       **
**  Description:                                                **
******************************************************************/

#ifndef S_PARAMETERS_DATA_H
#define S_PARAMETERS_DATA_H

#include <map>
//#include <pair>
#include <tuple>
#include <vector>
#include <complex>


typedef std::complex<double>                    complex_t;
typedef std::tuple<std::string, int, int, int>  S_param_polarization_t;


typedef std::pair<double, double>               S_parameter_t;
typedef std::vector<double>                     S_noise_vector_t;


typedef std::map<std::string, S_parameter_t>    S_parameters_map_t;
typedef std::map<std::string, double>           S_noise_map_t;


std::map<S_param_polarization_t, S_parameters_map_t> 
MRF_transistor_S_parameters = {
    
        /*
        std::make_tuple(transitor_name, Vce, Ic, f0), 
        {
            { "s11", S_parameter_t( |s11|, ∠s11 )},
            { "s12", S_parameter_t( |s12|, ∠s12 )},
            { "s21", std::make_pair( |s21|, ∠s21 )},
            { "s22", std::make_pair( |s22|, ∠s22 )}
        }, 
        */
    
        {
            std::make_tuple("MRF571", 6, 5, 200), 
            {
                { "s11", S_parameter_t(0.74, -86)},
                { "s12", S_parameter_t(0.06, 48)},
                { "s21", std::make_pair(10.5, 129)},
                { "s22", std::make_pair(0.69, -42)}
            }
        },
        {
            std::make_tuple("MRF571", 6, 5, 500), 
            {
                { "s11", S_parameter_t(0.62, -143)},
                { "s12", S_parameter_t(0.08, 33)},
                { "s21", std::make_pair(5.5, 97)},
                { "s22", std::make_pair(0.41, -59)}
            }
        },
        {
            std::make_tuple("MRF571", 6, 5, 1000), 
            {
                { "s11", S_parameter_t(0.61, 178)},
                { "s12", S_parameter_t(0.09, 37)},
                { "s21", std::make_pair(3, 78)},
                { "s22", std::make_pair(0.28, -69)}
            }
        },
        {
            std::make_tuple("MRF571", 6, 5, 1500), 
            {
                { "s11", S_parameter_t(0.65, 158)},
                { "s12", S_parameter_t(0.11, 44)},
                { "s21", std::make_pair(2, 62)},
                { "s22", std::make_pair(0.26, -88)}
            }
        },
        {
            std::make_tuple("MRF571", 6, 5, 2000), 
            {
                { "s11", S_parameter_t(0.7, 140)},
                { "s12", S_parameter_t(0.14, 51)},
                { "s21", std::make_pair(1.6, 51)},
                { "s22", std::make_pair(0.27, -99)}
            }
        },
        {
            std::make_tuple("MRF571", 6, 10, 200), 
            {
                { "s11", S_parameter_t(0.64, -111)},
                { "s12", S_parameter_t(0.04, 44)},
                { "s21", std::make_pair(15, 118)},
                { "s22", std::make_pair(0.53, -59)}
            }
        },
        {
            std::make_tuple("MRF571", 6, 10, 500), 
            {
                { "s11", S_parameter_t(0.58, -160)},
                { "s12", S_parameter_t(0.06, 42)},
                { "s21", std::make_pair(6.9, 93)},
                { "s22", std::make_pair(0.27, -77)}
            }
        },
        {
            std::make_tuple("MRF571", 6, 10, 1000), 
            {
                { "s11", S_parameter_t(0.59, 168)},
                { "s12", S_parameter_t(0.09, 52)},
                { "s21", std::make_pair(3.7, 77)},
                { "s22", std::make_pair(0.16, -91)}
            }
        },
        {
            std::make_tuple("MRF571", 6, 10, 1500), 
            {
                { "s11", S_parameter_t(0.63, 151)},
                { "s12", S_parameter_t(0.12, 56)},
                { "s21", std::make_pair(2.5, 64)},
                { "s22", std::make_pair(0.16, -113)}
            }
        },
        {
            std::make_tuple("MRF571", 6, 10, 2000), 
            {
                { "s11", S_parameter_t(0.67, 134)},
                { "s12", S_parameter_t(0.16, 57)},
                { "s21", std::make_pair(2, 53)},
                { "s22", std::make_pair(0.16, -118)}
            }
        },
        {
            std::make_tuple("MRF571", 6, 50, 200), 
            {
                { "s11", S_parameter_t(0.56, -160)},
                { "s12", S_parameter_t(0.02, 57)},
                { "s21", std::make_pair(20.4, 102)},
                { "s22", std::make_pair(0.27, -98)}
            }
        },
        {
            std::make_tuple("MRF571", 6, 50, 500), 
            {
                { "s11", S_parameter_t(0.57, 176)},
                { "s12", S_parameter_t(0.05, 67)},
                { "s21", std::make_pair(8.4, 86)},
                { "s22", std::make_pair(0.14, -130)}
            }
        },
        {
            std::make_tuple("MRF571", 6, 50, 1000), 
            {
                { "s11", S_parameter_t(0.6, 156)},
                { "s12", S_parameter_t(0.09, 70)},
                { "s21", std::make_pair(4.4, 75)},
                { "s22", std::make_pair(0.11, -164)}
            }
        },
        {
            std::make_tuple("MRF571", 6, 50, 1500), 
            {
                { "s11", S_parameter_t(0.62, 152)},
                { "s12", S_parameter_t(0.13, 68)},
                { "s21", std::make_pair(2.9, 64)},
                { "s22", std::make_pair(0.13, -175)}
            }
        },
        {
            std::make_tuple("MRF571", 6, 50, 2000), 
            {
                { "s11", S_parameter_t(0.66, 127)},
                { "s12", S_parameter_t(0.18, 62)},
                { "s21", std::make_pair(2.4, 53)},
                { "s22", std::make_pair(0.11, -178)}
            }
        },
        {
            std::make_tuple("MRF571", 8, 5, 200), 
            {
                { "s11", S_parameter_t(0.75, -83)},
                { "s12", S_parameter_t(0.06, 49)},
                { "s21", std::make_pair(10.7, 129)},
                { "s22", std::make_pair(0.71, -39)}
            }
        },
        {
            std::make_tuple("MRF571", 8, 5, 500), 
            {
                { "s11", S_parameter_t(0.62, -140)},
                { "s12", S_parameter_t(0.08, 34)},
                { "s21", std::make_pair(5.1, 98)},
                { "s22", std::make_pair(0.43, -54)}
            }
        },
        {
            std::make_tuple("MRF571", 8, 5, 1000), 
            {
                { "s11", S_parameter_t(0.6, -179)},
                { "s12", S_parameter_t(0.09, 38)},
                { "s21", std::make_pair(3.7, 78)},
                { "s22", std::make_pair(0.31, -62)}
            }
        },
        {
            std::make_tuple("MRF571", 8, 5, 1500), 
            {
                { "s11", S_parameter_t(0.64, 159)},
                { "s12", S_parameter_t(0.1, 45)},
                { "s21", std::make_pair(2.1, 62)},
                { "s22", std::make_pair(0.29, -80)}
            }
        },
        {
            std::make_tuple("MRF571", 8, 5, 2000), 
            {
                { "s11", S_parameter_t(0.69, 141)},
                { "s12", S_parameter_t(0.13, 52)},
                { "s21", std::make_pair(1.7, 52)},
                { "s22", std::make_pair(0.29, -91)}
            }
        },
        {
            std::make_tuple("MRF571", 8, 10, 200), 
            {
                { "s11", S_parameter_t(0.64, -99)},
                { "s12", S_parameter_t(0.05, 46)},
                { "s21", std::make_pair(15.1, 120)},
                { "s22", std::make_pair(0.54, -60)}
            }
        },
        {
            std::make_tuple("MRF571", 8, 10, 500), 
            {
                { "s11", S_parameter_t(0.52, -152)},
                { "s12", S_parameter_t(0.07, 45)},
                { "s21", std::make_pair(7.1, 94)},
                { "s22", std::make_pair(0.32, -75)}
            }
        },
        {
            std::make_tuple("MRF571", 8, 10, 1000), 
            {
                { "s11", S_parameter_t(0.52, 170)},
                { "s12", S_parameter_t(0.1, 54)},
                { "s21", std::make_pair(3.7, 76)},
                { "s22", std::make_pair(0.15, -82)}
            }
        },
        {
            std::make_tuple("MRF571", 8, 10, 1500), 
            {
                { "s11", S_parameter_t(0.52, 150)},
                { "s12", S_parameter_t(0.13, 56)},
                { "s21", std::make_pair(2.5, 62)},
                { "s22", std::make_pair(0.16, -108)}
            }
        },
        {
            std::make_tuple("MRF571", 8, 10, 2000), 
            {
                { "s11", S_parameter_t(0.57, 133)},
                { "s12", S_parameter_t(0.18, 55)},
                { "s21", std::make_pair(2, 51)},
                { "s22", std::make_pair(0.16, -107)}
            }
        },
        {
            std::make_tuple("MRF571", 8, 50, 200), 
            {
                { "s11", S_parameter_t(0.52, -153)},
                { "s12", S_parameter_t(0.03, 56)},
                { "s21", std::make_pair(19.6, 102)},
                { "s22", std::make_pair(0.28, -92)}
            }
        },
        {
            std::make_tuple("MRF571", 8, 50, 500), 
            {
                { "s11", S_parameter_t(0.52, 178)},
                { "s12", S_parameter_t(0.05, 67)},
                { "s21", std::make_pair(8.1, 86)},
                { "s22", std::make_pair(0.16, -98)}
            }
        },
        {
            std::make_tuple("MRF571", 8, 50, 1000), 
            {
                { "s11", S_parameter_t(0.56, 157)},
                { "s12", S_parameter_t(0.1, 70)},
                { "s21", std::make_pair(4.1, 73)},
                { "s22", std::make_pair(0.06, -130)}
            }
        },
        {
            std::make_tuple("MRF571", 8, 50, 1500), 
            {
                { "s11", S_parameter_t(0.54, 139)},
                { "s12", S_parameter_t(0.13, 68)},
                { "s21", std::make_pair(2.8, 62)},
                { "s22", std::make_pair(0.11, -146)}
            }
        },
        {
            std::make_tuple("MRF571", 8, 50, 2000), 
            {
                { "s11", S_parameter_t(0.59, 126)},
                { "s12", S_parameter_t(0.19, 63)},
                { "s21", std::make_pair(2.2, 52)},
                { "s22", std::make_pair(0.1, -137)}
            }
        },
        


        {
        std::make_tuple("MRF572", 6, 5, 200), 
        {
            { "s11", S_parameter_t(0.81, -73)},
            { "s12", S_parameter_t(0.06, 50)},
            { "s21", std::make_pair(10.9, 134)},
            { "s22", std::make_pair(0.74, -40)}
        }
    },
    {
        std::make_tuple("MRF572", 6, 5, 500), 
        {
            { "s11", S_parameter_t(0.68, -130)},
            { "s12", S_parameter_t(0.09, 29)},
            { "s21", std::make_pair(6.1, 102)},
            { "s22", std::make_pair(0.43, -64)}
        }
    },
    {
        std::make_tuple("MRF572", 6, 5, 1000), 
        {
            { "s11", S_parameter_t(0.66, -167)},
            { "s12", S_parameter_t(0.1, 22)},
            { "s21", std::make_pair(3.3, 79)},
            { "s22", std::make_pair(0.29, -77)}
        }
    },
    {
        std::make_tuple("MRF572", 6, 5, 1500), 
        {
            { "s11", S_parameter_t(0.66, 174)},
            { "s12", S_parameter_t(0.1, 22)},
            { "s21", std::make_pair(2.3, 63)},
            { "s22", std::make_pair(0.27, -94)}
        }
    },
    {
        std::make_tuple("MRF572", 6, 5, 2000), 
        {
            { "s11", S_parameter_t(0.68, 161)},
            { "s12", S_parameter_t(0.11, 23)},
            { "s21", std::make_pair(1.8, 49)},
            { "s22", std::make_pair(0.29, -104)}
        }
    },
    {
        std::make_tuple("MRF572", 6, 10, 200), 
        {
            { "s11", S_parameter_t(0.72, -101)},
            { "s12", S_parameter_t(0.05, 43)},
            { "s21", std::make_pair(15.9, 123)},
            { "s22", std::make_pair(0.57, -58)}
        }
    },
    {
        std::make_tuple("MRF572", 6, 10, 500), 
        {
            { "s11", S_parameter_t(0.66, -150)},
            { "s12", S_parameter_t(0.06, 30)},
            { "s21", std::make_pair(7.7, 95)},
            { "s22", std::make_pair(0.29, -86)}
        }
    },
    {
        std::make_tuple("MRF572", 6, 10, 1000), 
        {
            { "s11", S_parameter_t(0.66, -178)},
            { "s12", S_parameter_t(0.08, 33)},
            { "s21", std::make_pair(4, 77)},
            { "s22", std::make_pair(0.19, -103)}
        }
    },
    {
        std::make_tuple("MRF572", 6, 10, 1500), 
        {
            { "s11", S_parameter_t(0.67, 166)},
            { "s12", S_parameter_t(0.09, 36)},
            { "s21", std::make_pair(2.7, 63)},
            { "s22", std::make_pair(0.19, -122)}
        }
    },
    {
        std::make_tuple("MRF572", 6, 10, 2000), 
        {
            { "s11", S_parameter_t(0.69, 155)},
            { "s12", S_parameter_t(0.1, 37)},
            { "s21", std::make_pair(2.1, 51)},
            { "s22", std::make_pair(0.2, -129)}
        }
    },
    {
        std::make_tuple("MRF572", 6, 50, 200), 
        {
            { "s11", S_parameter_t(0.67, -154)},
            { "s12", S_parameter_t(0.02, 43)},
            { "s21", std::make_pair(21.8, 104)},
            { "s22", std::make_pair(0.3, -94)}
        }
    },
    {
        std::make_tuple("MRF572", 6, 50, 500), 
        {
            { "s11", S_parameter_t(0.68, -177)},
            { "s12", S_parameter_t(0.03, 52)},
            { "s21", std::make_pair(9, 87)},
            { "s22", std::make_pair(0.17, -129)}
        }
    },
    {
        std::make_tuple("MRF572", 6, 50, 1000), 
        {
            { "s11", S_parameter_t(0.7, 167)},
            { "s12", S_parameter_t(0.06, 58)},
            { "s21", std::make_pair(4.5, 74)},
            { "s22", std::make_pair(0.14, -151)}
        }
    },
    {
        std::make_tuple("MRF572", 6, 50, 1500), 
        {
            { "s11", S_parameter_t(0.71, 157)},
            { "s12", S_parameter_t(0.08, 59)},
            { "s21", std::make_pair(3, 62)},
            { "s22", std::make_pair(0.16, -160)}
        }
    },
    {
        std::make_tuple("MRF572", 6, 50, 2000), 
        {
            { "s11", S_parameter_t(0.73, 148)},
            { "s12", S_parameter_t(0.1, 55)},
            { "s21", std::make_pair(2.3, 51)},
            { "s22", std::make_pair(0.17, -161)}
        }
    },
    {
        std::make_tuple("MRF572", 8, 5, 200), 
        {
            { "s11", S_parameter_t(0.83, -69)},
            { "s12", S_parameter_t(0.06, 52)},
            { "s21", std::make_pair(10.9, 136)},
            { "s22", std::make_pair(0.75, -36)}
        }
    },
    {
        std::make_tuple("MRF572", 8, 5, 500), 
        {
            { "s11", S_parameter_t(0.71, -125)},
            { "s12", S_parameter_t(0.08, 30)},
            { "s21", std::make_pair(6.3, 103)},
            { "s22", std::make_pair(0.46, -57)}
        }
    },
    {
        std::make_tuple("MRF572", 8, 5, 1000), 
        {
            { "s11", S_parameter_t(0.64, -164)},
            { "s12", S_parameter_t(0.09, 24)},
            { "s21", std::make_pair(3.5, 80)},
            { "s22", std::make_pair(0.31, -68)}
        }
    },
    {
        std::make_tuple("MRF572", 8, 5, 1500), 
        {
            { "s11", S_parameter_t(0.65, 176)},
            { "s12", S_parameter_t(0.1, 23)},
            { "s21", std::make_pair(2.4, 63)},
            { "s22", std::make_pair(0.29, -84)}
        }
    },
    {
        std::make_tuple("MRF572", 8, 5, 2000), 
        {
            { "s11", S_parameter_t(0.66, 163)},
            { "s12", S_parameter_t(0.11, 24)},
            { "s21", std::make_pair(1.8, 49)},
            { "s22", std::make_pair(0.3, -94)}
        }
    },
    {
        std::make_tuple("MRF572", 8, 10, 200), 
        {
            { "s11", S_parameter_t(0.74, -94)},
            { "s12", S_parameter_t(0.05, 45)},
            { "s21", std::make_pair(16.2, 125)},
            { "s22", std::make_pair(0.6, -51)}
        }
    },
    {
        std::make_tuple("MRF572", 8, 10, 500), 
        {
            { "s11", S_parameter_t(0.65, -146)},
            { "s12", S_parameter_t(0.06, 32)},
            { "s21", std::make_pair(7.9, 96)},
            { "s22", std::make_pair(0.31, -74)}
        }
    },
    {
        std::make_tuple("MRF572", 8, 10, 1000), 
        {
            { "s11", S_parameter_t(0.64, -176)},
            { "s12", S_parameter_t(0.07, 33)},
            { "s21", std::make_pair(4.2, 77)},
            { "s22", std::make_pair(0.2, -87)}
        }
    },
    {
        std::make_tuple("MRF572", 8, 10, 1500), 
        {
            { "s11", S_parameter_t(0.65, 168)},
            { "s12", S_parameter_t(0.09, 36)},
            { "s21", std::make_pair(2.8, 63)},
            { "s22", std::make_pair(0.19, -104)}
        }
    },
    {
        std::make_tuple("MRF572", 8, 10, 2000), 
        {
            { "s11", S_parameter_t(0.67, 156)},
            { "s12", S_parameter_t(0.1, 37)},
            { "s21", std::make_pair(2.2, 50)},
            { "s22", std::make_pair(0.2, -111)}
        }
    },
    {
        std::make_tuple("MRF572", 8, 50, 200), 
        {
            { "s11", S_parameter_t(0.62, -150)},
            { "s12", S_parameter_t(0.02, 43)},
            { "s21", std::make_pair(22.7, 104)},
            { "s22", std::make_pair(0.3, -81)}
        }
    },
    {
        std::make_tuple("MRF572", 8, 50, 500), 
        {
            { "s11", S_parameter_t(0.64, -174)},
            { "s12", S_parameter_t(0.03, 51)},
            { "s21", std::make_pair(9.4, 86)},
            { "s22", std::make_pair(0.15, -107)}
        }
    },
    {
        std::make_tuple("MRF572", 8, 50, 1000), 
        {
            { "s11", S_parameter_t(0.68, 167)},
            { "s12", S_parameter_t(0.05, 58)},
            { "s21", std::make_pair(4.8, 74)},
            { "s22", std::make_pair(0.1, -126)}
        }
    },
    {
        std::make_tuple("MRF572", 8, 50, 1500), 
        {
            { "s11", S_parameter_t(0.69, 160)},
            { "s12", S_parameter_t(0.07, 58)},
            { "s21", std::make_pair(3.2, 61)},
            { "s22", std::make_pair(0.13, -140)}
        }
    },
    {
        std::make_tuple("MRF572", 8, 50, 2000), 
        {
            { "s11", S_parameter_t(0.7, 147)},
            { "s12", S_parameter_t(0.09, 55)},
            { "s21", std::make_pair(2.4, 50)},
            { "s22", std::make_pair(0.15, -140)}
        }
    },
    
};











/////// NOISE PARAMETERS OF MRF571 and MRF572 /////////

std::map<S_param_polarization_t, S_noise_map_t> 
MRF_transistor_noise_parameters = {
    {
        std::make_tuple("MRF571", 6, 5, 500), 
        {
            { "NF_opt_db",          0.9},
            { "R_n",                9.3},
            { "Gamma_S_on_mag",     0.49},
            { "Gamma_S_on_arg",     74},
        }
    },
    {
        std::make_tuple("MRF571", 6, 5, 1000), 
        {
            { "NF_opt_db",          1.5},
            { "R_n",                7.5},
            { "Gamma_S_on_mag",     0.48},
            { "Gamma_S_on_arg",     134},
        }
    },


    {
        std::make_tuple("MRF572", 6, 5, 500), 
        {
            { "NF_opt_db",          1.0},
            { "R_n",                17.1},
            { "Gamma_S_on_mag",     0.43},
            { "Gamma_S_on_arg",     57},
        }
    },
    {
        std::make_tuple("MRF572", 6, 5, 1000), 
        {
            { "NF_opt_db",          1.5},
            { "R_n",                6.0},
            { "Gamma_S_on_mag",     0.56},
            { "Gamma_S_on_arg",     116},
        }
    }


};

#endif