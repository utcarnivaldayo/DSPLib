//------------------------------------------------------------------------------
//
//          This file is part of the DSPLAB C++ Library.
//
//          Copyright (c) 2019-2021 Yuta Harigae
//
//          Licensed under the Apache License, Version 2.0 (the "License").
//
//------------------------------------------------------------------------------

#ifndef _DSPLAB_FIR_HPP_
#define _DSPLAB_FIR_HPP_
#include <cmath>
#include <cstdio>
#include <complex>
#include "polynomial.hpp"
#include "constants.hpp"
#if defined(_MSC_VER) && _MSC_VER >= 1910
#pragma warning(disable:4996)
#endif

namespace dsplab {

    namespace filter {

        class FIR {

            private:
                unsigned int n;
                double* coefficients;
                std::complex<double>* frequency_response;
                double* delays;
                double* group_delay;
                double* normalized_angular_frequency;
                std::complex<double> *sin_w;
                unsigned int s;

            public:
                FIR();
                ~FIR();
                FIR(const FIR &copy) = delete;
                FIR &operator=(const FIR &copy) = delete;
                bool SetCoefficients(double* coefficients, unsigned int n);
                void SetCoefficients(double* coefficients);
                bool SetFrequencySample(double* normalized_angular_frequency, unsigned int s);
                inline unsigned int GetN() const { return n;}
                inline unsigned int GetS() const { return s;}
                bool CalculateFrequencyResponse();
		    	bool CalculateGroupDelay();
                double operator() (const double& input);
                std::complex<double>& operator[](unsigned int index);
                const std::complex<double>& operator[](unsigned int index) const;
                bool WriteCoefficients(const char* filename);
                bool WriteFrequencyResponse(const char* filename);
                bool WriteMagnitudeResponse(const char* filename, bool decibel = true);
                bool WritePhaseResponse(const char* filename);
                bool WriteGroupDelay(const char* filename);
                bool WriteZeros(const char *filename);
                bool ClearDelays();
                void Clear();
                static bool CreateFrequencySample(double *normalized_angular_frequency, unsigned int s);
        };
    }
}
#endif