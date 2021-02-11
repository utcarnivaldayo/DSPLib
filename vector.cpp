//------------------------------------------------------------------------------
//
//          The file is part of the DSPLAB Library.
//
//          Copyright (c) 2019-2021 Yuta Harigae
//
//          Licensed under the Apache License, Version 2.0 (the "License").
//
//------------------------------------------------------------------------------

#include "vector.hpp"

bool dsplab::math::Vector::Zero(double *vector, unsigned int length) {

    if (nullptr == vector) return false;
    for (unsigned int i = 0u; i < length; i++) {
        vector[i] = 0.0;
    }
    return true;
}

bool dsplab::math::Vector::Zero(std::complex<double> *vector, unsigned int length) {

    if (nullptr == vector) return false;
    for (unsigned int i = 0u; i < length; i++) {
        vector[i] = 0.0;
    }
    return true;
}

bool dsplab::math::Vector::One(double *vector, unsigned int length) {

    if (nullptr == vector) return false;
    for (unsigned int i = 0u; i < length; i++) {
        vector[i] = 1.0;
    }
    return true;
}

bool dsplab::math::Vector::One(std::complex<double> *vector, unsigned int length) {

    if (nullptr == vector) return false;
    for (unsigned int i = 0u; i < length; i++) {
        vector[i] = 1.0;
    }
    return true;
}

bool dsplab::math::Vector::Add(double *output, double *vector_a, double *vector_b, unsigned int length) {

    if (nullptr == output) return false;
    if (nullptr == vector_a) return false;
    if (nullptr == vector_b) return false;

    for (unsigned int i = 0u; i < length; i++) {
        output[i] = vector_a[i] + vector_b[i];
    }
    return true;
}

bool dsplab::math::Vector::Add(double *vector_a, double *vector_b, unsigned int length) {

    if (nullptr == vector_a) return false;
    if (nullptr == vector_b) return false;
    for (unsigned int i = 0u; i < length; i++) {
        vector_a[i] += vector_b[i];
    }
    return true;
}

bool dsplab::math::Vector::Add(double *output, double *vector, double scalar, unsigned int length) {

    if (nullptr == output) return false;
    if (nullptr == vector) return false;
    for (unsigned int i = 0u; i < length; i++) {
        output[i] = vector[i] + scalar;
    }
    return true;
}

bool dsplab::math::Vector::Add(double *vector, double scalar, unsigned int length) {

    if (nullptr == vector) return false;
    for (unsigned int i = 0u; i < length; i++) {
        vector[i] += scalar;
    }
    return true;
}

bool dsplab::math::Vector::Add(std::complex<double> *output, std::complex<double> *vector_a, std::complex<double> *vector_b, unsigned int length) {

    if (nullptr == output) return false;
    if (nullptr == vector_a) return false;
    if (nullptr == vector_b) return false;
    for (unsigned int i = 0u; i < length; i++) {
        output[i] = vector_a[i] + vector_b[i];
    }
    return true;
}

bool dsplab::math::Vector::Add(std::complex<double> *vector_a, std::complex<double> *vector_b, unsigned int length) {

    if (nullptr == vector_a) return false;
    if (nullptr == vector_b) return false;
    for (unsigned int i = 0u; i < length; i++) {
        vector_a[i] += vector_b[i];
    }
    return true;
}

bool dsplab::math::Vector::Add(std::complex<double> *output, std::complex<double> *vector, std::complex<double> scalar, unsigned int length) {

    if (nullptr == output) return false;
    if (nullptr == vector) return false;
    for (unsigned int i = 0u; i < length; i++) {
        output[i] = vector[i] + scalar;
    }
    return true;
}

bool dsplab::math::Vector::Add(std::complex<double> *vector, std::complex<double> scalar, unsigned int length) {

    if (nullptr == vector) return false;
    for (unsigned int i = 0u; i < length; i++) {
        vector[i] += scalar;
    }
    return true;
}

//sub
bool dsplab::math::Vector::Substract(double *output, double *vector_a, double *vector_b, unsigned int length) {

    if (nullptr == output) return false;
    if (nullptr == vector_a) return false;
    if (nullptr == vector_b) return false;

    for (unsigned int i = 0u; i < length; i++) {
        output[i] = vector_a[i] - vector_b[i];
    }
    return true;
}

bool dsplab::math::Vector::Substract(double *vector_a, double *vector_b, unsigned int length) {

    if (nullptr == vector_a) return false;
    if (nullptr == vector_b) return false;
    for (unsigned int i = 0u; i < length; i++) {
        vector_a[i] -= vector_b[i];
    }
    return true;
}

