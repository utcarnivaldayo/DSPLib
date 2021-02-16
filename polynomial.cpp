//------------------------------------------------------------------------------
//
//          The file is part of the DSPLAB Library.
//
//          Copyright (c) 2019-2021 Yuta Harigae
//
//          Licensed under the Apache License, Version 2.0 (the "License").
//
//------------------------------------------------------------------------------

#include "polynomial.hpp"

bool dsplab::math::Polynomial::QuadraticFormula(std::complex<double> *roots, double c_1, double c_2, double c_0) {

    double d = c_1 * c_1 - 4.0 * c_0 * c_2;
    double m = 2.0 * c_0;
    double real = 0.0;
    double imaginaly = 0.0;
    if (d < 0.0) {
        real = -c_1 / m;
        imaginaly = std::sqrt(-d) / m;
        roots[0].real(real);
        roots[0].imag(imaginaly);
        roots[1].real(real);
        roots[1].imag(-imaginaly);
    }
    else if (d > 0.0) {
        if (c_1 > 0.0) {
            roots[0] = -c_1 - std::sqrt(d);
            roots[0] /= m;
        }
        else {
            roots[0] = -c_1 + std::sqrt(d);
            roots[0] /= m;
        }
        roots[1] = c_2 / (roots[0].real() * c_0);
    }
    else {
        roots[0] = -c_1 / m;
        roots[1] = roots[0].real();
    }
    return true;
}

bool dsplab::math::Polynomial::VietaFormula(double* coefficients, std::complex<double>* roots, unsigned int n, double scaling_coefficient) {

    if (nullptr == roots) return false;
    if (nullptr == coefficients) return false;
    if (0u == n) return false;
    if (0.0 == scaling_coefficient) return false;
    std::complex<double> buff;
    unsigned int* index = nullptr;
    unsigned int i, j, p, ipp;

    for (i = 0u; i < n; i++) {
        ipp = i + 1u;
        index = new unsigned int[ipp];
        for (j = 0u; j < ipp; j++) index[j] = j;
        while(1) {
            p = 0u;
            buff = 1.0;
            for (j = 0u; j < ipp; j++) buff *= roots[index[j]];
            coefficients[i] += buff.real();
            
            //check carry
            for (j = ipp; j > 0u; j--) {
                if (index[j - 1u] == (n - i + j - 2)) p++;
                else break;
            }
            if (index[0] == (n - 1 - i)) break;

            //carry
            index[i - p]++;
            for (j = p; j > 0u; j--) index[ipp - j] = index[i - j] + 1u;
        }
        if (1u == ipp % 2u) coefficients[i] = -coefficients[i] / scaling_coefficient;
        else coefficients[i] /= scaling_coefficient;
        delete[] index;
        index = nullptr;
    }
    return true;
}

double dsplab::math::Polynomial::Horner(double *coefficients, unsigned int n, double &z, double non_monic) {

    if (nullptr == coefficients) return 0.0;
    if (0u == n) return 0.0;
    double ans = non_monic;
    for (unsigned int i = 0u; i < n; i++) {
        ans *= z;
        ans += coefficients[i];
    }
    return ans;
}

std::complex<double> dsplab::math::Polynomial::Horner(double *coefficients, unsigned int n, std::complex<double> &z, double non_monic) {

    if (nullptr == coefficients) return 0.0;
    if (0u == n) return 0.0;
    std::complex<double> ans = non_monic;
    for (unsigned int i = 0u; i < n; i++) {
        ans *= z;
        ans += coefficients[i];
    }
    return ans;
}

std::complex<double> dsplab::math::Polynomial::Horner(std::complex<double> *coefficients, unsigned int n, std::complex<double> &z, std::complex<double> non_monic) {

    if (nullptr == coefficients) return 0.0;
    if (0u == n) return 0.0;
    std::complex<double> ans = non_monic;
    for (unsigned int i = 0u; i < n; i++) {
        ans *= z;
        ans += coefficients[i];
    }
    return ans;
}

