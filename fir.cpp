//------------------------------------------------------------------------------
//
//          This file is part of the DSPLAB C++ Library.
//
//          Copyright (c) 2019-2021 Yuta Harigae
//
//          Licensed under the Apache License, Version 2.0 (the "License").
//
//------------------------------------------------------------------------------

#include "fir.hpp"

dsplab::filter::FIR::FIR() {

    n = 0u;
    coefficients = nullptr;
    frequency_response = nullptr;
    delays = nullptr;
    group_delay = nullptr;
    normalized_angular_frequency = nullptr;
    s = 0u;
    sin_w = nullptr;
}

dsplab::filter::FIR::~FIR() {
    Clear();
}

void dsplab::filter::FIR::Clear() {
    n = 0u;
    s = 0u;
    coefficients = nullptr;
    normalized_angular_frequency = nullptr;

    delete[] frequency_response;
    frequency_response = nullptr;

    delete[] delays;
    delays = nullptr;

    delete[] group_delay;
    group_delay = nullptr;

    delete[] sin_w;
    sin_w = nullptr;
}

bool dsplab::filter::FIR::SetCoefficients(double* coefficients, unsigned int n) {

    if (nullptr == coefficients) return false;
    if (0u == n) return false;
    if (nullptr != delays) Clear();

    FIR::coefficients = coefficients;
    FIR::n = n;

    delays = new double[n];
    for (unsigned int i = 0u; i < n; i++) {
        delays[i] = 0.0;
    }

    return true;
}

void dsplab::filter::FIR::SetCoefficients(double* coefficients) {

    FIR::coefficients = coefficients;
}

bool dsplab::filter::FIR::SetFrequencySample(double* normalized_angular_frequency, unsigned int s) {

    if (nullptr == normalized_angular_frequency) return false;
    if (s < 2u) return false;
    if (nullptr != frequency_response) {
        delete[] frequency_response;
        frequency_response = nullptr;
        delete[] group_delay;
        group_delay = nullptr;
        delete[] sin_w;
        sin_w = nullptr;
    }

    FIR::normalized_angular_frequency = normalized_angular_frequency;
    FIR::s = s;

    sin_w = new std::complex<double>[s];
    frequency_response = new std::complex<double>[s];
    group_delay = new double[s];

    for (unsigned int i = 0u; i < s; i++) {
        group_delay[i] = 0.0;
        sin_w[i].real(std::cos(normalized_angular_frequency[i]));
        sin_w[i].imag(-std::sin(normalized_angular_frequency[i]));
    }

    return true;
}

bool dsplab::filter::FIR::CalculateFrequencyResponse() {

    if (nullptr == frequency_response) return false;
    if (nullptr == coefficients) return false;

    for (unsigned int i = 0u; i < s; i++) {
        frequency_response[i] = dsplab::math::Polynomial::ReverseHorner(coefficients, n + 1, sin_w[i]);
    }

    return true;
}

bool dsplab::filter::FIR::CalculateGroupDelay() {

    if (nullptr == group_delay) return false;
    if (nullptr == coefficients) return false;

    if (!CalculateFrequencyResponse()) return false;
    unsigned int i, j;
    std::complex<double> numerator;
    for (i = 0u; i < s; i++) {
        numerator = n * coefficients[n];
         for (j = n - 1u; j >= 1u; j--) {
            numerator *= sin_w[i];
            numerator += j * coefficients[j];
        }
        numerator *= sin_w[i];
        group_delay[i] = (numerator / frequency_response[i]).real();
    }
    return true;
}

double dsplab::filter::FIR::operator() (const double& input) {

    if (nullptr == delays) return 0.0;
    if (nullptr == coefficients) return 0.0;

    double output = 0.0;
    unsigned int i;
    output += coefficients[0] * input;
    for (i = 0u; i < n; i++) output += coefficients[i + 1u] * delays[i];
    for (i = n - 1u; i >= 1u; i--) delays[i] = delays[i - 1u];
    delays[0] = input;
    return output;                                                                                                                                                                                                    
}

const std::complex<double>& dsplab::filter::FIR::operator[](unsigned int index) const {
    
    static std::complex<double> buff;
    buff = 0.0;
    if (nullptr == frequency_response) return buff;
    if (index >= s) return buff;
    return frequency_response[index];
}

