
#include <cmath>
#include <sstream>
#include <regex>
#include <iostream>

#include <QDebug>
#include "ccomplex.h"



ccomplex::ccomplex(const std::string& str) {
    double real = 0.0, imag = 0.0;

    std::regex realRegex("^(-)?\\s*(\\d+(\\.\\d+)?)$");
    std::regex imagRegex("^(-)?\\s*(\\d+(\\.\\d+)?)j$");
    std::regex bothRegex("^(-)?\\s*(\\d+(\\.\\d+)?)\\s*([-+])\\s*(\\d+(\\.\\d+)?)j$");
    std::smatch match;
    if (std::regex_match(str.begin(), str.end(), match, realRegex)) {
        real = std::atof(match[2].str().c_str());
        if (match[1].matched) {
            real = -real;
        }
    } else if (std::regex_match(str.begin(), str.end(), match, imagRegex)) {
        imag = std::atof(match[2].str().c_str());
        if (match[1].matched) {
            imag = -imag;
        }
    } else if (std::regex_match(str.begin(), str.end(), match, bothRegex)) {
        real = std::atof(match[2].str().c_str());
        imag = std::atof(match[5].str().c_str());
        if (match[1].matched) {
            real = -real;
        }
        if (match[4].str() == "-") {
            imag = -imag;
        }
    }
    else {
//        throw std::runtime_error("Invalid number format " + str);
        qDebug("Invalid number format ");

    }
    _re = real;
    _im = imag;
}

ccomplex::ccomplex(double real, double imag) {
    _re = real;
    _im = imag;
}

double ccomplex::Re() const {
    return _re;
}

double ccomplex::Im() const {
    return _im;
}


// Pretty prints ccomplex

std::ostream& operator<<( std::ostream &out, const ccomplex& b ) {

    bool realPrinted = false;

    if (b._re != 0 || (b._re == 0 && b._im == 0)) {
        out << b._re;
        realPrinted = true;
    }

    if (b._im > 0) {
        if (realPrinted) {
            out << "+";
        }
        if (b._im != 1) {
            out << b._im;
        }
        out << "j";
    }

    else if (b._im < 0) {
        if (b._im == -1) {
            out << "-";
        }
        else {
            out << b._im;
        }
        out << "j";
    }

    return out;
}

// natural extraction operator for ccomplexs

std::istream& operator>> ( std::istream& in, ccomplex& z ) {

    std::string complexText;
    int plusPos, minusPos, i_Pos;
    double coefficient1;
    bool real, imag;

    in >> coefficient1; // fails for pure imag nums converts "bi" to zero.
    getline(std::cin, complexText);

    plusPos = complexText.find('+');
    minusPos = complexText.find('-');
    i_Pos = complexText.find('j');

    real = i_Pos < 0; // real number won't contain the character i
    imag = minusPos < 0 && plusPos < 0; // pure imag number if no + or -

    if (real) {
        z._re = coefficient1;
        z._im = 0.0;
    }

    else if (imag) {
        z._re = 0.0;
        z._im = coefficient1;
    }

    else {
        z._re = coefficient1;

        complexText.replace(i_Pos,1," ");

        if (plusPos >= 0)
            complexText.replace(plusPos,1," ");

        if (minusPos >= 0)
            complexText.replace(minusPos,1," ");

        z._im = atof(complexText.c_str());

        if (z._im == 0)
            z._im = 1; // 1 + i, 1 - i

        if (minusPos >= 0)
            z._im = -z._im;
    }

    return in;
}
