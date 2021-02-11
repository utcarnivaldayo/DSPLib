//------------------------------------------------------------------------------
//
//          The file is part of the DSPLAB Library.
//
//          Copyright (c) 2019-2021 Yuta Harigae
//
//          Licensed under the Apache License, Version 2.0 (the "License").
//
//------------------------------------------------------------------------------

#include "iir.hpp"

dsplab::filter::IIR::IIR() {
    n = 0u;
    m = 0u;
    harf_n = 0u;
    harf_m = 0u;
    n_odd = false;
    m_odd = false;
    scaling_coefficient = nullptr;
    numerator_coefficients = nullptr;
    denominator_coefficients = nullptr;
    delays = nullptr;
    delays_length = 0u;
    group_delay = nullptr;
    normalized_angular_frequency = nullptr;
    sin_w = nullptr;
    sin_2w = nullptr;
    frequency_response = nullptr;
    s = 0u;
}

dsplab::filter::IIR::~IIR() {
    Clear();
}

void dsplab::filter::IIR::Clear() {
    n = 0u;
    m = 0u;
    harf_n = 0u;
    harf_m = 0u;
    n_odd = false;
    m_odd = false;
    scaling_coefficient = nullptr;
    numerator_coefficients = nullptr;
    denominator_coefficients = nullptr;
    normalized_angular_frequency = nullptr;
    s = 0u;
    delays_length = 0u;

    delete[] delays;
    delays = nullptr;

    delete[] group_delay;
    group_delay = nullptr;

    delete[] sin_w;
    sin_w = nullptr;

    delete[] sin_2w;
    sin_2w = nullptr;

    delete[] frequency_response;
    frequency_response = nullptr;
}

bool dsplab::filter::IIR::SetCoefficients(double *scaling_coefficient, double *numerator_coefficients, double *denominator_coefficients, unsigned int n, unsigned int m) {

    if (0 == n && 0 == m) return false;
    if (nullptr != IIR::delays) Clear();

    IIR::scaling_coefficient = scaling_coefficient;
    IIR::numerator_coefficients = numerator_coefficients;
    IIR::denominator_coefficients = denominator_coefficients;
    IIR::n = n;
    IIR::m = m;
    IIR::harf_n = n >> 1u;
    IIR::harf_m = m >> 1u;
    IIR::n_odd = (1u == n % 2u) ? true : false;
    IIR::m_odd = (1u == m % 2u) ? true : false;
    IIR::delays_length = (n >= m) ? n : m;
    IIR::delays = new double[delays_length];

    for (unsigned int i = 0u; i < delays_length; i++) {
        delays[i] = 0.0;
    }

    return true;
}

void dsplab::filter::IIR::SetCoefficients(double *scaling_coefficient, double *numerator_coefficients, double *denominator_coefficients) {

    IIR::scaling_coefficient = scaling_coefficient;
    IIR::numerator_coefficients = numerator_coefficients;
    IIR::denominator_coefficients = denominator_coefficients;
}

bool dsplab::filter::IIR::SetFrequencySample(double *normalized_angular_frequency, unsigned int s) {

    if (nullptr == normalized_angular_frequency) return false;
    if (s < 2u) return false;
    if (nullptr != frequency_response) {
        delete[] frequency_response;
        frequency_response = nullptr;
        delete[] group_delay;
        group_delay = nullptr;
        delete[] sin_w;
        sin_w = nullptr;
        delete[] sin_2w;
        sin_2w = nullptr;
    }

    IIR::normalized_angular_frequency = normalized_angular_frequency;
    IIR::s = s;

    frequency_response = new std::complex<double>[s];
    group_delay = new double[s];
    sin_w = new std::complex<double>[s];
    sin_2w = new std::complex<double>[s];

    for (unsigned int i = 0u; i < s; i++) {
        group_delay[i] = 0.0;
        sin_w[i].real(std::cos(normalized_angular_frequency[i]));
        sin_w[i].imag(-std::sin(normalized_angular_frequency[i]));
        sin_2w[i].real(std::cos(2.0 * normalized_angular_frequency[i]));
        sin_2w[i].imag(-std::sin(2.0 * normalized_angular_frequency[i]));
    }
    return true;
}

