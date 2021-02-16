//------------------------------------------------------------------------------
//
//          This file is part of the DSPLAB C++ Library.
//
//          Copyright (c) 2019-2021 Yuta Harigae
//
//          Licensed under the Apache License, Version 2.0 (the "License").
//
//------------------------------------------------------------------------------

#ifndef _DSPLAB_POLYNOMIAL_HPP_
#define _DSPLAB_POLYNOMIAL_HPP_
#include <cmath>
#include <complex>
#include "constants.hpp"

namespace dsplab {

	namespace math {

        class Polynomial {
            private:
                Polynomial(){}
                Polynomial(const Polynomial &copy){}
                ~Polynomial(){}
                Polynomial &operator=(const Polynomial &copy) { return *this; }
                static std::complex<double> DenominatorOfSecondOrderMethod(std::complex<double> *zeros, unsigned int n, unsigned int index);

            public:
                static bool QuadraticFormula(std::complex<double> *roots, double c_1, double c_2, double c_0 = 1.0);
                static bool VietaFormula(double *coefficients, std::complex<double> *roots, unsigned int n, double scaling_coefficient = 1.0);
                static std::complex<double> Horner(double *coefficients, unsigned int n, std::complex<double> &z, double non_monic = 1.0);
                static std::complex<double> Horner(std::complex<double> *coefficients, unsigned int n, std::complex<double> &z, std::complex<double> non_monic = 1.0);
                static double Horner(double *coefficients, unsigned int n, double &z, double non_monic = 1.0);
                static std::complex<double> ReverseHorner(double *coefficients, unsigned int length, std::complex<double> &z);
                static std::complex<double> ReverseHorner(std::complex<double> *coefficients, unsigned int length, std::complex<double> &z);
                static bool DKAMethod(std::complex<double> *zeros, std::complex<double> *coefficients, unsigned int n);
        };
    }
}
#endif