bool dsplab::math::Vector::Substract(double *output, double *vector, double scalar, unsigned int length) {

    if (nullptr == output) return false;
    if (nullptr == vector) return false;
    for (unsigned int i = 0u; i < length; i++) {
        output[i] = vector[i] - scalar;
    }
    return true;
}

bool dsplab::math::Vector::Substract(double *vector, double scalar, unsigned int length) {

    if (nullptr == vector) return false;
    for (unsigned int i = 0u; i < length; i++) {
        vector[i] -= scalar;
    }
    return true;
}

bool dsplab::math::Vector::Substract(std::complex<double> *output, std::complex<double> *vector_a, std::complex<double> *vector_b, unsigned int length) {

    if (nullptr == output) return false;
    if (nullptr == vector_a) return false;
    if (nullptr == vector_b) return false;
    for (unsigned int i = 0u; i < length; i++) {
        output[i] = vector_a[i] - vector_b[i];
    }
    return true;
}

bool dsplab::math::Vector::Substract(std::complex<double> *vector_a, std::complex<double> *vector_b, unsigned int length) {

    if (nullptr == vector_a) return false;
    if (nullptr == vector_b) return false;
    for (unsigned int i = 0u; i < length; i++) {
        vector_a[i] -= vector_b[i];
    }
    return true;
}

bool dsplab::math::Vector::Substract(std::complex<double> *output, std::complex<double> *vector, std::complex<double> scalar, unsigned int length) {

    if (nullptr == output) return false;
    if (nullptr == vector) return false;
    for (unsigned int i = 0u; i < length; i++) {
        output[i] = vector[i] - scalar;
    }
    return true;
}

bool dsplab::math::Vector::Substract(std::complex<double> *vector, std::complex<double> scalar, unsigned int length) {

    if (nullptr == vector) return false;
    for (unsigned int i = 0u; i < length; i++) {
        vector[i] -= scalar;
    }
    return true;
}

bool dsplab::math::Vector::Scalar(double *output, double *vector_a, double *vector_b, unsigned int length) {
    
    if (nullptr == output) return false;
    if (nullptr == vector_a) return false;
    if (nullptr == vector_b) return false;
    for (unsigned int i = 0u; i < length; i++) {
        output[i] = vector_a[i] * vector_b[i];
    }
    return true;
}

bool dsplab::math::Vector::Scalar(double *vector_a, double *vector_b, unsigned int length) {
    
    if (nullptr == vector_a) return false;
    if (nullptr == vector_b) return false;
    for (unsigned int i = 0u; i < length; i++) {
        vector_a[i] *= vector_b[i];
    }
    return true;
}

bool dsplab::math::Vector::Scalar(double *output, double *vector, double scalar, unsigned int length) {
    
    if (nullptr == output) return false;
    if (nullptr == vector) return false;
    for (unsigned int i = 0u; i < length; i++) {
        output[i] = vector[i] * scalar;
    }
    return true;
}

bool dsplab::math::Vector::Scalar(double *vector, double scalar, unsigned int length) {
    
    if (nullptr == vector) return false;
    for (unsigned int i = 0u; i < length; i++) {
        vector[i] *= scalar;
    }
    return true;
}

bool dsplab::math::Vector::Scalar(std::complex<double> *output, std::complex<double> *vector_a, std::complex<double> *vector_b, unsigned int length) {
    
    if (nullptr == output) return false;
    if (nullptr == vector_a) return false;
    if (nullptr == vector_b) return false;
    for (unsigned int i = 0u; i < length; i++) {
        output[i] = vector_a[i] * vector_b[i];
    }
    return true;
}

bool dsplab::math::Vector::Scalar(std::complex<double> *vector_a, std::complex<double> *vector_b, unsigned int length) {
    
    if (nullptr == vector_a) return false;
    if (nullptr == vector_b) return false;
    for (unsigned int i = 0u; i < length; i++) {
        vector_a[i] *= vector_b[i];
    }
    return true;
}

bool dsplab::math::Vector::Scalar(std::complex<double> *output, std::complex<double> *vector, std::complex<double> scalar, unsigned int length) {

    if (nullptr == output) return false;
    if (nullptr == vector) return false;
    for (unsigned int i = 0u; i < length; i++) {
        output[i] = vector[i] * scalar;
    }
    return true;
}

bool dsplab::math::Vector::Scalar(std::complex<double> *vector, std::complex<double> scalar, unsigned int length) {

    if (nullptr == vector) return false;
    for (unsigned int i = 0u; i < length; i++) {
        vector[i] *= scalar;
    }
    return true;
}