bool dsplab::filter::FIR::WriteCoefficients(const char* filename) {

    if (nullptr == filename) return false;
    if (nullptr == coefficients) return false;

    FILE *fp = nullptr;
    fp = std::fopen(filename, "w");
    if (nullptr == fp) return false;

    for (unsigned int i = 0u; i < n + 1u; i++) {
        std::fprintf(fp, "h_%u,%-16.15lf\n", i, coefficients[i]);
    }
    std::fclose(fp);
    fp = nullptr;
    return true;
}

bool dsplab::filter::FIR::WriteFrequencyResponse(const char* filename) {

    if (nullptr == filename) return false;
    if (nullptr == normalized_angular_frequency) return false;
    if (nullptr == frequency_response) return false;

    FILE *fp = nullptr;
    fp = std::fopen(filename, "w");
    if (nullptr == fp) return false;

    for (unsigned int i = 0u; i < s; i++) {
        std::fprintf(fp, "%-16.15lf,%-16.15lf,%-16.15lf\n", normalized_angular_frequency[i], frequency_response[i].real(), frequency_response[i].imag());
    }
    std::fclose(fp);
    fp = nullptr;
    return true;
}

bool dsplab::filter::FIR::WriteMagnitudeResponse(const char* filename, bool decibel) {

    if (nullptr == filename) return false;
    if (nullptr == normalized_angular_frequency) return false;
    if (nullptr == frequency_response) return false;

    FILE *fp = nullptr;
    fp = std::fopen(filename, "w");
    if (nullptr == fp) return false;

    if (decibel) {
        double db = 0.0;
        for (unsigned int i = 0u; i < s; i++) {
            db = 20.0 * std::log10(std::abs(frequency_response[i]));
            std::fprintf(fp, "%-16.15lf,%-16.15lf\n", normalized_angular_frequency[i], db);
        }
    }
    else {
        for (unsigned int i = 0u; i < s; i++) {
            std::fprintf(fp, "%-16.15lf,%-16.15lf\n", normalized_angular_frequency[i], std::abs(frequency_response[i]));
        }
    }
    std::fclose(fp);
    fp = nullptr;
    return true;
}

bool dsplab::filter::FIR::WritePhaseResponse(const char* filename) {

    if (nullptr == filename) return false;
    if (nullptr == normalized_angular_frequency) return false;
    if (nullptr == frequency_response) return false;

    FILE *fp = nullptr;
    fp = std::fopen(filename, "w");
    if (nullptr == fp) return false;

    for (unsigned int i = 0u; i < s; i++) {
        std::fprintf(fp, "%-16.15lf,%-16.15lf\n", normalized_angular_frequency[i], std::arg(frequency_response[i]));
    }
    std::fclose(fp);
    fp = nullptr;
    return true;
}

bool dsplab::filter::FIR::WriteGroupDelay(const char* filename) {

    if (nullptr == filename) return false;
    if (nullptr == normalized_angular_frequency) return false;
    if (nullptr == group_delay) return false;

    FILE *fp = nullptr;
    fp = std::fopen(filename, "w");
    if (nullptr == fp) return false;

    for (unsigned int i = 0u; i < s; i++) {
        std::fprintf(fp, "%-16.15lf,%-16.15lf\n", normalized_angular_frequency[i], group_delay[i]);
    }
    std::fclose(fp);
    fp = nullptr;
    return true;
}

bool dsplab::filter::FIR::WriteZeros(const char* filename)  {

    if (nullptr == filename) return false;
    if (nullptr == coefficients) return false;

    std::complex<double> *coef = new std::complex<double>[n];
    std::complex<double> *zeros = new std::complex<double>[n];

    unsigned int i;
    for (i = 0u; i < n; i++) {
        coef[i] = coefficients[i + 1u] / coefficients[0];
    }
    dsplab::math::Polynomial::DKAMethod(zeros, coef, n);

    FILE *fp = nullptr;
    fp = std::fopen(filename, "w");
    if (nullptr == fp) return false;

    for (i = 0u; i < n; i++) {
        std::fprintf(fp, "%-16.15lf,%-16.15lf\n", zeros[i].real(), zeros[i].imag());
    }
    std::fclose(fp);
    fp = nullptr;
    delete[] coef;
    coef = nullptr;
    delete[] zeros;
    zeros = nullptr;
    return true;
}

bool dsplab::filter::FIR::CreateFrequencySample(double *normalized_angular_frequency, unsigned int s) {
    
    if (nullptr == normalized_angular_frequency) return false;
    if (s < 2u) return false;

    double delta = dsplab::constants::PI / (s - 1u);

    for (unsigned int i = 0u; i < s; i++) {
        normalized_angular_frequency[i] = i * delta;
    }
    return true;
}