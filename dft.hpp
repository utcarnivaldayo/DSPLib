//------------------------------------------------------------------------------
//
//          The file is part of the DSPLAB Library.
//
//          Copyright (c) 2019-2021 Yuta Harigae
//
//          Licensed under the Apache License, Version 2.0 (the "License").
//
//------------------------------------------------------------------------------

#ifndef _DSPLAB_DFT_HPP_
#define _DSPLAB_DFT_HPP_
#include <cmath>
#include <complex>
#include <cstdio>
#include "constants.hpp"
#include "polynomial.hpp"

namespace dsplab {

    namespace filter {

        class FrequencyAnalysis {

            private:
                FrequencyAnalysis(){}
                FrequencyAnalysis(const FrequencyAnalysis &copy){}
                ~FrequencyAnalysis(){}
                FrequencyAnalysis &operator=(const FrequencyAnalysis &copy) { return *this; }

            public:
                static bool DFT(std::complex<double>* frequency_domain, std::complex<double>* time_domain, unsigned int frame_length);
                static bool IDFT(std::complex<double> *time_domain, std::complex<double> *frequency_domain, unsigned int frame_length);
                static bool FFT(std::complex<double> *frequency_domain, std::complex<double> *time_domain, unsigned int frame_length);
                static bool IFFT(std::complex<double>* time_domain, std::complex<double> *frequency_domain, unsigned int frame_length);
        };
    }
}
#endif