bool dsplab::filter::IIR::CalculateFrequencyResponse() {

    if (nullptr == scaling_coefficient) return false;
    if (nullptr == numerator_coefficients) return false;
    if (nullptr == denominator_coefficients) return false;
    if (nullptr == frequency_response) return false;

    unsigned int i, j, base_index;
    for (i = 0u; i < s; i++) {
        frequency_response[i] = *scaling_coefficient;
        for (j = 0u; j < harf_n; j++) {
            base_index = j << 1u;
            frequency_response[i] *= 1.0 + numerator_coefficients[base_index] * sin_w[i] + numerator_coefficients[base_index + 1] * sin_2w[i];
        }

        for (j = 0u; j < harf_m; j++) {
            base_index = j << 1u;
            frequency_response[i] /= 1.0 + denominator_coefficients[base_index] * sin_w[i] + denominator_coefficients[base_index + 1] * sin_2w[i];
        }
    }

    if (n_odd) {
        for (i = 0u; i < s; i++) {
            frequency_response[i] *= 1.0 + numerator_coefficients[n - 1u] * sin_w[i];
        }
    }

    if (m_odd) {
        for (i = 0u; i < s; i++) {
            frequency_response[i] /= 1.0 + denominator_coefficients[m - 1u] * sin_w[i];
        }
    }
    return true;
}

bool dsplab::filter::IIR::CalculateGroupDelay() {

    if (nullptr == scaling_coefficient) return false;
    if (nullptr == numerator_coefficients) return false;
    if (nullptr == denominator_coefficients) return false;

    unsigned int i, j, base_index, base_next_index;
    std::complex<double> buff;
    for (i = 0u; i < s; i++) {
        group_delay[i] = 0.0;
        for (j = 0u; j < harf_n; j++) {
            base_index = j << 1u;
            base_next_index = base_index + 1u;
            buff += (numerator_coefficients[base_index] * sin_w[i] + 2.0 * numerator_coefficients[base_next_index] * sin_2w[i]) / (1.0 + numerator_coefficients[base_index] * sin_w[i] + numerator_coefficients[base_next_index] * sin_2w[i]);
        }
        group_delay[i] += buff.real();
        buff = 0.0;
        for (j = 0u; j < harf_m; j++) {
            base_index = j << 1u;
            base_next_index = base_index + 1u;
            buff += (denominator_coefficients[base_index] * sin_w[i] + 2.0 * denominator_coefficients[base_next_index] * sin_2w[i]) / (1.0 + denominator_coefficients[base_index] * sin_w[i] + denominator_coefficients[base_next_index] * sin_2w[i]);
        }
        group_delay[i] -= buff.real();
    }

    if (n_odd) {
        for (i = 0u; i < s; i++) {
            buff = (numerator_coefficients[n - 1u] * sin_w[i]) / (1.0 + numerator_coefficients[n - 1] * sin_w[i]);
            group_delay[i] += buff.real();
        }
    }

    if (m_odd) {
        for (i = 0u; i < s; i++) {
            buff = (denominator_coefficients[m - 1u] * sin_w[i]) / (1.0 + denominator_coefficients[m - 1] * sin_w[i]);
            group_delay[i] -= buff.real();
        }
    }
    return true;
}

double dsplab::filter::IIR::operator()(const double &input) {

    if (nullptr == IIR::delays) return 0.0;
    if (nullptr == IIR::scaling_coefficient) return 0.0;
    if (nullptr == IIR::numerator_coefficients) return 0.0;
    if (nullptr == IIR::denominator_coefficients) return 0.0;

    double output = 0.0;
    double buffer = 0.0;
    output = input;
    unsigned i, base_index, base_next_index;
    for (i = 0u; i < delays_length; i++) {
        base_index = i << 1u;
        base_next_index = base_index + 1u;
        if (base_next_index < m) {
            buffer = output - denominator_coefficients[base_index] * delays[base_index] - denominator_coefficients[base_next_index] * delays[base_next_index];
        }
        else {
            buffer = output;
        }
        if (base_next_index < n) {
            output = buffer + numerator_coefficients[base_index] * delays[base_index] + numerator_coefficients[base_next_index] * delays[base_next_index];
        }
        else {
            output = buffer;
        }
        delays[base_next_index] = delays[base_index];
        delays[base_index] = buffer;
    }

    if (m_odd) {
        buffer = output - denominator_coefficients[m - 1] * delays[delays_length - 1];
    }
    else {
        buffer = output;
    }
    
    if (n_odd) {
        output = buffer + numerator_coefficients[n - 1] * delays[delays_length - 1];
    }
    else {
        output = buffer;
    }

    return output;
}

