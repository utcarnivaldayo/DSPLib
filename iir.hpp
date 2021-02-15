//------------------------------------------------------------------------------
//
//          This file is part of the DSPLAB C++ Library.
//
//          Copyright (c) 2019-2021 Yuta Harigae
//
//          Licensed under the Apache License, Version 2.0 (the "License").
//
//------------------------------------------------------------------------------

#ifndef _DSPLAB_IIR_HPP_
#define _DSPLAB_IIR_HPP_
#include <cmath>
#include <cstdio>
#include <complex>
#include "constants.hpp"
#include "polynomial.hpp"
#if defined(_MSC_VER) && _MSC_VER >= 1910
#pragma warning(disable:4996)
#endif

namespace dsplab {

	namespace filter {

	    class IIR {
            private:
                unsigned int n;
                unsigned int m;
                unsigned int harf_n;
                unsigned int harf_m;
                bool n_odd;
                bool m_odd;
                double *scaling_coefficient;
                double *numerator_coefficients;
                double *denominator_coefficients;
                double *delays;
                unsigned int delays_length;
                double *group_delay;
                double *normalized_angular_frequency;
                std::complex<double> *sin_w;
                std::complex<double> *sin_2w;
                std::complex<double> *frequency_response;
                unsigned int s;

            public:
                IIR();
                ~IIR();
                IIR(const IIR &copy) = delete;
                IIR& operator=(const IIR &copy) = delete;
                bool SetCoefficients(double *scaling_coefficient, double *numerator_coefficients, double *denominator_coefficients, unsigned int n, unsigned int m);
                void SetCoefficients(double *scaling_coefficient, double *numerator_coefficients, double *denominator_coefficients);
                bool SetFrequencySample(double *normalized_angular_frequency, unsigned int s);
                inline unsigned int GetN() const { return n; }
                inline unsigned int GetM() const { return m; }
                inline unsigned int GetS() const { return s; }
                inline unsigned int GetDelaysLength() const { return delays_length; }
                double operator()(const double &input);
                const std::complex<double>& operator[](unsigned int index) const;
                bool CalculateFrequencyResponse();
                bool CalculateGroupDelay();
                bool IsStability();
                bool WriteCoefficients(const char *filename);
                bool WriteFrequencyResponse(const char *filename);
                bool WriteMagnitudeResponse(const char *filename, bool decibel = true);
                bool WritePhaseResponse(const char *filename);
                bool WriteGroupDelay(const char *filename);
                bool WriteZeros(const char *filename);
                bool WritePoles(const char *filename);
                bool ClearDelays();
                void Clear();
                static bool CreateFrequencySample(double *normalized_angular_frequency, unsigned int s);
                static bool ToSymmetry(double *numerator_coefficients, double *denominator_coefficients, unsigned int n, unsigned int m);
                static bool StabilityTriangle(const double &b_1, const double &b_2);
                static bool StabilityOfRealRoot(const double &b_1);
                static bool CoefficientsToZeros(std::complex<double> *zeros, double *coefficients, unsigned int n);
        };
    }
}
#endif