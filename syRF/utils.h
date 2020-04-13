/***************************************************************************
**                                                                        **
**  syRF                                                                  **
**  Copyright (C) 2019 Francesco Urbani                                   **
**                                                                        **
****************************************************************************
**  Author:         Francesco Urbani <https://urbanij.github.io/>         **
**  Date:           Sun Apr 12 19:02:02 CEST 2020                         **
**  File:           utils.h                                               **
**  Description:    various utils and functions used throghout the project**
****************************************************************************/

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




#endif // UTILS_H
