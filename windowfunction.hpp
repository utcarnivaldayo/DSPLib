//------------------------------------------------------------------------------
//
//          This file is part of the DSPLAB C++ Library.
//
//          Copyright (c) 2019-2021 Yuta Harigae
//
//          Licensed under the Apache License, Version 2.0 (the "License").
//
//------------------------------------------------------------------------------

#ifndef _DSPLAB_WINDOWFUNCTION_HPP_
#define _DSPLAB_WINDOWFUNCTION_HPP_
#include <cmath>
#include "constants.hpp"

namespace dsplab {

    namespace math {

        class WindowFunction {
            private:
                WindowFunction(){}
                WindowFunction(const WindowFunction &copy){}
                ~WindowFunction(){}
                WindowFunction &operator=(const WindowFunction &copy) { return *this; }
            
            public:
                static inline double Rectangular(double x) { return 1.0; }
                static inline double Hanning(double x) { return (0.5 + 0.5 * std::cos(dsplab::constants::DOUBLE_PI * x)); }
                static inline double Hamming(double x) { return (0.54 - 0.46 * std::cos(dsplab::constants::DOUBLE_PI * x)); }
                static inline double Blackman(double x) { return (0.42 - 0.5 * std::cos(dsplab::constants::DOUBLE_PI * x) + 0.08 * std::cos(2.0 * dsplab::constants::DOUBLE_PI * x)); }
                static inline double Triangular(double x) { return (1.0 - 2.0 * std::fabs(x - 0.5)); }
                static inline double BartlettHann(double x) { return (0.62 - 0.48 * std::fabs(x - 0.5) - 0.38 * std::cos(dsplab::constants::DOUBLE_PI * x)); }
                static inline double BlackmanNuttall(double x) { return (0.3635819 - 0.4891775 * std::cos(dsplab::constants::DOUBLE_PI * x) + 0.1365995 * std::cos(2.0 * dsplab::constants::DOUBLE_PI * x) - 0.0106411 * std::cos(3.0 * dsplab::constants::DOUBLE_PI * x)); }
                static inline double Parzen(double x) { return (std::fabs(x) <= 1.0) ? (1.0 - 1.5 * x * x + 0.75 * std::pow(std::fabs(x), 3.0)) : 0.25 * std::pow(2.0 - std::fabs(x), 3.0); }
                static inline double Akaike(double x) { return 0.625 - 0.5 * std::cos(dsplab::constants::DOUBLE_PI * x) - 0.125 * std::cos(2.0 * dsplab::constants::DOUBLE_PI * x); }
        };
    }
}

#endif