std::complex<double>& dsplab::filter::IIR::operator[](unsigned int index) {

    static std::complex<double> buff;
    buff = 0.0;
    if (nullptr == frequency_response) return buff;
    if (index >= s) return buff;
    return frequency_response[index];
}

const std::complex<double>& dsplab::filter::IIR::operator[](unsigned int index) const {
    
    static std::complex<double> buff;
    buff = 0.0;
    if (nullptr == frequency_response) return buff;
    if (index >= s) return buff;
    return frequency_response[index];
}

bool dsplab::filter::IIR::WriteCoefficients(const char* filename) {

    if (nullptr == filename) return false;
    if (nullptr == scaling_coefficient) return false;

    FILE *fp = nullptr;
    fp = std::fopen(filename, "w");
    if (nullptr == fp) return false;

    std::fprintf(fp, "a_0,%-16.15lf\n", *scaling_coefficient);

    if (nullptr != numerator_coefficients) {
        for (unsigned int i = 0u; i < n; i++) {
            std::fprintf(fp, "a_%u,%-16.15lf\n", (i + 1), numerator_coefficients[i]);
        }
    }

    if (nullptr != denominator_coefficients) {
        for (unsigned int i = 0u; i < m; i++) {
            std::fprintf(fp, "b_%u,%-16.15lf\n", (i + 1), denominator_coefficients[i]);
        }
    }

    std::fclose(fp);
    fp = nullptr;
    return true;
}