std::complex<double> dsplab::math::Polynomial::ReverseHorner(double *coefficients, unsigned int length, std::complex<double> &z) {

    if (nullptr == coefficients) return 0.0;
    if (0u == length) return 0.0;
    std::complex<double> ans = coefficients[length - 1];
    for (unsigned int i = length - 2; i >= 1u; i--) {
        ans *= z;
        ans += coefficients[i];
    }
    ans *= z;
    ans += coefficients[0];
    return ans;
}

std::complex<double> dsplab::math::Polynomial::ReverseHorner(std::complex<double> *coefficients, unsigned int length, std::complex<double> &z) {

    if (nullptr == coefficients) return 0.0;
    if (0u == length) return 0.0;
    std::complex<double> ans = coefficients[length - 1u];
    for (unsigned int i = length - 2u; i > 1u; i--) {
        ans *= z;
        ans += coefficients[i];
    }
    ans *= z;
    ans += coefficients[0];
    return ans;
}

bool dsplab::math::Polynomial::DKAMethod(std::complex<double> *zeros, std::complex<double> *coefficients, unsigned int n) {
    
    if (nullptr == zeros) return false;
    if (nullptr == coefficients) return false;
    if (0u == n) return false;

    std::complex<double> *honer = new std::complex<double>[n];
    std::complex<double> *taylor_coefficients = new std::complex<double>[n];
    std::complex<double> buffer;
    double *real_taylor_coefficients = new double[n + 1u];
    double *differential_coefficients = new double[n];
    double before_radius = 0.0;
    double radius = 1000.0;
    unsigned int fixed_point = 0u;
    const double EPS = 1.0e-7;
    unsigned i, j, cnt;

    //barycentor
    std::complex<double> b = -coefficients[0] / (double)n;

    //kumitate
    for (i = 0u; i < n; i++) {
        taylor_coefficients[0] += b;
        for (j = 1u; j < n - i - 1u; j++) {
            taylor_coefficients[j] = taylor_coefficients[j - 1u] * b + coefficients[j];
        }
    }

    real_taylor_coefficients[0] = 1.0;
    for (i = 2u; i < n + 1u; i++) {
        real_taylor_coefficients[i] = -std::abs(taylor_coefficients[i - 1u]);
    }

    for (i = 0u; i < n; i++) {
        differential_coefficients[i] = (n - i) * real_taylor_coefficients[i];
    }

    //newton method
    while(std::fabs(before_radius - radius) >= EPS) {
        before_radius = radius;
        radius = before_radius - dsplab::math::Polynomial::Horner(&real_taylor_coefficients[1], n + 1u, before_radius, real_taylor_coefficients[0]) / Horner(&differential_coefficients[1], n, before_radius, differential_coefficients[0]);
    }

    //initial point
    for (i = 0u; i < n; i++) {
        zeros[i] = std::polar(radius, dsplab::constants::DOUBLE_PI * i / n + 3.0 / (2.0 * n)) + b;
    }

    //second order method
    cnt = 0u;
    while(true) {
        //smith's method
        for (i = fixed_point; i < n; i++) {
            honer[i] = dsplab::math::Polynomial::Horner(coefficients, n, zeros[i]);
            if (std::abs(honer[i]) < EPS) {
                buffer = honer[fixed_point];
                honer[fixed_point] = honer[i];
                honer[i] = buffer;
                fixed_point++;
            }
        }
        if (fixed_point == n) break;
        for (i = fixed_point; i < n; i++) {
            zeros[i] = zeros[i] - honer[i] / dsplab::math::Polynomial::DenominatorOfSecondOrderMethod(zeros, n, i);
        }
        cnt++;
        if (cnt == 1000u) break;
    }
    delete[] honer;
    honer = nullptr;
    delete[] taylor_coefficients;
    taylor_coefficients = nullptr;
    delete[] real_taylor_coefficients;
    real_taylor_coefficients = nullptr;
    delete[] differential_coefficients;
    differential_coefficients = nullptr;
    return true;
}

std::complex<double> dsplab::math::Polynomial::DenominatorOfSecondOrderMethod(std::complex<double> *zeros, unsigned int n, unsigned int index) {

    if (nullptr == zeros) return 0.0;
    if (0u  == n) return 0.0;
    std::complex<double> ans = 1.0;
    for (unsigned int i = 0u; i < n; i++) {
        if (i == index) continue;
        ans *= zeros[index] - zeros[i];
    }
    return ans;
}