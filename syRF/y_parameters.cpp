/***************************************************************************
**                                                                        **
**  syRF                                                                  **
**  Copyright (C) 2019 Francesco Urbani                                   **
**                                                                        **
****************************************************************************
**  Author:         Francesco Urbani <https://urbanij.github.io/>         **
**  Date:           Wed Dec 11 19:48:18 CET 2019                          **
**  File:           y_parameters.cpp                                      **
**  Description:                                                          **
****************************************************************************/

#include "y_parameters.h"

float compute_C(float yie, float yfe, float yoe, float yre){
    return yie+yfe+yoe+yre;
}

