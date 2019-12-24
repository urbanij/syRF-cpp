#ifndef CCOMPLEX_H
#define CCOMPLEX_H

#include <iostream>
#include <QString>


class ccomplex {

    double _re;
    double _im;

public:
    ccomplex(const std::string& str);
    ccomplex(double real = 0, double imag = 0);

    double Re() const;
    double Im() const;

    friend std::ostream& operator<<( std::ostream& in, const ccomplex& b );
    friend std::istream& operator>>( std::istream& in, ccomplex& c );

};


#endif // CCOMPLEX_H
