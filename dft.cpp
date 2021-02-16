//------------------------------------------------------------------------------
//
//          The file is part of the DSPLAB Library.
//
//          Copyright (c) 2019-2021 Yuta Harigae
//
//          Licensed under the Apache License, Version 2.0 (the "License").
//
//------------------------------------------------------------------------------

#include "dft.hpp"

bool DFT(std::complex<double>* frequency_domain, std::complex<double>* time_domain, unsigned int frame_length) {

    if (nullptr == frequency_domain) return false;
    if (nullptr == time_domain) return false;
    if (frame_length < 2u) return false;

    unsigned int i, j;
    std::complex<double> w;
    for (i = 0u; i < frame_length; i++) {
        w.real(std::cos(dsplab::constants::DOUBLE_PI * i / (double)frame_length));
        w.imag(-std::sin(dsplab::constants::DOUBLE_PI * i / (double)frame_length));
        frequency_domain[i] = dsplab::math::Polynomial::ReverseHorner(time_domain, frame_length, w);
    }
    return true;
}

bool IDFT(std::complex<double> *time_domain, std::complex<double> *frequency_domain, unsigned int frame_length) {

    if (nullptr == time_domain) return false;
    if (nullptr == frequency_domain) return false;

    unsigned int i, j;
    std::complex<double> w;
    for (i = 0u; i < frame_length; i++) {
        w.real(std::cos(dsplab::constants::DOUBLE_PI * i / (double)frame_length));
        w.imag(std::sin(dsplab::constants::DOUBLE_PI * i / (double)frame_length));
        time_domain[i] = dsplab::math::Polynomial::ReverseHorner(frequency_domain, frame_length, w);
        time_domain[i] /= (double)frame_length;
    }
    return true;
}

bool FFT(std::complex<double>* frequency_domain, double* time_domain, unsigned int frame_length) {

    if (nullptr == frequency_domain) return false;
    if (nullptr == time_domain) return false;

    return true;
}

bool IFFT(double *time_domain, std::complex<double> *frequency_domain, unsigned int frame_length) {

    if (nullptr == time_domain) return false;
    if (nullptr == frequency_domain) return false;
    
    return true;
}