/***************************************************************************
**                                                                        **
**  syRF                                                                  **
**  Copyright (C) 2019 Francesco Urbani                                   **
**                                                                        **
****************************************************************************
**  Author:         Francesco Urbani <https://urbanij.github.io/>         **
**  Date:           Wed Dec 11 19:48:18 CET 2019                          **
**  File:           y_parameters.h                                        **
**  Description:                                                          **
****************************************************************************/

#ifndef Y_PARAMETERS_H
#define Y_PARAMETERS_H

#include <complex>

/**
 * @brief compute_C
 * @param yie
 * @param yfe
 * @param yoe
 * @param yre
 * @return
 */
float compute_C(std::complex<float> yie, std::complex<float> yfe, std::complex<float> yoe, std::complex<float> yre);




#endif // Y_PARAMETERS_H