bool dsplab::filter::IIR::WriteFrequencyResponse(const char* filename) {

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

bool dsplab::filter::IIR::WriteMagnitudeResponse(const char* filename, bool decibel) {

    if (nullptr == filename) return false;
    if (nullptr == normalized_angular_frequency) return false;
    if (nullptr == frequency_response) return false;

    FILE *fp = nullptr;
    fp = std::fopen(filename, "w");

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

bool dsplab::filter::IIR::WritePhaseResponse(const char* filename) {
    if (nullptr == filename) return false;
    if (nullptr == normalized_angular_frequency) return false;
    if (nullptr == frequency_response) return false;

    FILE *fp = nullptr;
    fp = std::fopen(filename, "w");

    for (unsigned int i = 0u; i < s; i++) {
        std::fprintf(fp, "%-16.15lf,%-16.15lf\n", normalized_angular_frequency[i], std::arg(frequency_response[i]));
    }

    std::fclose(fp);
    fp = nullptr;
    return true;
}

bool dsplab::filter::IIR::WriteGroupDelay(const char* filename) {
    
    if (nullptr == filename) return false;
    if (nullptr == normalized_angular_frequency) return false;
    if (nullptr == group_delay) return false;

    FILE *fp = nullptr;
    fp = std::fopen(filename, "w");

    for (unsigned int i = 0u; i < s; i++) {
        std::fprintf(fp, "%-16.15lf,%-16.15lf\n", normalized_angular_frequency[i], group_delay[i]);
    }

    std::fclose(fp);
    fp = nullptr;
    return true;
}

bool dsplab::filter::IIR::WriteZeros(const char* filename) {

    if (nullptr == filename) return false;
    if (nullptr == numerator_coefficients) return false;

    std::complex<double> *zeros = new std::complex<double>[n];

    for (unsigned int i = 0u; i < harf_n; i++) {
        dsplab::math::Polynomial::QuadraticFormula(&zeros[i << 1u], numerator_coefficients[i << 1u], numerator_coefficients[(i << 1u) + 1]);
    }

    if (n_odd) {
        zeros[n - 1].real(-numerator_coefficients[n - 1]);
    }

    FILE *fp = nullptr;
    fp = std::fopen(filename, "w");
    for (unsigned int i = 0u; i < n; i++) {
        std::fprintf(fp, "%-16.15lf,%-16.15lf\n", zeros[i].real(), zeros[i].imag());
    }
    std::fclose(fp);
    fp = nullptr;
    delete[] zeros;
    zeros = nullptr;
    return true;
}

bool dsplab::filter::IIR::WritePoles(const char* filename) {

    if (nullptr == filename) return false;
    if (nullptr == denominator_coefficients) return false;

    std::complex<double> *poles = new std::complex<double>[m];

    for (unsigned int i = 0u; i < harf_m; i++) {
        dsplab::math::Polynomial::QuadraticFormula(&poles[i << 1u], denominator_coefficients[i << 1u], denominator_coefficients[(i << 1u) + 1]);
    }

    if (m_odd) {
        poles[m - 1].real(-denominator_coefficients[m - 1]);
    }

    FILE *fp = nullptr;
    fp = std::fopen(filename, "w");
    for (unsigned int i = 0u; i < m; i++) {
        std::fprintf(fp, "%-16.15lf,%-16.15lf\n", poles[i].real(), poles[i].imag());
    }
    std::fclose(fp);
    fp = nullptr;
    return true;
}

bool dsplab::filter::IIR::IsStability() {

    if (nullptr == denominator_coefficients) return false;

    for (unsigned int i = 0u; i < harf_m; i++) {
        if (!dsplab::filter::IIR::StabilityTriangle(denominator_coefficients[i << 1u], denominator_coefficients[(i << 1u) + 1u])) {
            return false;
        }
    }

    if (m_odd) {
        if (!dsplab::filter::IIR::StabilityOfRealRoot(denominator_coefficients[m - 1u])) {
            return false;
        }
    }
    return true;
}

bool dsplab::filter::IIR::ClearDelays() {

    if (nullptr == delays) return false;

    for (unsigned int i = 0u; i < delays_length; i++) {
        delays[i] = 0.0;
    }

    return true;
}

bool dsplab::filter::IIR::ToSymmetry(double *numerator_coefficients, double *denominator_coefficients, unsigned int n, unsigned int m) {

    if (0u == n && 0u == m) return false;
    if (nullptr == numerator_coefficients && nullptr == denominator_coefficients) return false;

    if (nullptr != numerator_coefficients) {
        for (unsigned int i = 0u; i < n; i++) {
            if (0 == i % 2u) {
                numerator_coefficients[i] = -numerator_coefficients[i];
            }
        }
    }

    if (nullptr != denominator_coefficients) {
        for (unsigned int i = 0u; i < m; i++) {
            if (0 == i % 2u) {
                denominator_coefficients[i] = -denominator_coefficients[i];
            }
        }
    }

    return true;
}

bool dsplab::filter::IIR::CreateFrequencySample(double *normalized_angular_frequency, unsigned int s) {
    if (nullptr == normalized_angular_frequency) return false;
    if (s < 2u) return false;

    double delta = dsplab::constants::PI / (s - 1u);

    for (unsigned int i = 0u; i < s; i++) {
        normalized_angular_frequency[i] = i * delta;
    }
    return true;
}

bool dsplab::filter::IIR::StabilityTriangle(const double &b_1, const double &b_2) {
    if (-1.0 < b_2 && b_2 < 1.0) {
        if (b_2 > std::fabs(b_1) - 1.0) {
            return true;
        }
    }
    return false;
}

bool dsplab::filter::IIR::StabilityOfRealRoot(const double &b_1) {
    if (-1.0 < b_1 && b_1 < 1.0) return true;
    else return false;
}

bool dsplab::filter::IIR::CoefficientsToZeros(std::complex<double> *zeros, double *coefficients, unsigned int n) {

    if (nullptr == zeros) return false;
    if (nullptr == coefficients) return false;
    if (0u == n) return false;

    for (unsigned int i = 0u; i < (n >> 1u); i++) {
        dsplab::math::Polynomial::QuadraticFormula(&zeros[i << 1u], coefficients[i << 1u], coefficients[(i << 1u) + 1]);
    }
    if (1u == n % 2u) {
        zeros[n - 1] = -coefficients[n - 1];
    }
    return true;
}