double dsplab::math::Vector::Inner(double *vector_a, double *vector_b, unsigned int length) {

    if (nullptr == vector_a) return 0.0;
    if (nullptr == vector_b) return 0.0;
    double inner = 0.0;

    for (unsigned int i = 0u; i < length; i++) {
        inner += vector_a[i] * vector_b[i];
    }
    return inner;
}

std::complex<double> dsplab::math::Vector::Inner(std::complex<double> *vector_a, std::complex<double> *vector_b, unsigned int length) {

    if (nullptr == vector_a) return 0.0;
    if (nullptr == vector_b) return 0.0;

    std::complex<double> inner;
    for (unsigned int i = 0u; i < length; i++) {
        inner += vector_a[i] * std::conj(vector_b[i]);
    }
    return inner;
}

double dsplab::math::Vector::SquareSum(double *vector, unsigned int length) {
    
    if (nullptr == vector) return 0.0;
    return Inner(vector, vector, length);
}

double dsplab::math::Vector::SquareSum(std::complex<double>* vector, unsigned int length) {

    if (nullptr == vector) return 0.0;
    std::complex<double> inner;
    for (unsigned int i = 0u; i < length; i++) {
        inner += vector[i] * std::conj(vector[i]);
    }
    return inner.real();
}

double dsplab::math::Vector::L2(double *vector, unsigned int length) {
    
    if (nullptr == vector) return 0.0;
    return std::sqrt(SquareSum(vector, length));
}

double dsplab::math::Vector::L2(std::complex<double> *vector, unsigned int length) {
    
    if (nullptr == vector) return 0.0;
    return std::sqrt(SquareSum(vector, length));
}

double dsplab::math::Vector::L1(double *vector, unsigned int length) {

    if (nullptr == vector) return 0.0;
    double norm = 0.0;
    for (unsigned int i = 0u; i < length; i++) {
        norm += std::fabs(vector[i]);
    }
    return norm;
}

double dsplab::math::Vector::L1(std::complex<double> *vector, unsigned int length) {

    if (nullptr == vector) return 0.0;
    double norm = 0.0;
    for (unsigned int i = 0u; i < length; i++) {
        norm += std::abs(vector[i]);
    }
    return norm;
}

bool dsplab::math::Vector::Print(double *vector, unsigned int length) {

    if (nullptr == vector) return false;
    for (unsigned int i = 0; i < length; i++) {
        if (0u == i) {
            std::printf("[ %lf", vector[i]);
        }
        else {
            std::printf("  %lf", vector[i]);
        }
        if ((length - 1) == i) {
            std::printf(" ]");
        }
        std::printf("\n");
    }
    return true;
}

bool dsplab::math::Vector::Print(std::complex<double> *vector, unsigned int length) {

    if (nullptr == vector) return false;
    for (unsigned int i = 0; i < length; i++) {
        if (0u == i) {
            if (vector[i].real() > 0.0) {
                std::printf("[ %lf + j%lf", vector[i].real(), vector[i].imag());
            }
            else {
                std::printf("[ %lf - j%lf", vector[i].real(), -vector[i].imag());
            }
        }
        else {
            if (vector[i].real() > 0.0) {
                std::printf("  %lf + j%lf", vector[i].real(), vector[i].imag());
            }
            else {
                std::printf("  %lf - j%lf", vector[i].real(), -vector[i].imag());
            }
        }
        if ((length - 1) == i) {
            std::printf(" ]");
        }
        std::printf("\n");
    }
    return true;
}

bool dsplab::math::Vector::Write(const char* filename, double *vector, unsigned int length) {

    if (nullptr == filename) return false;
    if (nullptr == vector) return false;

    FILE *fp = nullptr;
    fp = std::fopen(filename, "w");
    if (nullptr == fp) return false;

    for (unsigned int i = 0u; i < length; i++) {
        std::fprintf(fp, "%16.15lf\n", vector[i]);
    }
    std::fclose(fp);
    fp = nullptr;
    return true;
}

bool dsplab::math::Vector::Write(const char* filename, std::complex<double> *vector, unsigned int length) {

    if (nullptr == filename) return false;
    if (nullptr == vector) return false;

    FILE *fp = nullptr;
    fp = std::fopen(filename, "w");
    if (nullptr == fp) return false;

    for (unsigned int i = 0u; i < length; i++) {
        std::fprintf(fp, "%16.15lf,%16.15\n", vector[i].real(), vector[i].imag());
    }
    std::fclose(fp);
    fp = nullptr;
    return true;
}